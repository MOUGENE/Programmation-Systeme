#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include "Sommet.h"
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <time.h>
#include <termios.h>
#include <signal.h>

int x;
int size;
int *tabProcessus = NULL;
int loop = 1;
Sommet* sommets;



void handle_sig1(int sig){
	for(int i = 0; i < size;i++){
		kill(sommets[i].processus,SIGUSR2);
	}
}
void handle_sig2(int sig){	
	loop = 0;
}

int kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;
    int count = 0;

    // Sauvegarde de la configuration actuelle du terminal
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Modification de la configuration pour désactiver la mise en mémoire tampon de l'entrée
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Obtention du descripteur de fichier du terminal
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    // Lecture de tous les caractères présents dans le tampon d'entrée
    while ((ch = getchar()) != EOF) {
        count++;
    }

    // Restauration de la configuration initiale du terminal
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    // Vérification s'il y a eu une saisie
    if (count > 0) {
        // S'il y a eu une saisie, vider le tampon d'entrée
        
        return 1;
    }

    return 0;
}


int main(int argc, char* argv[]) {
    
    if(argc != 2) {
        printf("Error\n");
        return 1;
    }
    
    
    fd_set rfds;
    int nfds = 0;
    int token = 0;
    int current = 0;
    char buffer[26];
    char message[100];
    int dest; //Descripteur de fichier
    time_t timer;
    struct tm* tm_info;
    x = atoi(argv[1]); //Dimension
    size = 1 << x; //2^n Sommet
    int pipeCount = size * x; // 2^n * n tubes
    int fdCount = (size << 1) * x; // 2^n+1 * n descripteur de fichier
    int pipes[pipeCount][2]; //Tableau de tubes
    sommets = (Sommet*) malloc(sizeof(Sommet)*size); //Tableau de Sommet
    int fds[fdCount]; // tableau de descripteur de fichier
    int* voisins; // voisins du processus actuel
    int taille; // taille du tableau des voisins
    srand(time(NULL)); // Initialisation du générateur de nombre aléatoire
    tabProcessus = (int*) calloc(size,sizeof(int));
    
    
    //int parentPid = getpid();

    /*dest = open (argv[2], O_WRONLY | O_CREAT, 0644);
    if(dest == -1) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }*/

   
	signal(SIGUSR1,handle_sig1);
	signal(SIGINT,handle_sig1);
    for(int i = 0; i < pipeCount; i++) {
        if(pipe(pipes[i]) < 0) {
            perror("Erreur lors de la création du tube\n");
            exit(EXIT_FAILURE);
        }
    }

    for(int i = 0; i < fdCount; i++) {
        fds[i] = open("Hypercube.txt", O_WRONLY | O_CREAT, 0644);
        if(fds[i] == -1) {
            perror("Erreur lors de l'ouverture du fichier.\n");
            exit(EXIT_FAILURE);
        }
    }
    signal(SIGUSR2,handle_sig2);

    for(int i = 0; i < size; i++) {
        sommets[i] = returnBlankSommet();
        if(i == 0) {
            initPremierSommet(&sommets[i], x);
        } 
        else {
            initSommetSuivant(&sommets[i], sommets[i-1]);
        }
        sommets[i].processus = fork();
        if(sommets[i].processus < 0) {
            fprintf(stderr,"Erreur init fork\n");
        }
        if(sommets[i].processus == 0) {
        	
        	
            while(loop) {
                free(voisins);
                // Détermination des voisins du sommet actuel
                voisins = voisinAdj(sommets[current], sommets, size, &taille);

                /*printf("Voisin de %d : ",current);
                for(int i = 0; i < taille; i++) {
                    printf("%d ",voisins[i]);
                }
                printf("\n");*/
        
                //Initialisation de l'ensemble de descripteurs de fichiers
                FD_ZERO(&rfds);

                // Préparation de l'ensemble de descripteurs de fichiers pour select()
                for(int i = 0; i < taille; i++) {
                    FD_SET(fds[voisins[i]*2],&rfds);
                    //printf("COUCOU FD SET\n");
                    if(fds[voisins[i]*2+1] > nfds) {
                        nfds = fds[voisins[i]*2];
                    }
                }

                // Appel à select()
                dest = select(nfds+1, &rfds, NULL, NULL, NULL);

                if(dest == -1) {
                    perror("select\n");
                } 
        
                else if (dest) {
            
                    //Ecriture dans aléatoire dans les tubes
                    int random_voisins = rand() % taille;
                    current = voisins[random_voisins];
                    write(pipes[voisins[random_voisins]][1],&token,sizeof(token));
            
                    //On obtient l'heure actuelle
                    //Incrémentation du token
                    token++;
                    time(&timer);
                    tm_info = localtime(&timer);
                    //Formate l'heure en chaine de caractères
                    strftime(buffer,26,"%Y-%m-%d %H:%M:%S", tm_info);
                    printf("Token : %d, Heure de passage : %s, Processus : %s\n",token,buffer,sommets[current].etiquette);
                    //Créer le message a écrire dans le fichier
                    //Ecrit le message dans le fichier
                    snprintf(message,sizeof(message), "Token : %d, Heure de passage : %s, Processus : %s\n",token,buffer,sommets[current].etiquette);
                    write(fds[voisins[0]],message,strlen(message));

                    // Lecture du token à partir des tubes prêts
                    for(int i = 0; i < taille; i++) {
                        if(FD_ISSET(fds[voisins[i]*2+1], &rfds)) {
                            read(fds[voisins[i]*2+1],&token,sizeof(token)); // Lit le token à partir du tube i
                        }
                    }
            
                    //free(voisins);
                    if(current >= size) {
                        current = 0;
                    }
                } 
                else {
                    printf("Aucun tube n'est pret pour l'ecriture.\n");
                }

                //Réinitialisation de l'ensemble de descripteur de fichiers pour le prochain tour de boucle
                FD_ZERO(&rfds);
                 
                if(kbhit()) {
		    // Une touche a été pressée		    		
		    		kill(getppid(),SIGUSR1);
		    	
		     // Sortir de la boucle
		}
            }
            exit(0);
            
         
        }
        
        //exit(0);
    }

    

    /*voisins = voisinAdj(sommets[current],sommets,size,&taille);
    printf("Voisins de %d : ",token);
    for(int i = 0; i < taille; i++) {
        printf("%d",voisins[i]);
    }
    printf("\n");
    */
    
    for(int i = 0; i < size; i++) {
        wait(NULL);
    }
    printf("FIN\n");
    exit(0);
}
//token écrit dans le tube pour circuler et le processus écrit dans un fichier l'heure de passage du token
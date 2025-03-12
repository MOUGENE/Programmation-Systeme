#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int lancer_piece() {
    int faces = 0;
    for (int i = 0; i < 10; i++) {
        if(rand() % 2 == 0) { // 0 pour "Face", 1 pour "Pile"
            faces++;
        }
        else {
            break; // Arrêt dès qu'on obtient 'Pile'
        }
    }
    return faces;
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        printf("Il manque des paramètres");
        exit(1);
    }

    int n = atoi(argv[1]); // Nombre de processus
    int pipes[n][2]; // Tableau de tubes
    int k;

    // Initialiser le générateur aléatoires
    // srand(time(NULL));

    // Création des tubes
    for(int i = 0; i < n; i++) {
        // Test si pipe() à échouer
        if(pipe(pipes[i]) == -1) {
            perror("pipe");
            exit(1);
        }
    }

    // Processus père
    //int x = lancer_piece(); // Le premier processus fait le lancer initial
    //int h = 1; // On initialise h a 1

    /*int y = lancer_piece();
    printf("Lancer test parent : %d\n",y);*/

    //printf("Processus parent a obtenu : %d 'Face'\n",x);

    // On envoie le couple (x,h) au premier processus
    //write(pipes[0][1], &x, sizeof(int));
    //write(pipes[0][1], &h, sizeof(int));

    for(int i = 0; i < n; i++) {
        if((k=fork()) == 0) {
            // Test si fork() à échouer
            if(k == -1) {
                perror("fork");
                exit(1);
            }

            // Processus fils
            int prev = i == 0 ? n - 1 : i - 1; // Le processus précédent
            int next = i; // Le processus suivant
            int x = 0, h = 1; // Initialise le couple (x,h)

            // Initialiser le générateur aléatoire dans le processus fils grâce à une graine unique
            srand(time(NULL) + getpid());

            // On ferme les tubes non utilisé
            for(int j = 0; j < n; j++) {
                if(j != prev){
                    close(pipes[j][0]); // On ferme toutes les entrées sauf celles du tubes précédent
                }
                if(j != next) {
                    close(pipes[j][1]); // On ferme toutes les sorties sauf celles du suivants
                }
            }

            // Reçoit le couple (x,h) du processus précédent sauf pour le premier processus qui démarre
            if( i!= 0) {
                read(pipes[prev][0], &x, sizeof(int));
                read(pipes[prev][0], &h, sizeof(int));
            }
            
            // Le processus actuel fait son lancer de pièces
            int lancer = lancer_piece();
            //printf("Lancer test fils : %d\n",lancer);
            printf("Processus : %d, pid : %d, a obtenu : %d 'Face', max actuel de 'Face' : %d\n", i + 1, getpid(),lancer,x);

            // Si le processus actuel a obtenu plus de 'Face', alors on met à jour
            if(lancer > x) {
                // Le premier processus fait son lancer et initialise h à 1
                x = lancer;
                printf("Processus : %d, pid : %d, met a jour le maximun de 'Face' à : %d\n", i + 1, getpid(), x);
            }
    
            // Si h == n - 1 alors c'est le dernier processus
            /*if(h == n) {
                printf("Processus : %d, pid : %d, termine avec : %d 'Face' et h = %d \n", i + 1,getpid(),x,h);
            }
            else {
                // Sinon on transmet les couples (x,h + 1) au suivant
                h++;
                //printf("lancer : %d\n",lancer);
                printf("Processus : %d, pid : %d, transmet : %d 'Face' et h = %d \n", i + 1, getpid(),x,h);
                write(pipes[next][1], &x, sizeof(int));
                write(pipes[next][1], &h, sizeof(int));
            }*/

            while (h != n) {
                // Sinon on transmet les couples (x,h + 1) au suivant
                h++;
                //printf("lancer : %d\n",lancer);
                printf("Processus : %d, pid : %d, transmet : %d 'Face' et h = %d \n", i + 1, getpid(),x,h);
                write(pipes[next][1], &x, sizeof(int));
                write(pipes[next][1], &h, sizeof(int));
            }
            
            if(h == n) {
                printf("Processus : %d, pid : %d, termine avec : %d 'Face' et h = %d \n", i + 1,getpid(),x,h);
            }

            // On ferme les tubes restants
            close(pipes[prev][0]);
            close(pipes[next][1]);
            
            // Fin du  processus fils
            exit(0);
        }
    }

    // On attend que tous les processus fils se terminent
    for(int i = 0; i < n; i++) {
        wait(NULL);
    }

    // On ferme tout les tubes dans le processus père
    for(int i = 0; i < n; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    return 0;
}
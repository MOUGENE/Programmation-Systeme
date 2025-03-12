#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

//Fonction récursive pour créer des processus fils
void create_process(int n, int s) {
    int k;
    //Vérifier si n et s sont strictement positifs
    if (n <= 0 || s <= 0) {
        return;
    }
    for (int i = 0; i < n; i++) {
            if ((k = fork()) == 0) {
                if(k < 0) {
                    perror("Erreur lors du fork");
                    exit(1);
                }
                time_t current_time;
                char filename[20];
                char buffer[255];

                //Récupère l'id du fils 
                pid_t child_pid = getpid();

                //Construit le nom du fichier 
                snprintf(filename,sizeof(filename),"pid%d.txt",child_pid);

                //Ouvre le fichier en écriture
                int fd = open(filename, O_WRONLY | O_CREAT, 0644);
                if(fd == -1) {
                    perror("Erreur lors de l'ouverture/creation du fichier");
                    exit(1);
                }

                //Obtenir la date/heure système
                current_time = time(NULL);

                //Créer une chaine de caractères avec les informations a écrire
                int len = snprintf(buffer, sizeof(buffer), "PID : %d\n Date systeme : %ld\n", child_pid, current_time);

                //Ecrire le contenu dans le fichier write()
                if (write(fd, buffer, len) == -1) {
                    perror("Erreur lors de l'ecriture dans le fichier");
                    close(fd);
                    exit(1);
                }

                close(fd);
                printf("Processus fils : %d \n",getpid());
                create_process(n-1,s-1); // Récursivité de création de processus
                exit(0);
            }
        sleep(s);
    }
}

int main (int argc, char* argv []) {
    if(argc != 3) {
        printf("Usage : %s <nombre_de_processus> <delai_en_seconde>\n",argv[0]);
        exit(1);
    }

    int n = atoi(argv[1]); // Nombre de processus à créer
    int s = atoi(argv[2]); // Délai entre chaque création de processus

    // Appel initial de la fonction récursive
    create_process(n,s);

    printf("Processus pere : %d \n",getpid());
    exit(0);
}
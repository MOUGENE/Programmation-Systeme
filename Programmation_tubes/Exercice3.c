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

    // Création des tubes
    for(int i = 0; i < n; i++) {
        // Test si pipe() à échouer
        if(pipe(pipes[i]) == -1) {
            perror("pipe");
            exit(1);
        }
    }

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
            int active = 1; // 1 pour actif, 0 pour passif

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

            while (h != n) {
                h++;
                printf("Processus : %d, pid : %d, transmet : %d 'Face' et h = %d \n", i + 1, getpid(), x, h);
                write(pipes[next][1], &x, sizeof(int));
                write(pipes[next][1], &h, sizeof(int));
            }

            if(h == n) {
                int max_values[n];
                max_values[i] = x;

                for (int j = 0; j < n; j++) {
                    if (j != i) {
                        read(pipes[j][0], &max_values[j], sizeof(int));
                    }
                }

                int is_winner = 1;
                for (int j = 0; j < n; j++) {
                    if (max_values[j] > x) {
                        is_winner = 0;
                        break;
                    }
                }

                if (is_winner) {
                    printf("Processus : %d, pid : %d, est le vainqueur avec : %d 'Face'\n", i + 1, getpid(), x);
                } else {
                    active = 0;
                    printf("Processus : %d, pid : %d, devient passif\n", i + 1, getpid());
                }
            }
            
            /*if(h == n) {
                printf("Processus : %d, pid : %d, termine avec : %d 'Face' et h = %d \n", i + 1,getpid(),x,h);
            }*/

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
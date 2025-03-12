#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/select.h>
#define MAX_PROCESSUS 100

int main(int agrc, char * argv []) {

    if(agrc != 2) {
        printf("Usage : %s <dimension>\n",argv[0]);
        return 1;
    }

    int dest = open (argv[2], O_WRONLY | O_CREAT, 0644);
    if(dest == -1) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    signal(SIGUSR1,handleSignal);
    int token = 0;
    int dimension = atoi(argv[1]);
    int nb_tubes = 2 << (dimension - 1); // Calcul du nombre de tubes -> Tubes 2^n*n
    int nb_pipes = nb_tubes * dimension;
    int pipes[nb_pipes][2];
    
    for(int i = 0; i < nb_pipes; ++i) {
        if(pipe(pipes[i]) == -1){
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }

    int nbProcessus = 1 << dimension; // Calcul du nombre de processus -> Sommet 2^n
    int coord[nbProcessus][MAX_PROCESSUS]; //Tableau pour stocker les coordonnées des sommets

    for(int i  = 0; i < nbProcessus; ++i) {
        int num = i; //Numéro du sommet
        for (int j = 0; j < dimension; ++j) {
            coord[i][j] = num % 2; //Stocke le bit actuel
            num /= 2; //Décale vers la droite
        }
    }

    for(int i = 0; i < nbProcessus; ++i) {
        pid_t pid = fork();
        if(pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0){
            while(1) {
                fd_set readSet;
                FD_ZERO(&readSet);
                FD_SET(father[0], &readSet);

                select(father[0] + 1, &readSet, NULL, NULL, NULL);
            }


            exit(0);
        }
    }

    for(int i = 0; i < nbProcessus; ++i) {
        kill(pid[i],SIGUSR1);
    }

    for(int i = 0; i < nbProcessus; ++i) {
        wait(NULL);
    }

    for(int i = 0; i < nb_pipes; ++i) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    close(dest);
    exit(0);
}
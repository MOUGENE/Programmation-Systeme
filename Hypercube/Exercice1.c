/*
Projet : 
n dim
Sommet 2^n (processus)
Arretes 2^n-1
Tubes 2^n*n
Des 2^n+1 * n
Fonction select : nombre descripteur de fichier, 3 descripteur -> retourne un nombre de descripteur de fichier
dans ses 3 ensembles dans lesquels les données sont disponibles, 3 ensembles read, write,... (que besoin de read)
time val combien de temps d'attente
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#define MAX_PROCESSUS 100

void initializeRelations(int dimension, int relations[][MAX_PROCESSUS]) {
    int numVertices = 1 << dimension; //Nombre de sommet 2^n
    for(int i = 0; i < numVertices; ++i) {
        for(int j = 0; j < numVertices; ++j) {
            //Initialisation a 0 pas de communication par défaut
            relations[i][j] = 0;
        }
    }
}

void fillRelations(int dimension, int relations[][MAX_PROCESSUS]) {
    int numVertices = 1 << dimension;
    for(int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            //Vérifiez si les sommets i et j sont voisins
            int xorResult = i ^ j; //XOR des numéros binaires
            if((xorResult & (xorResult - 1)) == 0) {
                //Un seul bit différent donc voisins
                relations[i][j] == 1;
            }
        }
    }
}

void creationProcessusFilsHypercube(int dimension, int processus, int nbProcessus) {
    if(processus >= nbProcessus) {
        //Cela veut dire que tout les processus ont été créer.
        return;
    }

    if(fork() == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (fork() == 0) {
        printf("Processus %d (PID%d) créé.\n",processus,getpid());
        //Faire le travail des processus fils ici.
        exit(0);
    } else {
        //Processus père.
        creationProcessusFilsHypercube(dimension, processus +1, nbProcessus);
    }
}

int main(int argc, char * argv[]) {

    if(argc != 2) {
        printf("Usage : %s <dimension>\n",argv[0]);
        return 1;
    }

    int token = 0;
    int dimension = atoi(argv[1]);
    if(dimension <= 0) {
        perror("La dimension doit etre strictement positive");
        exit(EXIT_FAILURE);
    }

    int relations[MAX_PROCESSUS][MAX_PROCESSUS];
    initializeRelations(dimension,relations);
    fillRelations(dimension,relations);

    int nb_tubes = 2 << (dimension - 1); //Calcul du nombre de tubes -> Tubes 2^n*n
    int nb_pipes = nb_tubes * dimension;
    int pipes[nb_pipes][2];

    for(int i = 0; i < nb_pipes; ++i) {
        if(pipe(pipes[i]) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }

    int nbProcessus = 1 << dimension; //Calcul du nombre de processus -> Sommet 2^n
    creationProcessusFilsHypercube(dimension;0;nbProcessus);

    for(int i = 0; i < nb_pipes; ++i) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    for (int i = 0; i < nbProcessus; ++i) {
        wait(NULL);
    }

    exit(0);
}
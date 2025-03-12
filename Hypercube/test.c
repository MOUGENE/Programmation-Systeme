#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include "Sommet.h"
#include <string.h>
#include <time.h>
#include <fcntl.h>

int main(int argc, char* argv []) {

    if(argc != 3) {
        printf("Error\n");
        return 1;
    }
    
    fd_set wfds;
    int token = 0;
    char buffer[26];
    int dest;
    time_t timer;
    struct tm* tm_info;

    dest = open (argv[2], O_WRONLY | O_CREAT, 0644);
    if(dest == -1) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    FD_ZERO(&wfds);
    FD_SET(dest, &wfds);

    int pipes[11][2];
    for(int i = 0; i < 11; i++) {
        if(pipe(pipes[i]) == -1) {
            perror("Erreur lors de la création du tube");
            exit(EXIT_FAILURE);
        }
        printf("Tube %d creer avec succes\n",i);
    }
    
    int size = 10;
    Sommet sommets[size];

    for(int i = 0; i < size; i++) {
        sommets[i] = returnBlankSommet();
        if(i == 0) {
            initPremierSommet(&sommets[i], 6);
        } else {
            initSommetSuivant(&sommets[i], sommets[i-1]);
        }
        if(sommets[i].processus == 0){
            exit(0);
        }
    }

    for(int i = 0; i < size; i++) {
        printf("Processus %d : PID = %d\n", i, sommets[i].processus);
    }

    int x = atoi(argv[1]); //Dimension
    int taille = 0;
    int* voisins;
    
    voisins = voisinAdj(sommets[token],sommets,size,&taille);
    printf("Voisins de %d : ",token);
    for(int i = 0; i < taille; i++) {
        printf("%d",voisins[i]);
    }
    printf("\n");

    while(1) {
        dest = select(1,&wfds,NULL,NULL,NULL);

        if(dest == -1) {
            perror("select");
        } else if (dest) {
            printf("Le fichier est pret pour l'ecriture");
            time(&timer);
            tm_info = localtime(&timer);
            strftime(buffer,26,"%Y-%m-%d %H:%M:%S", tm_info);
            voisins = voisinAdj(sommets[token],sommets,size,&taille);
            for(int i = 0; i < taille; i++) {
                write(pipes[voisins[i]][1],&buffer,26);
                printf("Token %d ecrit dans le tube %d\n",token,dest);
            }
            free(voisins);
            token++;
        } else {
            printf("Aucun fichier est pret pour l'ecriture");
        }
    }

    FD_ZERO(&wfds);
    FD_SET(dest,&wfds);
    for(int i = 0; i < size; i++) {
        wait(NULL);
    }
    exit(0);
}
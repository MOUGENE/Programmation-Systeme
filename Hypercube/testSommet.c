#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include "Sommet.h"
#include <string.h>
#include <time.h>

int main(int argc, char** argv) {
    if(argc != 2) {
        printf("Error\n");
        return 1;
    }
    int token = 0;
    int dest = open (argv[2], O_WRONLY | O_CREAT, 0644);
    if(dest == -1) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
    int pipes[11][2];
    for(int i = 0; i < 11; i++) {
        pipe(pipes[i]);
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
        //printf("etiquette : %s\n",sommets[i].etiquette);
        /*if(sommets[i].processus == 0) {
            int temp;
            printf("pid : %i\n", getpid());
            read(pipes[i][0], &temp, sizeof(int));
            temp++;
            write(pipes[i+1][1], &temp, sizeof(int));
            exit(0);
        }*/
        
       
        //kill(sommets[i].processus, SIGSTOP);
    }

    /*int token = 0;
    read(pipes[0][0],&token,sizeof(int));
    write(pipes[0][1],&token,sizeof(int));
    printf("token : %d",token);*/
    int x = atoi(argv[1]);
    //int y = atoi(argv[2]);
    //printf("etiquette  : %s | etiquette : %s || %d\n",sommets[x].etiquette,sommets[y].etiquette,estVoisin(sommets[x],sommets[y]));
    int taille = 0;
    int* v = voisinAdj(sommets[x],sommets,size,&taille);
    printf("%d",taille);
    printf("Voisins : %s\n",sommets[x].etiquette);
    for(int i = 0; i < taille; i++) {
        printf("%d : %s\n",v[i],sommets[v[i]].etiquette);
    }

    for(int i = 0; i < size; i++) {
        wait(NULL);
    }
 
    exit(0);
}

    //write(sommets[i]);
    
    /*
    int f = fork();
    if(f == 0){
        sleep(5);
        kill(getppid(),SIGUSR1);
        exit(0);
    }
    
    struct sigaction sa = {0};
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = &hint;
    sigaction(SIGUSR1,&sa,NULL);
    
    printf("5*3 : ");
    scanf("%d",&x);
    if(x == 15){
        printf("right\n");
    }else{
        printf("wrong\n");
    }
    kill(f,SIGKILL);
    wait(NULL);
    */
    
    
    /*int x = atoi(argv[1]);
    int y = atoi(argv[2]);
    printf("etiquette  : %s | etiquette : %s || %d\n",sommets[x].etiquette,sommets[y].etiquette,estVoisin(sommets[x],sommets[y]));*/
    
    /*if(s.processus == 0){
        sleep(5);
        printf("5 seconds passed");
        
        exit(0);
    }
    
    printf("What is 5 * 2 : ");
    scanf("%d",&x);
    if(x == 10){
        printf("Good answer !\n");        
    }
    else{
        printf("Wrong answer\n");
    }
    kill(s.processus,SIGKILL);
    wait(NULL);
    */
    
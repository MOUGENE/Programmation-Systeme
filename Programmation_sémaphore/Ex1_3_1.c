#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>

/*
    Acceder à 1 des 2 fichiers
*/



int main(){
    int x = 0;
    int semid = semget(4000,2,0);
    struct sembuf s;
    s.sem_num = x; //x = 0 pour l'acces a A, x=1 pour l'acces à B
    s.sem_op = -1;
    semop(semid,&s,1); // P(S0) ou P(S1)  //verouille le fichier
    //Accès au fichier A ou B (section critique)
    s.sem_op = 1;
    semop(semid,&s,1); // operation V()

    exit(0); 
}
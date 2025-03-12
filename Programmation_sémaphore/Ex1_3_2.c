//Accede à 2 fichiers (A et B -> S0 et S1)
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main(){
    int semid= semget(4000,2,0);
    struct sembuf s[2];
    s[0].sem_num = 0;
    s[0].sem_op = -1; //operation P()
    s[1].sem_num = 1; 
    s[1].sem_op = -1; // Operation P()
    semop(semid,s,2);
    //Accès fichiers A et B
    s[0].sem_op = 1; //Operation V()
    s[1].sem_op = 1; //Operation V()
    semop(semid,&s,2);
    exit(0);
    return 0;
}
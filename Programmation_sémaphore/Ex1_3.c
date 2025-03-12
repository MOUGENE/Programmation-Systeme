#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun {
    int val;               // Pour SETVAL
    struct semid_ds *buf;   // Pour IPC_STAT et IPC_SET
    unsigned short *array;  // Pour GETALL et SETALL
    struct seminfo *__buf;  // Pour IPC_INFO (optionnel)
};

int main(){
    // On crée 2 sémaphores
    int semid = semget(4000,2,IPC_CREAT | 0666);
    union semun s;
    s.val = 1;
    semctl(semid,0,SETVAL,s);
    semctl(semid,1,SETVAL,s);
    exit(0);
}
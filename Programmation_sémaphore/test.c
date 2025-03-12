#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun {
    int val;                  // Utilisé pour SETVAL
    struct semid_ds *buf;     // Utilisé pour IPC_STAT et IPC_SET
    unsigned short *array;    // Utilisé pour GETALL et SETALL
};


int main(){
    union semun s;
    struct sembuf t[2];
    int idIpc=semget(3700, 3, IPC_CREAT|0666);
    s.val = 3;
    semctl(idIpc, 0, SETVAL, s);
    int v = semctl(idIpc, 0, GETVAL);
    printf("Valeur de la semaphore : %d\n", v);
    t[0].sem_num = 0;
    t[0].sem_op = -1;
    t[0].sem_flg = 0;
    t[1].sem_num = 1;
    t[1].sem_op = 1;
    t[1].sem_flg = 0;
    semop(idIpc, &t, 2);
    //semctl(idIpc, 1, IPC_RMID);
    int x = semctl(idIpc,0,GETVAL);
    printf("Valeur de la semaphore : %d\n",x);
}
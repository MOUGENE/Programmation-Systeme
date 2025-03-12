//P
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <unistd.h>


union semun {
    int val;                  // Utilisé pour SETVAL
    struct semid_ds *buf;     // Utilisé pour IPC_STAT et IPC_SET
    unsigned short *array;    // Utilisé pour GETALL et SETALL
};


int main(int argc, char**argv){
    int NMAX = atoi(argv[1]);
    int S = semget(4000,NMAX+1,IPC_CREAT | 0666);
    int M = shmget(4001,2*NMAX*sizeof(float),IPC_CREAT | 0666);
    union semum se;
    se.val = 0;
    for(int i = 0; i < NMAX+1;i++){
        semctl(S,i,IPC_SET,se);
    }  
    float* mem = (float*) shmqt(M,NULL,0);
    for(int i = 0; i < NMAX;i++){
        scanf("%f",&mem[0]);
    }  
    struct sembuf SB;
    SB.sem_num = 0;
    SB.sem_op = 1;
    semop(S,&SB,1);

    for(int i = 0; i < NMAX;i++){
        SB.sem_num = i;
        SB.sem_op = -1;
        semop(S,&SB,1);
        printf("%f\n",mem[NMAX+i]);
    }
    shmdt(mem);
    shmctl(M,IPC_RMID,NULL);
    semctl(S,0,IPC_RMID,0);
    exit(0);

}
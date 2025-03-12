#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>

int main(){
    int S = semget(4000,NMAX+1,0);
    int M = shmget(4001,2*NMAX * sizeof(float),0);
    float* mem = (float*) shmat(M,NULL,0);
    struct sembuf SB;
    SB.sem_num = 0;
    SB.semop = -1;
    semop(S,&SB,1);
    for(int i = 0; i < NMAX;i++){
        men[NMAX+i] = f(men[i]);
        SB.sem_num = i+1;
        SB.sem_op = 1;
        semop(S,&SB,1);
    }
    shmdt(mem);
    exit(0);
}
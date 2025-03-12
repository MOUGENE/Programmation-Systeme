#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>


int main(){
    int shmid = shmget(4567,4*sizeof(int),IPC_CREAT | 0666);
    int *p = shmat(shmid,NULL,0);

    for(int i = 0; i < 4; i++){
        if(fork() == 0){
            p[i] = i;
            exit(0);
        }
    }

    for(int i= 0; i < 4;i++){
        wait(NULL);
    }

    for(int i= 0; i < 4;i++){
        printf("%d\t",p[i]);
    }

    shmdt(p);
    shmctl(shmid,IPC_RMID,0);
    exit(0);
}
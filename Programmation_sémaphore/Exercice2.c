#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>

int main(){
    int shmid = shmget(4001,4*sizeof(int),IPC_CREAT |0666);
    int *p = (int*)shmat(shmid,NULL,0);
    for(int i = 0;i < 4;i++){
        if(fork() == 0){
            p[i] = i;
            exit(0);
        }
    } 
    return 0;
}
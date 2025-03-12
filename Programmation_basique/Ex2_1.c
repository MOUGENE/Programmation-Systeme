#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
    int k;
    for(int i = 0;i < 10;i++){
        if((k = fork()) == 0){
            printf("index : %d,pid : %d\n",i,getpid());
            exit(0);
        }
        wait(NULL);
    }
    exit(0);
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    for(int i = 0; i < 10;i++){
        if((fork()) == 0){
            printf("processus fils : %d|%d\n",i,getpid());
            for(int j = 0; j < 10; j++){
                if((fork()) == 0){
                    printf("processus petit fils : %d|%d\n",j,getpid());
                    exit(0);
                }
            }
            for(int y = 0; y < 10;y++){
                wait(NULL);
            }
            exit(0);
        }
        wait(NULL);
    }
    return 0;
}
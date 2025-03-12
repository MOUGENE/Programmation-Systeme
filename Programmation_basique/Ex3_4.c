#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <signal.h>

int c = 0;
void handler(int s){
    c++;
    if( c >= 3){
        exit(0);
    }
}

int main(){
    signal(SIGINT,handler);
    while(1){

    }
    exit(0);
}
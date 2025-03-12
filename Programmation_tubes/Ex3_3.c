#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>

int main(int argc,char** argv){
    int T[2];
    int src;
    int lu;
    char buf[255];
    pipe(&T[0]);
    if(fork() == 0){
        close(T[1]);
        read(T[0],&lu,sizeof(int));
        while(lu != 0){
            read(T[0],&lu,sizeof(int));
            printf("%s",buf);
            read(T[0],&lu,sizeof(int));
        }
        close(T[0]);
        exit(0);
    }
    close(T[0]);
    src = open(argv[1],O_RDONLY,0);
    lu = read(src,buf,255);
    write(T[1],&lu,sizeof(int));
    while(lu!= 0){
        write(T[1],buf,lu);
        lu = read(src,buf,255);
        write(T[1],lu,sizeof(int));
    }
    wait(NULL);
    close(src);
    close(T[1]);
    exit(0);
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc,char** argv){
    char c;
    int src,dest;
    src = open(argv[1],O_RDONLY,0);
    dest = open(argv[2],O_WRONLY,0644);
    int l;
    lseek(src,-1,SEEK_END);
    read(src,&c,1);
    write(dest,&c,1);
    while(lseek(src,-2,SEEK_CUR) != 0){
        read(src,&c,1);
        write(dest,&c,1);
    }
    read(src,&c,1);
    write(dest,&c,1);
    close(src);
    close(dest);
    exit(0);
}
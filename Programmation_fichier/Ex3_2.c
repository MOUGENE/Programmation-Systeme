#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>

int main(){
    DIR* p = opendir(".");
    struct dirent *e;
    struct stat s;
    while((e = readdir(p)) != NULL){
        stat(e->d_name,&s);
        printf("Fichier %s,taille : %d, uid : %d\n",e->d_name,s.st_size,s.st_uid);
    }
    closedir(p);
    exit(0);
}
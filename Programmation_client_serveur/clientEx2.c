#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#define PORT 3000

int main(int argc, char* argv[]) {
    struct sockaddr_in s;
    socklen_t l = sizeof(s);
    int sock = socket(AF_INET,SOCK_STREAM,0);
    memset(&s,0,sizeof(s));
    s.sin_family = AF_INET;
    s.sin_port = htons(PORT);
    s.sin_addr.s_addr = inet_addr("127.0.0.1");
    connect(sock,(struct sock addr*)&s,l);
    write(sock,?,?);
    read(sock,?,?);
    printf("%s\n",?);
    close(sock);
    exit(0);
}
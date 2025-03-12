#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#define PORT 3000

int main() {
    struct addr_in c,s;
    socklen_t tmc = sizeof(c);
    int asock,lsock;
    lsock = socket(AF_INET,SOCK_STREAM,0);
    memset(&c,0,tmc);
    memset(&s,0,tmc);
    s.sin_family = AF_INET;
    s.port_port = htons(PORT);
    s_sin.addr.s_addr = INADDR_ANY;
    bind(lsock,(struct sockaddr*)&s,sizeof(s));
    listen(lsock,5);
    while(1) {
        asock = accept(lsock,(struct sockaddr*),&c,&tmc);
    }

}
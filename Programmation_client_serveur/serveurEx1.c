#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#define PORT 3000

int est_premier(int nombre) {
    if(nombre <= 1) {
        return 0; // Les nombres <= 1 ne sont pas premiers
    }
    for(int i = 2; i < nombre; i++) {
        if(nombre % i == 0) {
            return 0; // Nombre non premier
        }
    }
    return 1;
}

int main() {
    struct sockaddr_in c,s;
    int sock = socket(AF_INET,SOCK_DGRAM,0);
    int x;
    socklen_t tc = sizeof(c);
    memset(&s,0,sizeof(s));
    memset(&c,0,tc);
    s.sin_family = AF_INET;
    s.sin_port = htons(PORT);
    s.sin_addr.s_addr = INADDR_ANY;
    bind(sock,(struct sockaddr*)&s,sizeof(s));
    while(1) {
        recvfrom(sock,&x,sizeof(int),0,(struct sockaddr*)&c,&tc);
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &c.sin_addr, client_ip, INET_ADDRSTRLEN);
        printf("Reçu de %s:%d - Nombre: %d\n", client_ip, ntohs(c.sin_port), x);
        x = est_premier(x);
        sendto(sock,&x,sizeof(int),0,(struct sockaddr*)&c,tc);
    }
    close(sock);
    exit(0);
}
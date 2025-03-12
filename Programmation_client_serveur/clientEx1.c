#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#define PORT 3000

int main(int argc,char* argv[]) {
    if(argc != 2) {
        fprintf(stderr, "Erreur argument incorrect, 1 requis");
        exit(1);
    }

    struct sockaddr_in s;
    int sock = socket(AF_INET, SOCK_DGRAM,0);
    int x = atoi(argv[1]);
    printf("Entrez une valeur entiere : ");
    socklen_t ts = sizeof(s);
    memset(&s,0,ts);
    s.sin_family = AF_INET;
    s.sin_port = htons(PORT);
    s.sin_addr.s_addr = inet_addr ("127.0.0.1");
    sendto(sock,&x,sizeof(int),0,(struct sockaddr*)&s,ts);
    recvfrom(sock,&x,sizeof(int),0,(struct sockaddr*)&s,&ts);
    printf("Le nombre envoye etait %d est un nombre %s\n",atoi(argv[1]), x != 0 ? "premier" : "non premier");
    close(sock);
    exit(0);
}
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#define PORT 3000

// Code serveur version TCP

int main() {
    struct sockaddr_in c,s;
    char buf[512];
    socklen_t tc = sizeof(c);
    int asock, lsock;
    int k;

    // Création de la socket
    lsock = socket(AF_INET,SOCK_STREAM,0);
    if(lsock < 0) {
        perror("Erreur lors de la création de la socket");
        exit(EXIT_FAILURE);
    }

    // Initialisation des structures d'adresses
    memset(&c,0,tc);
    memset(&s,0,tc);
    s.sin_family = AF_INET;
    s.sin_port = htons(PORT);
    s.sin_addr.s_addr = INADDR_ANY;

    // Liaison de la socket
    if(bind(lsock,(struct sockaddr*)&s,sizeof(s)) < 0) {
        perror("Erreur lors de la liaison (bind)");
        close(lsock);
        exit(EXIT_FAILURE);
    }

    // Ecoute les connexions entrantes
    if(listen(lsock,5) < 0) {
        perror("Erreur lors de l'ecoute (listen)");
        close(lsock);
        exit(EXIT_FAILURE);
    }

    printf("Serveur en attente de connexions sur le port %d....\n",PORT);

    // Boucle pour accepter les connexions
    while(1) {
        asock = accept(lsock,(struct sockaddr*)&c,&tc);
        if(asock < 0) {
            perror("Erreur lors de l'acceptation de connexion (accept)");
            continue;
        }
        printf("Connexion acceptée de %s:%d\n", inet_ntoa(c.sin_addr), ntohs(c.sin_port));

        for(int i = 0; i < 2; i++) {
            if((k=fork()) == 0) {
                // Partie processus fils
                if(i == 0) {
                    // Processus de collecte régulière
                    close(lsock); // On n'a pas besoin de lsock ici donc on peut le fermer pour des mesures de sécurités
                    memset(buf,0,sizeof(buf)); // Permet de remettre le buffer a 0 pour éviter les données résiduelles
                    int valread = read(asock,buf,sizeof(int));
                    if(valread > 0) {
                        printf("Le processus de collecte reguliere de donnees a reçu : %d",valread);
                        // Ici on envoie une reponse au client
                        const char *response = "Message de collecte bien reçu par le processus regulier.";
                        send(asock,response,strlen(response),0);
                    }
                    close(asock);
                    exit(EXIT_SUCCESS); // Le processus de collecte de données régulières a finis son travail alors on peut le terminer
                } 
                else if (i == 1) {
                    // Processus pour les alertes urgentes
                    close(lsock);
                    memset(buf,0,sizeof(buf));
                    int valread = read(asock,buf,sizeof(int));
                    if(valread > 0) {
                        printf("Le processus de collecte d'alerte urgente de donnees a bien reçu : %d",valread);
                        const char* response = "Alerte urgente bien reçu par le processus d'alerte urgente.";
                        send(asock,responde,strlen(response),0);
                    }
                    close(asock);
                    exit(EXIT_SUCCESS);
                }
            } 
        }
        close(asock);
    }
    close(lsock);
    return 0;
}
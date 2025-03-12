#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#define PORT 3000

// Fonction des données de collecte reçu par le serveur
int collecte_donnees() {
    return rand() % 50;
}

// Code client version TCP
int main() {
    struct sockaddr_in c;
    socklen_t l = sizeof(c);
    int sock = socket(AF_INET,SOCK_STREAM,0);
    char buf[512];
    int n;

    // Initialise la graine de génération aléatoire
    srand(time(NULL));

    // Creation de la socket
    if(sock < 0) {
        perror("Erreur lors de la creation de la socket.");
        exit(EXIT_FAILURE);
    }
    
    // Configuration de l'adresse du serveur
    memset(&c,0,sizeof(c));
    s.sin_family = AF_INET;
    s.sin_port = htons(PORT);
    if(inet_pton(AF_INET,"127.0.0.1", &c.sin_addr) <= 0) {
        perror("Adresse IP invalide ou non supportee.");
        exit(EXIT_FAILURE);
    }

    // Connexion au serveur
    if(connect(sock, (struct sockaddr*)&c,sizeof(c)) < 0) {
        perror("Erreur de connexion au serveur.");
        close(sock);
        exit(EXIT_FAILURE);
    }
    printf("Connecte au serveur sur le port %d. \n",PORT);

    // Boucle d'envoi périodique de données au serveur
    while(1) {
        // Génère un niveau d'alerte
        n = collecte_donnees();
        sprintf(buf,"%d",n); // Convertit la données en chaîne de caractères
        // Envoie le niveau d'alerte au serveur
        send(sock,buffer,strlen(buffer),0);
        printf("Niveau d'alerte envoye au serveur : %d\n",n);

        // Simuler un délai avant d'envoyer la prochaine collecte de données
        sleep(20);
    }

    // Fermeture de la socket, normalement ce code n'atteint jamais ce niveau pour cause de la boucle infinie
    close(sock);
    return 0;
}

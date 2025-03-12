#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    if(argc != 2) {
        printf("Il manque des paramètres");
        exit(1);
    }

    int n = atoi(argv[1]); // Nombre de processus
    int pipes[n][2]; // Tableau de tubes
    int k;

    // Création des tubes
    for(int i = 0; i < n; i++) {
        // Test si pipe() à échouer
        if(pipe(pipes[i]) == -1) {
            perror("pipe");
            exit(1);
        }
    }

    for(int i = 0; i < n; i++) {
        if((k=fork()) == 0) {
            // Test si fork() à échouer
            if(k == -1) {
                perror("fork");
                exit(1);
            }

            // Processus fils
            char message[512];
            int prev = i == 0 ? n - 1 : i - 1; // Le processus précédent
            int next = i; // Le processus suivant

            // On ferme les tubes non utilisé
            for(int j = 0; j < n; j++) {
                if(j != prev){
                    close(pipes[j][0]); // On ferme toutes les entrées sauf celles du tubes précédent
                }
                if(j != next) {
                    close(pipes[j][1]); // On ferme toutes les sorties sauf celles du suivants
                }
            }

            // On lis depuis le processus précédent
            read(pipes[prev][0], message,sizeof(message));

            // printf("%s\n",message);

            // On affiche le message reçu 
            printf("Processus %d, pid : %d a reçu le message : '%s' \n",i + 1,getpid(),message);

            // Modifier le message et l'envoyer au prochain processus
            snprintf(message,sizeof(message),"Message du processus %d",i + 1);
            write(pipes[next][1],message,sizeof(message));

            // On ferme les tubes restants
            close(pipes[prev][0]);
            close(pipes[next][1]);
            
            // Fin du  processus fils
            exit(0);
        }
    }

    // Processus père
    char init_message[256] = "Message initial";

    // Envoie le message au premier processus
    write(pipes[0][1],init_message,sizeof(init_message));

    // On ferme tout les tubes dans le processus père
    for(int i = 0; i < n; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    // On attend que tous les processus fils se terminent
    for(int i = 0; i < n; i++) {
        wait(NULL);
    }

    return 0;
}
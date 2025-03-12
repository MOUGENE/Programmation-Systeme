#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {

    int semid = semget(4000,1,0); // Créer le jeux de sémpaphore

    for(int i = 0; i < 5; i++) {
        // On attend l'opération P
        struct sembuf s;
        s.sem_num = 0;
        s.sem_op = -1; // Décrémenter le sémaphore
        semop(semid,&s, 1);

        // Section critique
        printf("Processus 1 : %d\n", i);
        sleep(1); // Simule une tâche

        // Signaler (opération V)
        s.sem_num = 1;
        s.sem_op = 1; // Incrémente le sémaphore
        semop(semid,&s,1);
        sleep(1);
    }
    return 0;
}
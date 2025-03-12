#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

int main() {
    int semid = semget(4000,2,0);

    for(int i = 0; i < 5; i++) {
        // On attend l'opération P
        struct sembuf s;
        s.sem_num = 1;
        s.sem_op = -1; // Décrémente le sémaphore de 1
        semop(semid,&s,1);

        // Section critique
        printf("Processus 2 : %d\n", i);
        sleep(1); // Simuler une tâche

        // Opération V
        s.sem_num = 0;
        s.sem_op = 1; // Incrémenter le sémaphore
        semop(semid,&s,1);
        sleep(1);
    }
    return 0;
}
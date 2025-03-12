#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

int main(void) {
    int semid = semget(4000,2, 0666 | IPC_CREAT); // Initialise un jeux de deux sémaphores

    // Initialise le premier sémaphore a 1
    semctl(semid,0,SETVAL,1);

    // Initialise le deuxième sémaphore a 0
    semctl(semid,1,SETVAL,0);

    printf("Sémaphores initialises : Sem0 = 1, Sem1 = 0\n");

    return 0;

    // ipcs -s pour voir les sémaphores
    // ipcrm -s <semid> pour supprimer les sémaphores
}

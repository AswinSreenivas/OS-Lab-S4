#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_SIZE 1024

int main() {
    int shmid;
    key_t key;
    char *shm, *s;

    // Generate a unique key for the shared memory segment
    key = ftok(".", 'a');

    // Create the shared memory segment
    shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);

    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    // Attach to the shared memory segment
    shm = shmat(shmid, NULL, 0);

    if (shm == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    // Write a message to the shared memory segment
    strcpy(shm, "Hello, world!");

    // Read from the shared memory segment and print the message
    for (s = shm; *s != '\0'; s++) {
        putchar(*s);
    }
    putchar('\n');

    // Detach from the shared memory segment
    shmdt(shm);

    // Remove the shared memory segment
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}

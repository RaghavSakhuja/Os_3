#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>
#include <semaphore.h>
#include <stdbool.h>


int main(){
    sem_t *semaphore;
    semaphore = sem_open("/sem",0);

    sem_unlink("/sem");
    perror("sem_unlink");
    sem_close(semaphore);
    perror("sem_close");
}
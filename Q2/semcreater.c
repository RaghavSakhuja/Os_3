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
    
    unsigned int sem=1;
    sem_t *semaphore;
    semaphore = sem_open("/sem",O_CREAT ,0777,sem);
    perror("sem_creation");

}
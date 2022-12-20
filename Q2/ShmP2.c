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

#define ll long long
#define p(a) printf("%s\n",a)
#define pi(a) printf("%d ",a)
#define pd(a) printf("%f\n",a)
#define fr(i,n) for(int i=0;i<n;i++)

int main(){
    key_t shm_key;
    shm_key = ftok("a.txt",65);
    sem_t *semaphore;
    int shm_id;
    int n=50;
    int finalval=0;
    char reader[50];
    int alpha=9;
    char x[alpha];
    char y[]="--end--";
    bool toread=true;
    

    sleep(1);
    semaphore = sem_open("/sem",0);
    perror("sem_open p2");


    shm_id = shmget(shm_key,1024,0666 | IPC_CREAT);
    perror("shmget");

    char* shm_addr=(char*)shmat(shm_id,NULL,0);


    sleep(1);
    fr(fuck,50)
    {   
        // pi(fuck);
        // p(" index in p2");
        if(toread){
            sem_wait(semaphore);
            // p("semaphore locked p21");
            fr(i,alpha){
                x[i]=shm_addr[i];
            }
            x[9]='\0';
            // p(x);
            if(!strcmp(x,"--start--")){
                // p("start found");
                fr(i,50){
                    reader[i]=shm_addr[i+alpha];
                }
                printf("recieved %s\n",reader);
                finalval=shm_addr[49+alpha]-'0';
                // pi(finalval);
                // pi(50+alpha);
                // p("finalval");
                toread=!toread;
            }
            sem_post(semaphore);
            // p("semaphore unlocked p21");
            sleep(1);
        }
        else{
            sem_wait(semaphore);
            // p("semaphore locked p22");
            fr(i,7){
                shm_addr[i]=y[i];
            }
            // pi(finalval);
            shm_addr[7]=finalval+'0';
            shm_addr[8]='\0';
            printf("finalval is %d, sending %s to p1\n",finalval,shm_addr);
            sem_post(semaphore);
            toread=!toread;
            // p("semaphore unlocked p22");
            sleep(1);
            if(finalval==n-1){
                p("sent acknoledgement for all");
                break;
            }
        }
    }


}

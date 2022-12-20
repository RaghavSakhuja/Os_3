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
#define frk(i,k,n) for(int i=k;i<n;i++)
#define abs(a) (a<0)?(-a):(a)
#define min(a,b) (a<b)?(a):(b)

int main(){
    key_t shm_key;
    shm_key = ftok("a.txt",65);
    sem_t *semaphore;
    char startchecker[]="--start--";
    int alpha=9;
    int shm_id;
    char endchecker[7];
    bool towrite=true;
    int finalval=-1;
    int n=50;
    char chararr[n][10];


    semaphore = sem_open("/sem",0);
    perror("sem_open p1");


    shm_id = shmget(shm_key,1024,0666 | IPC_CREAT);
    perror("shmget");


    char* shm_addr=(char*)shmat(shm_id,NULL,0);


    //generating random strings
    srand(time(NULL));
    fr(i,n){
        fr(j,9){
            int size = rand();  
            char a=abs((size%25))+97;
            chararr[i][j]=a;
        }
        chararr[i][9]=i+'0';
        char x[10];
        fr(j,10){
            x[j]=chararr[i][j];
        }
        p(x);
    }
    sleep(1);
    fr(fuck,50){
        // pi(fuck);
        // p(" index in p1");
        if(towrite){
            sem_wait(semaphore);
            // printf("fucking bullshirt, %d, %d\n",finalval,n);
            // p("semaphore locked p11");
            fr(i,alpha){
                shm_addr[i]=startchecker[i];
            }
            int d=min(finalval+1+5,n);
            // printf("starting at %d, ending at %d\n",finalval+1,d);

            frk(i,finalval+1,d){
                fr(j,10){
                    shm_addr[(i-finalval-1)*10+j+alpha]=chararr[i][j];
                }
            }
            towrite=!towrite;
            printf("send %s\n",shm_addr);
            sem_post(semaphore);
            // p("semaphore unlocked p11");
            sleep(1);
        }
        else{
            sem_wait(semaphore);
            // p("semaphore locked p12");
            // p(shm_addr);
            fr(i,7){
                endchecker[i]=shm_addr[i];
            }
            endchecker[7]='\0';
            // p(endchecker);
            if(!strcmp(endchecker,"--end--")){
                p("end found");
                finalval=shm_addr[7]-'0';
                // pi(finalval);
                // p("finalval recieved at p1");
                towrite=!towrite;
                if(finalval==n-1){
                    p("Recieved acknowledgemnet for all");
                    break;
                }
            }
            sem_post(semaphore);
            // p("semaphore unlocked p12");
            sleep(1);
        }
    }
    shmdt(shm_addr);
    perror("shmdt"); 
    shmctl(shm_id, IPC_RMID, NULL); 
    perror("shmctl");
}

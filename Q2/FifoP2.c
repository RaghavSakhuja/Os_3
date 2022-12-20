#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#define ll long long
#define p(a) printf("%s\n",a)
#define pi(a) printf("%d ",a)
#define pd(a) printf("%f\n",a)
#define fr(i,n) for(int i=0;i<n;i++)

int main(int argc, char* argv[]){
    int fd=open("sender",O_RDONLY);
    int fd1=open("reciever",O_WRONLY);
    perror("opening");
    p("recieving...");
    int n=50;
    int i=0;
    while(i<n-1){
        fr(k,5){
            char x[10];
            read(fd,&x,sizeof(x));
            // perror("read");
            read(fd,&i,sizeof(i));
            // perror("read");
            // p(x);
            pi(i);
            if(i==(n-1)){
                break;
            }
            // pi(j);
        }
        pi(i);
        p("sent");
        write(fd1,&i,sizeof(i));
    }
    close(fd);
    perror("close");
}

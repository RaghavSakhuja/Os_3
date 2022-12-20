#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

#define ll long long
#define p(a) printf("%s\n",a)
#define pi(a) printf("%d ",a)
#define pd(a) printf("%f\n",a)
#define fr(i,n) for(int i=0;i<n;i++)
#define min(a,b) (a<b)?a:b 


int main(int argc, char* argv[]){
    srand(time(NULL));
    int n=50;
    char chararr[n][10];
    fr(i,n){
        fr(j,10){
            int size = rand();  
            char a=abs((size%25))+97;
            chararr[i][j]=a;
        }
        char x[10];
        fr(j,10){
            x[j]=chararr[i][j];
        }
        p(x);
    }

    int fd=open("sender",O_WRONLY);
    int fd1=open("reciever",O_RDONLY);
    perror("opening");
    p("sending...");
    int i=0;
    while(i<n-1){
    // fr(i,n){
        int d=min(i+5,n);
        // pi(d);
        // p("upper");
        for(int k=i;k<d;k++){
            char x[10];
            int l=k;
            fr(j,10){
                x[j]=chararr[l][j];
            }
            write(fd,&x,sizeof(x));
            write(fd,&l,sizeof(l));
            pi(l);
            p("sent");
        }
        read(fd1,&i,sizeof(i));
        pi(i);
        char x[10];
        fr(j,10){
            x[j]=chararr[i][j];
        }
        p(x);
    }
    close(fd);
    perror("close");

}

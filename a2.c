#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define ll long long
#define p(a) printf("%s\n",a)
#define pi(a) printf("%d ",a)
#define pd(a) printf("%f\n",a)
#define fr(i,n) for(int i=0;i<n;i++)
#define min(a,b) (a<b)?a:b 

int PhiloState[5];
int philo[5] = { 0, 1, 2, 3, 4 };

int semval[5]={1,1,1,1,1};

sem_t acces;
sem_t chopsticks[5];

void* philosopher(void* num)
{
	int* i = num;
	int philonum = *i;
    int left = philonum;
    int right = (philonum+1)%5;
    int j=0;
    while (1)
    {
        sleep(5);
        for(int i=0;i<5;i++){
            sem_getvalue(&chopsticks[i],semval+i);
        }
        int a=semval[0]+semval[1]+semval[2]+semval[3]+semval[4];
        printf("Philosopher %d is thinking\n",philonum);
        sem_wait(&acces);
        sem_wait(&chopsticks[left]);
        printf("Philosopher %d took %d\n",philonum,left);
        sem_wait(&chopsticks[right]);
        printf("Philosopher %d took %d\n",philonum,right);
        sem_post(&acces);
        printf("Philosopher %d is eating\n",philonum);
        sleep(1);
        j++;
        sem_post(&chopsticks[right]);
        printf("Philosopher %d put %d\n",philonum,right);
        sem_post(&chopsticks[left]);
        printf("Philosopher %d put %d\n",philonum,left);
        sleep(1);
        // printf("Philosopher %d ate\n",philonum);
    }
    printf("Philosopher %d left table\n",philonum);
}

int main()
{
	int i;
	pthread_t pid[5];
	// initialize the semaphores
	sem_init(&acces, 0, 1);

	for (i = 0; i < 5; i++){
		sem_init(&chopsticks[i], 0, semval[i]);
    }
	for (i = 0; i < 5; i++) {
		pthread_create(&pid[i], NULL,philosopher, &philo[i]);
        sem_getvalue(&chopsticks[i],semval+i);
        // int a=semval[0]+semval[1]+semval[2]+semval[3]+semval[4];
		// printf("Philosopher %d is thinking and eating count is:%d\n", i + 1,a);
	}
	for (i = 0; i < 5; i++){
		pthread_join(pid[i], NULL);

    }
}

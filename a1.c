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

pthread_mutex_t chopsticks[5];

void* philosopher(void* num)
{
	int* i = num;
	int philonum = *i;
    int left = philonum;
    int right = (philonum+1)%5;
    int j=0;
    while (1)
    {
        printf("Philosopher %d is thinking\n",philonum);
        if(philonum==0){
            pthread_mutex_lock(&chopsticks[left]);
            pthread_mutex_lock(&chopsticks[right]);
            printf("Philosopher %d is eating\n",philonum);
            sleep(1);
            j++;
            pthread_mutex_unlock(&chopsticks[right]);
            pthread_mutex_unlock(&chopsticks[left]);
            sleep(1);
        }
        else{
            pthread_mutex_lock(&chopsticks[right]);
            pthread_mutex_lock(&chopsticks[left]);
            printf("Philosopher %d is eating\n",philonum);
            sleep(1);   
            j++;
            pthread_mutex_unlock(&chopsticks[left]);
            pthread_mutex_unlock(&chopsticks[right]);
            sleep(1);

        }
    }
    printf("Philosopher %d left table\n",philonum);
    
}

int main()
{
	int i;
	pthread_t pid[5];
	// initialize the semaphores
	for (i = 0; i < 5; i++){
        pthread_mutex_init(&chopsticks[i], NULL);
    }
	for (i = 0; i < 5; i++) {
		pthread_create(&pid[i], NULL,philosopher, &philo[i]);
		printf("Philosopher %d is thinking\n", i + 1);
	}
	for (i = 0; i < 5; i++){
		pthread_join(pid[i], NULL);
        pthread_mutex_destroy(&chopsticks[i]);
    }
}

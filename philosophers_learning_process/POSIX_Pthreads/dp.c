#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct vars
{
	int id;
}	t_dp;
#define NUMTHRDS 5
t_dp dp[NUMTHRDS]; 
pthread_t callThd[NUMTHRDS];
pthread_mutex_t mutexsum[NUMTHRDS];

void philosopher(void *philo)
{
	pthread_mutex_lock(&mutexsum);
		(t_dp)dp[0].id = 0;
	pthread_mutex_unlock(&mutexsum);
}
int main()
{
	int i;

	i = 0;
	for(i=0;i<NUMTHRDS;i++)
		pthread_mutex_init(&mutexsum[i],NULL);
	for(i=0;i<NUMTHRDS;i++)
		pthread_create(&callThd[i], NULL, philosopher, (void *)&dp[i]); 
}


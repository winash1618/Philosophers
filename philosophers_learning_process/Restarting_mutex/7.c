
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

void *philosopher (void *id);

typedef struct common_data
{
	int pno;
	size_t ttd;
	size_t tte;
	size_t tts;
	int tt;
	int e_max;
	pthread_mutex_t *fork;
	pthread_mutex_t task;
}	t_data;

typedef struct philo
{
	int id;
	size_t starvation_time;
	int eating;
	int thinking;
	int sleeping;
	pthread_t phi_t;
	t_data *s;
}	t_phi;

int main()
{
	t_phi *phi;

	phi = malloc(sizeof(t_phi) * 5);
	t_data *data;

	data  = malloc(sizeof(t_data));
	data->pno = 5;
	data->ttd = 800;
	data->tte = 200;
	data->tts = 400;
	pthread_mutex_init(&data->task, NULL);
	data->fork = malloc(sizeof(pthread_mutex_t) * 5);
	int i = 0;
	while (i < 5)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
	i = 0;
	while (i < 5)
	{
		phi[i].id = i;
		phi[i].s = data; 
		i++;
	}
	i = 0;
	while (i < 5)
	{
		printf("%d %p \n", phi[i].id, &phi[i].s->fork[i]);
		i++;
	}
	i = 0;
	while (i < 5)
	{
		pthread_create (&phi[i].phi_t, NULL, philosopher, (void *)&phi[i]);
		i++;
	}
	i = 0;
	while (i < 5)
	{
		pthread_join (phi[i].phi_t, NULL);
	}
}
size_t get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, 0);
	return((tv.tv_sec*1000 + tv.tv_usec/1000));
}

size_t time_event(t_phi *new, size_t ptime)
{
	size_t	time;
	int i;

	time = get_time();
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&new->s->task);
			if (get_time() - time >= ptime)
				break;
		pthread_mutex_unlock(&new->s->task);
		usleep(100);
	}
	return (get_time() - time);
}

void lock_stick(t_phi *phi, t_data *data)
{
	pthread_mutex_lock(&data->task);
	pthread_mutex_lock(&data->fork[phi->id]);
	pthread_mutex_lock(&data->fork[(phi->id + 1) % (data->pno)]);
	pthread_mutex_unlock(&data->task);
	printf("Philosopher %d: took stick %d and %d \n",phi->id,  phi->id, (phi->id + 1) % (data->pno));
}
void unlock_stick(t_phi *phi, t_data *data)
{
	pthread_mutex_unlock(&data->fork[phi->id]);
	printf ("Philosopher %d: drop %s stick %d\n", phi->id, "right", phi->id);
	pthread_mutex_unlock(&data->fork[(phi->id + 1) % (data->pno)]);
	printf ("Philosopher %d: drop %s stick %d\n", phi->id, "left", (phi->id + 1) % (data->pno));
}
void *philosopher (void *phi)
{
	t_phi *phi1 = (t_phi *)phi;
	t_data *data = phi1->s;
	size_t time;

	while (1)
	{
		lock_stick(phi1, data);
		printf ("Philosopher %d: eating.\n", phi1->id);
		// usleep (800000);
		time = data->tte;
		time_event(phi1, time);
		unlock_stick(phi1, data);
		printf("%d started sleeping \n", phi1->id);
		usleep(200000);
		// time_event(phi1, data->tts);
		printf("%d end sleeping \n", phi1->id);
		printf("%d started thinking \n", phi1->id);
	}
	printf ("Philosopher %d is done eating.\n", phi1->id);
	return (NULL);
}

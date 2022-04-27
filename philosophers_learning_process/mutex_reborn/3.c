
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include "libft/ft_printf/ft_printf.h"

void *philosopher (void *id);

typedef struct common_data
{
	int pno;
	size_t ttd;
	size_t tte;
	size_t tts;
	size_t tt;
	int e_max;
	pthread_mutex_t *fork;
	pthread_mutex_t task;
	pthread_mutex_t task2;
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
	data->tt = 0;
	pthread_mutex_init(&data->task, NULL);
	pthread_mutex_init(&data->task2, NULL);
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
		printf("%d %p %p\n", phi[i].id, &phi[i].s->fork[i], &phi[i].s->task);
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

size_t time_event(t_data *data, size_t ptime)
{
	size_t	time;

	time = get_time();
	while (1)
	{
		usleep(100);
		if (get_time() - time >= ptime)
			break;
		
	}
	return (get_time() - time);
}

void lock_stick(t_phi *phi, t_data *data)
{
	pthread_mutex_lock(&data->task);
	pthread_mutex_lock(&data->fork[phi->id]);
	ft_printf("%d %d has taken a fork\n", (int)data->tt, phi->id);
	pthread_mutex_lock(&data->fork[(phi->id + 1) % (data->pno)]);
	ft_printf("%d %d has taken a fork\n", (int)data->tt, phi->id);
	ft_printf("%d %d is eating\n", (int)data->tt, phi->id);
	pthread_mutex_unlock(&data->task);
}
void unlock_stick(t_phi *phi, t_data *data)
{
		
	
	pthread_mutex_unlock(&data->fork[phi->id]);
	pthread_mutex_unlock(&data->fork[(phi->id + 1) % (data->pno)]);
	pthread_mutex_lock(&data->task);
		ft_printf("%d %d is sleeping \n", (int)data->tt, phi->id);
	pthread_mutex_unlock(&data->task);
	

}
void *philosopher (void *phi)
{
	t_phi *phi1 = (t_phi *)phi;
	t_data *data = phi1->s;

	while (1)
	{
		lock_stick(phi1, data);
		data->tt += time_event(data, data->tte);
		unlock_stick(phi1, data);
		data->tt += time_event(data, data->tts);
		pthread_mutex_lock(&data->task);
		ft_printf("%d %d is thinking \n", (int)data->tt, phi1->id);
		pthread_mutex_unlock(&data->task);
	}
	printf ("Philosopher %d is done eating.\n", phi1->id);
	return (NULL);
}

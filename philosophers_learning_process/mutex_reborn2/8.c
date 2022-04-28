// added time variable in lock_stick and unlock_stick

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
	pthread_mutex_t *task;
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
	data->tts = 200;
	data->tt = 0;
	int i = 0;
	data->task = malloc(sizeof(pthread_mutex_t) * 10);
	while (i < 10)
	{
		pthread_mutex_init(&data->task[i], NULL);
		i++;
	}
	data->fork = malloc(sizeof(pthread_mutex_t) * 5);
	i = 0;
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
		printf("%d %p %p\n", phi[i].id, &phi[i].s->fork[i], &phi[i].s->task[i]);
		i++;
	}
	i = 0;
	while (i < 5)
	{
		pthread_create (&phi[i].phi_t, NULL, philosopher, (void *)&phi[i]);
		usleep(300);
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
void check_death(t_data *data, size_t time_after, size_t time_before)
{
	if (time_after - time_before >= data->ttd)
		exit(1);
}
size_t time_event(t_data *data, size_t ptime, size_t t)
{
	size_t	time;

	time = get_time();
	while (1)
	{
		usleep(100);
		if (check_death(data, get_time(), t),get_time() - time >= ptime)
			break;
	}
	return (get_time() - time);
}

void lock_stick(t_data *data, int left_fork, int right_fork)
{
	size_t time;
	if (left_fork % 2 != 0)
	{
		pthread_mutex_lock(&data->fork[right_fork]);
		pthread_mutex_lock(&data->fork[left_fork]);
	}
	else
	{
		pthread_mutex_lock(&data->fork[left_fork]);
		pthread_mutex_lock(&data->fork[right_fork]);
	}
	pthread_mutex_lock(&data->task[3]);
	time = data->tt;
	pthread_mutex_unlock(&data->task[3]);
	pthread_mutex_lock(&data->task[2]);
	ft_printf("%d %d has taken a fork\n", (int)time, left_fork);
	ft_printf("%d %d has taken a fork\n", (int)time, left_fork);
	ft_printf("%d %d is eating\n", (int)time, left_fork);
	pthread_mutex_unlock(&data->task[2]);
}
void unlock_stick(t_data *data, int left_fork, int right_fork)
{
	size_t time;
	if (left_fork % 2 != 0)
	{
	pthread_mutex_unlock(&data->fork[right_fork]);
	pthread_mutex_unlock(&data->fork[left_fork]);
	}
	else
	{
		pthread_mutex_unlock(&data->fork[left_fork]);
		pthread_mutex_unlock(&data->fork[right_fork]);
	}
	pthread_mutex_lock(&data->task[3]);
	time = data->tt;	
	pthread_mutex_unlock(&data->task[3]);
	pthread_mutex_lock(&data->task[2]);
	ft_printf("%d %d is sleeping \n", (int)time, left_fork);
	pthread_mutex_unlock(&data->task[2]);
	
}

void *philosopher (void *phi)
{
	int left_fork;
	int right_fork;
	size_t time;
	size_t t;
	size_t tot;
	tot = 0;
	t= get_time();
	t_phi *phi1 = (t_phi *)phi;
	t_data *data = phi1->s;
	while (1)
	{
		left_fork = phi1->id;
		right_fork = (phi1->id + 1) % (data->pno);
		lock_stick(data, left_fork, right_fork);
		check_death(data, get_time(), t);
		time = time_event(data, data->tte, t);
		t = get_time();
		pthread_mutex_lock(&data->task[3]);
		data->tt += time;
		pthread_mutex_unlock(&data->task[3]);
		unlock_stick(data, left_fork, right_fork);
		time = time_event(data, data->tts, t);
		pthread_mutex_lock(&data->task[3]);
		data->tt += time;
		time = data->tt;
		pthread_mutex_unlock(&data->task[3]);
		pthread_mutex_lock(&data->task[2]);
		ft_printf("%d %d is thinking \n", (int)time, phi1->id);
		pthread_mutex_unlock(&data->task[2]);
	}
	printf ("Philosopher %d is done eating.\n", phi1->id);
	return (NULL);
}

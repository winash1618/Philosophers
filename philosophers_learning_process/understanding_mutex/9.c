#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct super
{
	int pno;
	int ttd;
	int tte;
	int tts;
	int tt;
	int e_max;
	pthread_mutex_t *fork;
	pthread_mutex_t task;
}	t_sup;

typedef struct philo
{
	int id;
	int eating;
	int thinking;
	int sleeping;
	pthread_t phi_t;
	t_sup *s;
}	t_phi;

size_t get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, 0);
	return((tv.tv_sec*1000 + tv.tv_usec/1000));
}

size_t sleeper(t_phi *new)
{
	size_t	time;
	int i;

	time = get_time();
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&new->s->task);
		if (get_time() - time >= new->s->tts)
			break;
		pthread_mutex_unlock(&new->s->task);
		usleep(100);
	}
	return (get_time() - time);
}

size_t eater(t_phi *new)
{
	size_t	time;
	int i;

	time = get_time();
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&new->s->task);
		if (get_time() - time >= new->s->tte)
			break;
		pthread_mutex_unlock(&new->s->task);
		usleep(100);
	}
	return (get_time() - time);
}
void lock_forks(t_phi *new, t_sup *data)
{
	pthread_mutex_lock(&data->task);
		pthread_mutex_lock(&data->fork[new->id]);
		pthread_mutex_lock(&data->fork[(new->id + 1) % (data->pno + 1)]);
	pthread_mutex_unlock(&data->task);
}
void unlock_forks(t_phi *new, t_sup *data)
{
	pthread_mutex_lock(&data->task);
		pthread_mutex_unlock(&data->fork[new->id]);
		pthread_mutex_unlock(&data->fork[(new->id + 1) % (data->pno + 1)]);
	pthread_mutex_unlock(&data->task);
}
void p_eat(t_phi *new, t_sup *data)
{
	int time;
	pthread_mutex_lock(&data->task);
		time = get_time();
		printf("%dms philosopher %d started eating \n", data->tt, new->id);
		sleeper(new);
		data->tt += get_time() - time;
		printf("%dms philosopher %d ended eating \n", data->tt, new->id);
	pthread_mutex_unlock(&data->task);
}
void p_sleep(t_phi *new, t_sup *data)
{
	int time;
	pthread_mutex_lock(&data->task);
		time = get_time();
		printf("%dms philosopher %d started sleeping \n", data->tt, new->id);
		sleeper(new);
		data->tt += get_time() - time;
		printf("%dms philosopher %d ended sleeping \n", data->tt, new->id);
	pthread_mutex_unlock(&data->task);
}
void *philosopher_cycle(void *phi)
{
	t_phi *new = (t_phi *)phi;
	t_sup *data = (t_sup *)new->s;

	while(1)
	{
		lock_forks(new, data);
		p_eat(new, data);
		unlock_forks(new, data);
		p_sleep(new, data);
		
	}
	// size_t time;
	// time =get_time();

	// pthread_mutex_lock(&new->s->fork[new->id]);
	// pthread_mutex_lock(&new->s->fork[(new->id + 1) % (new->s->pno + 1)] );
	// printf("%d \n", new->id);
	// printf("timestamp_in_ms %d start %d eating\n", new->id, (new->id + 1) % (new->s->pno + 1));
	// // new[new->id].eating = 1;
	// // new[new->id].sleeping =0;
	// // new[new->id].thinking =0;
	// sleeper(new);
	// // printf("%d \n", new->id);
	// new->s->tt += get_time() - time;
	// // printf("%d \n", new[new->id].s->tt);
	// // printf("%lu \n", get_time() - time);
	// printf("timestamp_in_ms %d end %d eating\n", new->id, (new->id + 1) % (new->s->pno + 1));
	// pthread_mutex_unlock(&new->s->fork[(new->id + 1) % (new->s->pno + 1)]);
	// pthread_mutex_unlock(&new->s->fork[new->id]);
	// return (NULL);
}

// void *p_sleep(void *phi)
// {
// 	t_phi *new = (t_phi *)phi;
// 	size_t time;
// 	time =get_time();
// 	// printf("%p \n", &new->s->fork[new->id]);
// 	pthread_mutex_lock(&new->s->sleeping[new->id]);
// 	printf("timestamp_in_ms %d start sleeping\n", new->id);
// 	new[new->id].sleeping = 1;
// 	new[new->id].eating = 0;
// 	new[new->id].thinking = 0;
// 	sleeper(new);
// 	new[new->id].s->tt += get_time() - time;
// 	printf("timestamp_in_ms %d end sleeping\n", new->id);
// 	pthread_mutex_unlock(&new->s->sleeping[new->id]);
	
// 	return (NULL);
// }

// int died(int id, t_phi *phi)
// {
// 	// printf("%d %d\n", phi[id].s->tt, id);
// 	if(phi[id].s->tt > 800)
// 		exit(1);
// 	return (0);
// }

// int sleeping(int id, t_phi *phi)
// {
// 	if(phi[id].sleeping == 1)
// 		return (1);
// 	return (0);
// }

// int eating(int id, t_phi *phi)
// {
// 	if (phi[id].eating == 1)
// 		return (1);
// 	return (0);
// }

// int thinking(int id, t_phi *phi)
// {
// 	if (phi[id].thinking == 1)
// 		return (1);
// 	return (0);
// }

void philos(t_phi *phi, t_sup *new)
{
	int i;

	i = 0;
	while (i < phi->s->pno)
	{
		pthread_create(&phi[i].phi_t, NULL, philosopher_cycle, (void *)&phi[i]);
		//pthread_create(&phi[i].phi_t, NULL, p_sleep, (void *)&phi[i]);
		i++;
	}
	while (i < phi->s->pno)
		pthread_join(phi[i++].phi_t,NULL);
	
}

void init_phi(t_phi *phi, t_sup *new)
{
	int i;

	i = 0;
	while (i < 5)
	{
		phi[i].id = i;
		phi[i].s = new;
		phi[i].sleeping = 0;
		phi[i].thinking = 0;
		phi[i].eating = 0;
		pthread_mutex_init(&new->fork[i],NULL);
		i++;
	}
	while (1)
	{
		philos(phi, new);
		
	}
	
}

void init_sup(t_sup *new)
{
	new->pno = 5;
	new->e_max = 3;
	new->ttd = 400;
	new->tte = 100;
	new->tts = 100;
	new->tt = 0;
	new->fork = malloc(sizeof(pthread_mutex_t)*5);
	t_phi *phi;
	phi = malloc(sizeof(t_phi) * 5);
	init_phi(phi, new);
}

int main()
{
	t_sup *new;

	new = malloc(sizeof(t_sup));
	init_sup(new);
}

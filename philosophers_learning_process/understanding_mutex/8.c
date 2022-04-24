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
void *p_eat(void *phi)
{
	t_phi *new = (t_phi *)phi;
	size_t time;
	time =get_time();
	// printf("%p \n", &new->s->fork[new->id]);
	pthread_mutex_lock(&new->s->fork[new->id]);
	pthread_mutex_lock(&new->s->fork[(new->id + 1) % (new->s->pno + 1)] );
	printf("timestamp_in_ms %d start %deating\n", new->id, (new->id + 1) % (new->s->pno + 1));
	new[new->id].eating = 1;
	new[new->id].sleeping =0;
	new[new->id].thinking =0;
	sleeper(new);
	// printf("%d \n", new[new->id].s->tt);
	// printf("%lu \n", get_time() - time);
	printf("timestamp_in_ms %d end %d eating\n", new->id, (new->id + 1) % (new->s->pno + 1));
	pthread_mutex_unlock(&new->s->fork[(new->id + 1) % (new->id + 1) % (new->s->pno + 1)]);
	pthread_mutex_unlock(&new->s->fork[new->id]);
	return (NULL);
}

void *p_sleep(void *phi)
{
	t_phi *new = (t_phi *)phi;
	size_t time;
	time =get_time();
	// printf("%p \n", &new->s->fork[new->id]);
	pthread_mutex_lock(&new->s->fork[new->id]);
	printf("timestamp_in_ms %d start sleeping\n", new->id);
	new[new->id].sleeping = 1;
	new[new->id].eating = 0;
	new[new->id].thinking = 0;
	sleeper(new);
	new[new->id].s->tt += get_time() - time;
	printf("timestamp_in_ms %d end sleeping\n", new->id);
	pthread_mutex_unlock(&new->s->fork[new->id]);
	
	return (NULL);
}

int died(int id, t_phi *phi)
{
	// printf("%d %d\n", phi[id].s->tt, id);
	if(phi[id].s->tt > 800)
		exit(1);
	return (0);
}

int sleeping(int id, t_phi *phi)
{
	if(phi[id].sleeping == 1)
		return (1);
	return (0);
}

int eating(int id, t_phi *phi)
{
	if (phi[id].eating == 1)
		return (1);
	return (0);
}

int thinking(int id, t_phi *phi)
{
	if (phi[id].thinking == 1)
		return (1);
	return (0);
}

void philos(t_phi *phi)
{
	int i = 0;
	while (i < phi->s->pno)
	{
		if (!died(phi[i].id, phi) && sleeping(phi[i].id, phi))
		{
			pthread_create(&phi[i].phi_t, NULL, p_eat, (void *)&phi[i]);
		}
		else if (!died(phi[i].id, phi) && !eating(phi[i].id, phi))
		{
			pthread_create(&phi[i].phi_t, NULL, p_sleep, (void *)&phi[i]);
		}
		else
		{
			pthread_create(&phi[i].phi_t, NULL, p_eat, (void *)&phi[i]);
			phi[i].thinking = 1;
		}
			i++;
		pthread_join(phi[i].phi_t,NULL);
	}
	
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
		philos(phi);
		
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

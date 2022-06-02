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
		if (get_time() - time >= new->s->ttd)
			break;
		pthread_mutex_unlock(&new->s->task);
		usleep(100);
	}
	return (get_time() - time);
}

void *eat(void *phi)
{
	t_phi *new = (t_phi *)phi;
	size_t time;
	time =get_time();
	int phil_max = 5;
	int temp = new->id;
	printf("%p \n", &new->s->fork[new->id]);
	pthread_mutex_lock(&new->s->fork[new->id]);
	pthread_mutex_lock(&new->s->fork[(new->id + 1) % (new->s->pno + 1)] );
	printf("timestamp_in_ms %d start %deating\n", new->id, (new->id + 1) % (new->s->pno + 1));
		sleeper(new);
	printf("timestamp_in_ms %d end %d eating\n", new->id, (new->id + 1) % (new->s->pno + 1));
	pthread_mutex_unlock(&new->s->fork[(new->id + 1) % (new->id + 1) % (new->s->pno + 1)]);
	pthread_mutex_unlock(&new->s->fork[new->id]);
	printf("%lu \n", get_time() - time);
	return (NULL);
}

void init_phi(t_phi *phi, t_sup *new)
{
	int i;

	i = 0;
	while (i < 5)
	{
		phi[i].id = i;
		phi[i].s = new;
		pthread_mutex_init(&new->fork[i],NULL);
		pthread_create(&phi[i].phi_t, NULL, eat, (void *)&phi[i]);
		pthread_join(phi[i].phi_t,NULL);
		i++;
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
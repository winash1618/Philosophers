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
			if (get_time() - time >= new->s->ttd)
				break;
		pthread_mutex_unlock(&new->s->task);
		usleep(100);
	}
	return (get_time() - time);
}

void init_sup(t_sup *sup)
{
	
	sup->pno = 2;
	sup->ttd = 200;
	sup->fork = malloc(sizeof(pthread_mutex_t)*2);
	pthread_mutex_init(&sup->fork[0], NULL);
	pthread_mutex_init(&sup->fork[1], NULL);
	printf("%p ", &sup->fork[0]);
	printf("%p\n", &sup->fork[1]);
	pthread_mutex_init(&sup->task, NULL);
}

void init_phi(t_phi *phi)
{
	int i;

	i = 0;
	while(i < 2)
	{
		phi[i].id = i;
		i++;
	}
	phi->s = malloc(sizeof(t_sup));
	init_sup(phi->s);
}

void eat(t_phi *phi, t_sup *sup)
{
	// printf("%p \n", &sup->fork);
	// pthread_mutex_lock(&sup->fork[phi->id]);
	// printf("%d start eat\n", phi->id);
	// sleeper(phi);
	// printf("%d end end\n", phi->id);
	// pthread_mutex_unlock(&sup->fork[phi->id]);
	
}
void drink(t_phi *phi, t_sup *sup)
{
	pthread_mutex_lock(&sup->fork[phi->id]);
	printf("%d start drink \n", phi->id);
	sleeper(phi);
	printf("%d end drink\n", phi->id);
	pthread_mutex_unlock(&sup->fork[phi->id]);
}

void *understand(void *phi)
{
	t_phi *phi1 = (t_phi *)phi;
	t_sup *sup1 = (t_sup *)phi1->s;

	while (1)
	{
		eat(phi1, sup1);
		// drink(phi1, sup1);
	}
}

int main()
{
	t_phi *phi;
	t_phi *sci;

	phi = malloc(sizeof(t_phi)*2);
	// sci = malloc(sizeof(t_phi));
	init_phi(phi);
	// init_phi(sci);
	printf("%d %d %d \n", phi[0].id, phi->s->pno, phi->s->ttd);
	printf("%d %d %d \n", phi[1].id, phi->s->pno, phi->s->ttd);
	int i = 0;

	while (i < 2)
	{
		pthread_create(&phi[i].phi_t, NULL, understand, (void *)&phi[i]);
		i++;
	}
	i = 0;
	while (i < 2)
	{
		pthread_join(phi[i].phi_t, NULL);
		i++;
	}

}
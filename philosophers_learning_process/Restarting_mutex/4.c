/* din_philo.c */    
  #include <pthread.h>
  #include <stdio.h>
  #include <unistd.h>
  #include <stdlib.h>
  #include <errno.h>
  #include <assert.h>

void *philosopher (void *id);
void grab_stick (int, int, char *);
void down_sticks (int, int);
int food_on_table ();

typedef struct common_data
{
	int pno;
	int ttd;
	int tte;
	int tts;
	int tt;
	int e_max;
	pthread_mutex_t *fork;
	pthread_mutex_t task;
}	t_data;

typedef struct philo
{
	int id;
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

//   #define PHILOS 5
//   #define DELAY 5000
//   #define FOOD 50

// void *philosopher (void *id);
// void grab_stick (int, int, char *);
// void down_sticks (int, int);
// int food_on_table ();

// pthread_mutex_t stick[PHILOS];
// pthread_t philo[PHILOS];
// pthread_mutex_t event_lock;
// int sleep_seconds = 0;

// int main (int argn, char **argv)
// {
//     int i;

//     if (argn == 2)
//         sleep_seconds = atoi (argv[1]);

//     pthread_mutex_init (&event_lock, NULL);
//     for (i = 0; i < PHILOS; i++)
//         pthread_mutex_init (&stick[i], NULL);
//     for (i = 0; i < PHILOS; i++)
//         pthread_create (&philo[i], NULL, philosopher, (void *)i);
// 	for (i = 0; i < PHILOS; i++)
// 		pthread_join (philo[i], NULL);
// 	    return 0;
// }
	
void *philosopher (void *phi)
{
	t_phi *phi1 = (t_phi *)phi;
	t_data *data = phi1->s;
	int num;


	printf ("Philosopher %d is done thinking and now ready to eat.\n", phi1->id);
	while (1)
	{
		// if (phi1->id == 0)
		// 	sleep(2);
		pthread_mutex_lock(&data->task);
			printf ("Philosopher %d: got %s stick %d\n", phi1->id, "right", phi1->id);
			pthread_mutex_lock(&data->fork[phi1->id]);
			printf ("Philosopher %d: got %s stick %d\n", phi1->id, "left", (phi1->id + 1) % (data->pno));
			pthread_mutex_lock(&data->fork[(phi1->id + 1) % (data->pno)]);
		pthread_mutex_unlock(&data->task);
		printf ("Philosopher %d: eating.\n", phi1->id);
		usleep (800000);
		printf ("Philosopher %d: drop %s stick %d\n", phi1->id, "right", phi1->id);
		pthread_mutex_unlock(&data->fork[phi1->id]);
		printf ("Philosopher %d: drop %s stick %d\n", phi1->id, "left", (phi1->id + 1) % (data->pno));
		pthread_mutex_unlock(&data->fork[(phi1->id + 1) % (data->pno)]);
		printf("%d started sleeping \n", phi1->id);
		usleep(200000);
		printf("%d end sleeping \n", phi1->id);
		

	}
	printf ("Philosopher %d is done eating.\n", phi1->id);
	return (NULL);
	
	
	
	
	//////////////////////////////////////////////////////////////////////////////
	
	// int id;
	// int i, left_stick, right_stick, f;

	// id = (int)num;
	// printf ("Philosopher %d is done thinking and now ready to eat.\n", id);
	// right_stick = id;
	// left_stick = id + 1;

	// if (left_stick == PHILOS)
	// 	left_stick = 0;
	
	
	// f = food_on_table ();
	// while (f) 
	// {
	// 	if (id == 1)
	// 		sleep (sleep_seconds);
	// 	pthread_mutex_lock (&event_lock);
	// 	grab_stick (id, right_stick, "right ");
	// 	grab_stick (id, left_stick, "left");
	// 	pthread_mutex_unlock (&event_lock);
	// 	printf ("Philosopher %d: eating.\n", id);
	// 	usleep (DELAY * (FOOD - f + 1));
	// 	down_sticks (left_stick, right_stick);
	// 	printf("%d \n", f);
	// 	f = food_on_table ();
	
	// }
	// printf ("Philosopher %d is done eating.\n", id);
	// return (NULL);
}
	
// int food_on_table ()
// {
// 	static int food = FOOD;
// 	int myfood;

// 	pthread_mutex_lock (&event_lock);
// 	if (food > 0) 
// 	{
// 		food--;
// 	}
// 	myfood = food;
// 		pthread_mutex_unlock (&event_lock);
// 		return myfood;
// }
    	
// void grab_stick (int phil, int c, char *hand)
// {
// 	pthread_mutex_lock (&stick[c]);
// 	printf ("Philosopher %d: got %s stick %d\n", phil, hand, c);
// }
   	
// void down_sticks (int c1, int c2)
// {
// 	printf ("droping sticks %d %d \n", c1, c2);
// 	pthread_mutex_unlock (&stick[c1]);
// 	pthread_mutex_unlock (&stick[c2]);
// }
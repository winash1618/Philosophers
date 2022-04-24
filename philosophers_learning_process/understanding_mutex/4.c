#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#ifndef NUM_THREADS
#define NUM_THREADS 4
#endif
typedef struct var
{
	int i;
	int j;
	pthread_mutex_t car;
	pthread_mutex_t car2;
} t_new;
void *func3(void *param)
{
	t_new *var =(t_new *)param;
    pthread_mutex_lock(&var->car);
    printf("Incrementing the shared variable... %d\n", (int)param);
    for (int i = 0; i < 10000; ++i) {
        var->i += 1;
    }
    pthread_mutex_unlock(&var->car);
    return 0;
}
void *func5(void *param)
{
	t_new *var =(t_new *)param;
    pthread_mutex_lock(&var->car);
    printf("Incrementing the shared variable... %d\n", (int)param);
    for (int i = 0; i < 10000; ++i) {
        var->i += 1;
    }
    pthread_mutex_unlock(&var->car);
    return 0;
}
void *func4(void *param)
{
	t_new *var =(t_new *)param;
	pthread_mutex_lock(&var->car);
    printf("Incrementing the shared variable...%d\n", (int)(param));
    for (int i = 0; i < 10000; ++i) {
         var->i += 1; 
    }
    pthread_mutex_unlock(&var->car);
    return 0;
}
int main()
{
	t_new *new;
    pthread_t threads[NUM_THREADS];
	 pthread_t threads1[NUM_THREADS];
	
	t_new *new1;
	new = malloc(sizeof(t_new));
	new1 = malloc(sizeof(t_new));
	pthread_mutex_init(&new->car, NULL);
	pthread_mutex_init(&new->car2, NULL);
	pthread_mutex_init(&new1->car, NULL);
	new->i = 1;
	new->j = 1;
	new1->i = 1;
	new1->j = 1;
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], NULL, func3, (void *) new);
    }
    for (int i = 0; i < NUM_THREADS; ++i) 
	{
		pthread_create(&threads[i], NULL, func3, (void *) new);
	}	
	for (int i = 0; i < NUM_THREADS; ++i) 
	{
        pthread_create(&threads1[i], NULL, func4, (void *) new1);
    }
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }
	for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads1[i], NULL);
    }
    printf("%d\n", new->i);
    exit(EXIT_SUCCESS);
}

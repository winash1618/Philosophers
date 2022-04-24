#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#ifndef NUM_THREADS
#define NUM_THREADS 4
#endif

int shared = 0;
 pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 
	 pthread_mutex_t mutex1 =PTHREAD_MUTEX_INITIALIZER;
void *func3(void *param)
{
    pthread_mutex_lock(&mutex);
    printf("Incrementing the shared variable... %d\n", (int)param);
    for (int i = 0; i < 10000; ++i) {
        shared += 1;
    }
    pthread_mutex_unlock(&mutex);
    return 0;
}
void *func4(void *param)
{
	pthread_mutex_lock(&mutex1);
    printf("Incrementing the shared variable...%d\n", (int)(param));
    for (int i = 0; i < 10000; ++i) {
        shared += 1;
    }
    pthread_mutex_unlock(&mutex1);
    return 0;
}
int main()
{
    pthread_t threads[NUM_THREADS];
	 pthread_t threads1[NUM_THREADS];
	
	 pthread_mutex_init(&mutex, NULL);
	 pthread_mutex_init(&mutex1,NULL);

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], NULL, func3, (void *) 1);
    }
	for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads1[i], NULL, func4, (void *) 2);
    }
	sleep(2);
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }
	for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads1[i], NULL);
    }
    printf("%d\n", shared);
    exit(EXIT_SUCCESS);
}

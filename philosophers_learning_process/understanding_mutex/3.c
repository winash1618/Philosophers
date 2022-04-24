#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct var
{
	int i;
	int j;
} t_new;


void* Compare(void* pair)
{
    t_new *my_pair = (t_new *)pair;
    printf("\nThread %d, %d", (*my_pair).i, (*my_pair).j);

    // free that memory after it has been used
    free (pair);
    return NULL;
}

int main()
{
	int n = 5;
    long thread_cmp_count = (long)n*(n-1)/2;
    long t,index = 0;
    t_new *pair;
	pthread_t cmp_thread[thread_cmp_count];

   
    for(int thread = 0;(thread < thread_cmp_count); thread++){
		 cmp_thread[thread] = malloc(thread_cmp_count*sizeof(pthread_t));
        for(t = thread+1; t < n; t++){
            // allocate a separate pair for each thread
            pair = malloc(sizeof(t_new));
            (*pair).i = thread;
            (*pair).j = t;
            pthread_create(&cmp_thread[index], NULL, Compare, (void *) pair);
			while (index < thread_cmp_count)
				index++;
        }
    }

    for(int thread= 0;(thread<thread_cmp_count); thread++){
        pthread_join(cmp_thread[thread], NULL);
    }

    free(cmp_thread);
}

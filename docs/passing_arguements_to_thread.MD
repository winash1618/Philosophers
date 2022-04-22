# Passing Arguments to Threads
  - The pthread_create() routine permits the programmer to pass one argument to the thread start routine. For cases where multiple arguments must be passed, this limitation is easily overcome by creating a structure which contains all of the arguments, and then passing a pointer to that structure in the pthread_create() routine.
  - All arguments must be passed by reference and cast to (void *).
  - How can you safely pass data to newly created threads, given their non-deterministic start-up and scheduling? Ans. Make sure that all passed data is thread safe - that it can not be changed by other threads. The three examples that follow demonstrate what not and what to do.
## Example 1 - Thread Argument Passing
  - This code fragment demonstrates how to pass a simple integer to each thread. The calling thread uses a unique data structure for each thread, insuring that each thread’s argument remains intact throughout the program.
  ```
    #include <pthread.h>
    #include <stdio.h>
    #include <stdlib.h>
	  #include <unistd.h>
    #define NUM_THREADS	8

    char *messages[NUM_THREADS];

    void *PrintHello(void *threadid)
    {
       long taskid;

       sleep(1);
       taskid = (long) threadid;
       printf("Thread %d: %s\n", (int)taskid, messages[taskid]);
       pthread_exit(NULL);
    }

    int main(int argc, char *argv[])
    {
    pthread_t threads[NUM_THREADS];
    long taskids[NUM_THREADS];
    int rc, t;

    messages[0] = "English: Hello World!";
    messages[1] = "French: Bonjour, le monde!";
    messages[2] = "Spanish: Hola al mundo";
    messages[3] = "Klingon: Nuq neH!";
    messages[4] = "German: Guten Tag, Welt!"; 
    messages[5] = "Russian: Zdravstvuyte, mir!";
    messages[6] = "Japan: Sekai e konnichiwa!";
    messages[7] = "Latin: Orbis, te saluto!";

    for(t=0;t<NUM_THREADS;t++) {
      taskids[t] = t;
      printf("Creating thread %d\n", t);
      rc = pthread_create(&threads[t], NULL, PrintHello, (void *) taskids[t]);
      if (rc) {
        printf("ERROR; return code from pthread_create() is %d\n", (int)rc);
        exit(-1);
        }
      }

    pthread_exit(NULL);
    }
  ```
  ```
  Output:
  
  Creating thread 0
  Creating thread 1
  Creating thread 2
  Creating thread 3
  Creating thread 4
  Creating thread 5
  Creating thread 6
  Creating thread 7
  Thread 1: French: Bonjour, le monde!
  Thread 6: Japan: Sekai e konnichiwa!
  Thread 2: Spanish: Hola al mundo
  Thread 4: German: Guten Tag, Welt!
  Thread 3: Klingon: Nuq neH!
  Thread 5: Russian: Zdravstvuyte, mir!
  Thread 7: Latin: Orbis, te saluto!
  Thread 0: English: Hello World!
  ```
  - From the output it is clear that thread is not showing the result according to the order they called.

## Example 2 - Thread Argument Passing
  - This example shows how to setup/pass multiple arguments via a structure. Each thread receives a unique instance of the structure.
  ```
    #include <pthread.h>
    #include <stdio.h>
    #include <stdlib.h>
	  #include <unistd.h>
	  #define NUM_THREADS	8
    char *messages[NUM_THREADS];

    struct thread_data
    {
       int	thread_id;
       int  sum;
       char *message;
    };

    struct thread_data thread_data_array[NUM_THREADS];

    void *PrintHello(void *threadarg)
    {
       int taskid, sum;
       char *hello_msg;
       struct thread_data *my_data;

       sleep(1);
       my_data = (struct thread_data *) threadarg;
       taskid = my_data->thread_id;
       sum = my_data->sum;
       hello_msg = my_data->message;
       printf("Thread %d: %s  Sum=%d\n", taskid, hello_msg, sum);
       pthread_exit(NULL);
    }

    int main(int argc, char *argv[])
    {
    pthread_t threads[NUM_THREADS];
    int *taskids[NUM_THREADS];
    int rc, t, sum;

    sum=0;
    messages[0] = "English: Hello World!";
    messages[1] = "French: Bonjour, le monde!";
    messages[2] = "Spanish: Hola al mundo";
    messages[3] = "Klingon: Nuq neH!";
    messages[4] = "German: Guten Tag, Welt!"; 
    messages[5] = "Russian: Zdravstvytye, mir!";
    messages[6] = "Japan: Sekai e konnichiwa!";
    messages[7] = "Latin: Orbis, te saluto!";

    for(t=0;t<NUM_THREADS;t++) {
      sum = sum + t;
      thread_data_array[t].thread_id = t;
      thread_data_array[t].sum = sum;
      thread_data_array[t].message = messages[t];
      printf("Creating thread %d\n", t);
      rc = pthread_create(&threads[t], NULL, PrintHello, (void *) 
           &thread_data_array[t]);
      if (rc) {
        printf("ERROR; return code from pthread_create() is %d\n", rc);
        exit(-1);
        }
      }
    pthread_exit(NULL);
    }
  ```
  ```
  Output:
  
  Creating thread 0
  Creating thread 1
  Creating thread 2
  Creating thread 3
  Creating thread 4
  Creating thread 5
  Creating thread 6
  Creating thread 7
  Thread 0: English: Hello World!  Sum=0
  Thread 3: Klingon: Nuq neH!  Sum=6
  Thread 1: French: Bonjour, le monde!  Sum=1
  Thread 4: German: Guten Tag, Welt!  Sum=10
  Thread 5: Russian: Zdravstvytye, mir!  Sum=15
  Thread 2: Spanish: Hola al mundo  Sum=3
  Thread 6: Japan: Sekai e konnichiwa!  Sum=21
  Thread 7: Latin: Orbis, te saluto!  Sum=28
  ```
## Example 3 - Thread Argument Passing (Incorrect)
- This example performs argument passing incorrectly. It passes the address of variable t, which is shared memory space and visible to all threads. As the loop iterates, the value of this memory location changes, possibly before the created threads can access it.
```
  #include <pthread.h>
  #include <stdio.h>
  #include <stdlib.h>
  #define NUM_THREADS     8

  void *PrintHello(void *threadid)
  {
     long taskid;
     sleep(1);
     taskid = *(long *)threadid;
     printf("Hello from thread %ld\n", taskid);
     pthread_exit(NULL);
  }

  int main(int argc, char *argv[])
  {
  pthread_t threads[NUM_THREADS];
  int rc;
  long t;

  for(t=0;t<NUM_THREADS;t++) {
    printf("Creating thread %ld\n", t);
    rc = pthread_create(&threads[t], NULL, PrintHello, (void *) &t);
    if (rc) {
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(-1);
      }
     }

  pthread_exit(NULL);
  }
```
```
  Output:

  Creating thread 0
  Creating thread 1
  Creating thread 2
  Creating thread 3
  Creating thread 4
  Creating thread 5
  Creating thread 6
  Creating thread 7
  Hello from thread 8
  Hello from thread 8
  Hello from thread 8
  Hello from thread 8
  Hello from thread 8
  Hello from thread 8
  Hello from thread 8
  Hello from thread 8
```

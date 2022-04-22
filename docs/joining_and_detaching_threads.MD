# Joining and Detaching Threads
## Joining:
  - “Joining” is one way to accomplish synchronization between threads. For example:

![joining](https://user-images.githubusercontent.com/51042907/164605606-7f3477b6-b044-4839-8e87-0b4f1ba7af02.gif)

  - The pthread_join() subroutine blocks the calling thread until the specified threadid thread terminates.
  - The programmer is able to obtain the target thread’s termination return status if it was specified in the target thread’s call to pthread_exit().
  - A joining thread can match one pthread_join() call. It is a logical error to attempt multiple joins on the same thread.
  - Two other synchronization methods, mutexes and condition variables, will be discussed later.
```
  SYNOPSIS
     #include <pthread.h>

     int pthread_join(pthread_t thread, void **value_ptr);

  DESCRIPTION
         The  pthread_join()  function  shall  suspend  execution of the calling
         thread until the target thread terminates, unless the target thread has
         already  terminated.

  RETURN VALUE
         If  successful,  the  pthread_join() function shall return zero; other-
         wise, an error number shall be returned to indicate the error.
  ```
## Joinable or Not?
- When a thread is created, one of its attributes defines whether it is joinable or detached. Only threads that are created as joinable can be joined. If a thread is created as detached, it can never be joined.
- The final draft of the POSIX standard specifies that threads should be created as joinable.
- To explicitly create a thread as joinable or detached, the attr argument in the pthread_create() routine is used. The typical 4 step process is:
  - Declare a pthread attribute variable of the pthread_attr_t data type
  - Initialize the attribute variable with pthread_attr_init()
  - Set the attribute detached status with pthread_attr_setdetachstate()
  - When done, free library resources used by the attribute with pthread_attr_destroy()

## Detaching:
- The pthread_detach() routine can be used to explicitly detach a thread even though it was created as joinable.
```
  SYNOPSIS
         #include <pthread.h>
  DESCRIPTION
         The pthread_detach() function shall indicate to the implementation that
         storage for the thread thread can be reclaimed when that thread  termi-
         nates.  If  thread has not terminated, pthread_detach() shall not cause
         it to terminate. The effect of multiple pthread_detach() calls  on  the
         same target thread is unspecified.

  RETURN VALUE
         If  the  call  succeeds, pthread_detach() shall return 0; otherwise, an
         error number shall be returned to indicate the error.
```
## Note:
- It is recommended that if a thread requires joining, consider explicitly creating it as joinable. This provides portability as not all implementations may create threads as joinable by default. If you know in advance that a thread will never need to join with another thread, consider creating it in a detached state. Some system resources may be able to be freed.

## Pthread Joining Example:
  ```
    #include <pthread.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
    #define NUM_THREADS	4

    void *BusyWork(void *t)
    {
       int i;
       long tid;
       double result=0.0;
       tid = (long)t;
       printf("Thread %ld starting...\n",tid);
       for (i=0; i<1000000; i++)
       {
          result = result + sin(i) * tan(i);
       }
       printf("Thread %ld done. Result = %e\n",tid, result);
       pthread_exit((void*) t);
    }

    int main (int argc, char *argv[])
    {
       pthread_t thread[NUM_THREADS];
       pthread_attr_t attr;
       int rc;
       long t;
       void *status;

       /* Initialize and set thread detached attribute */
       pthread_attr_init(&attr);
       pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

       for(t=0; t<NUM_THREADS; t++) {
          printf("Main: creating thread %ld\n", t);
          rc = pthread_create(&thread[t], &attr, BusyWork, (void *)t); 
          if (rc) {
             printf("ERROR; return code from pthread_create() is %d\n", rc);
             exit(-1);
             }
          }

       /* Free attribute and wait for the other threads */
       pthread_attr_destroy(&attr);
       for(t=0; t<NUM_THREADS; t++) {
          rc = pthread_join(thread[t], &status);
          if (rc) {
             printf("ERROR; return code from pthread_join() is %d\n", rc);
             exit(-1);
             }
          printf("Main: completed join with thread %ld having a status of %ld\n",t,(long)status);
          }

    printf("Main: program completed. Exiting.\n");
    pthread_exit(NULL);
    }
  ```
  ```
  Output:
  
  Main: creating thread 0
  Main: creating thread 1
  Main: creating thread 2
  Main: creating thread 3
  Thread 0 starting...
  Thread 2 starting...
  Thread 1 starting...
  Thread 3 starting...
  Thread 1 done. Result = -3.153838e+06
  Thread 2 done. Result = -3.153838e+06
  Thread 3 done. Result = -3.153838e+06
  Thread 0 done. Result = -3.153838e+06
  Main: completed join with thread 0 having a status of 0
  Main: completed join with thread 1 having a status of 1
  Main: completed join with thread 2 having a status of 2
  Main: completed join with thread 3 having a status of 3
  Main: program completed. Exiting.
  ```
  

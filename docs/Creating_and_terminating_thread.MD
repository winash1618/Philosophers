# Thread Management: Creating and Terminating Threads
## Creating Threads:
  - Initially, your main() program comprises a single, default thread. All other threads must be explicitly created by the programmer. pthread_create creates a new thread and makes it executable. This routine can be called any number of times from anywhere within your code.
  - Each thread has its own thread id, which is a concept distinct from that of a process id, since a process may actually contain many threads. The thread id type is pthread_t.
  ```
    #include <pthread.h>
    
    int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void  *(*start_routine)(void*), void * arg);
                                   ^                       ^                     ^                           ^      
                                   |                       |                     |                           | 
                                   |                       |                     |                           | 
                      thread id written here   we'll always be using NULL   thread function    arguments for thread function
  ```
  - pthread_create arguments:
    - thread: An opaque, unique identifier for the new thread returned by the subroutine.
    - attr: An opaque attribute object that may be used to set thread attributes. You can specify a thread attributes object, or NULL for the default values.
    - start_routine: the C routine that the thread will execute once it is created.
    - arg: A single argument that may be passed to start_routine. It must be passed by reference as a pointer cast of type void. NULL may be used if no argument is to be passed.
  - Notice that the only argument for the thread function is a void*, that means you need to put any information it needs in an array or struct and give a pointer to that object.
  -The maximum number of threads that may be created by a process is implementation dependent. Programs that attempt to exceed the limit can fail or produce wrong results. You need to check hard limit and soft limits for your system by using following commands.
  ```
  ulimit -a
  ulimit -Hu
  ```
  - As our first example, lets do something that was a bit of a pain with multiple processes: We have a program that prints X's forever, and whenever the user enters a different letter, prints that forever instead.
    ```
      #include <unistd.h>
      #include <stdio.h>
      #include <pthread.h>

      /* Global variable's are shared amongst threads! */
      char c = 'X';

      /* The thread we create will execute this function. */
      void* listenerThread(void * p)
      { 
        while(scanf(" %c",&c) == 1 && c != 'q')
          ;
        exit(0); /* calling exit in a thread exits the whole process! */
      }

      int main()
      {
        /* Create the listener thread */
        pthread_t lt;
        pthread_create(&lt,NULL,listenerThread,NULL);

        /* Write character c forever! */
        while(1)
        {
          printf("      %c",c);
          fflush(stdout);
          usleep(250000);
        }
        return 0;
       }
      ```
  - This program has two threads: one for printing the character over and over, and one waiting for scanf to give new character values. It's worth noting that a call to exit (or _exit) in any thread terminates the whole process.
  ******************************************************************************************
  ************* You are not allowed to use the function pthread_exit() *********************
  ******************************************************************************************
  ## Terminating Threads & pthread_exit():
  - There are several ways in which a thread may be terminated:
    - The thread returns normally from its starting routine. Its work is done.
    - The thread makes a call to the pthread_exit subroutine - whether its work is done or not.
    - The thread is canceled by another thread via the pthread_cancel routine.
    - The entire process is terminated due to making a call to either the exec() or exit()
    - If main() finishes first, without calling pthread_exit explicitly itself
  - The pthread_exit() routine allows the programmer to specify an optional termination status parameter. This optional parameter is typically returned to threads “joining” the terminated thread (covered later).
  - In subroutines that execute to completion normally, you can often dispense with calling pthread_exit() - unless, of course, you want to pass the optional status code back.
  - Cleanup: the pthread_exit() routine does not close files; any files opened inside the thread will remain open after the thread is terminated.
  - Discussion on calling pthread_exit() from main():
    - There is a definite problem if main() finishes before the threads it spawned if you don’t call pthread_exit() explicitly. All of the threads it created will terminate because main() is done and no longer exists to support the threads.
    - By having main() explicitly call pthread_exit() as the last thing it does, main() will block and be kept alive to support the threads it created until they are done.
  ```
    #include <pthread.h>
    
    void pthread_exit(void *value_ptr);
  ```
## Example: Pthread Creation and Termination
- This simple example code creates 5 threads with the pthread_create() routine. Each thread prints a “Hello World!” message, and then terminates with a call to pthread_exit().
```
  #include <pthread.h>
   #include <stdio.h>
   #define NUM_THREADS     5

   void *PrintHello(void *threadid)
   {
      long tid;
      tid = (long)threadid;
      printf("Hello World! It's me, thread #%ld!\n", tid);
      pthread_exit(NULL);
   }

   int main (int argc, char *argv[])
   {
      pthread_t threads[NUM_THREADS];
      int rc;
      long t;
      for(t=0; t<NUM_THREADS; t++){
         printf("In main: creating thread %ld\n", t);
         rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
         if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
         }
      }

      /* Last thing that main() should do */
      pthread_exit(NULL);
   }
```
```
  Output:
    In main: creating thread 0
    In main: creating thread 1
    Hello World! It's me, thread #0!
    In main: creating thread 2
    Hello World! It's me, thread #1!
    Hello World! It's me, thread #2!
    In main: creating thread 3
    In main: creating thread 4
    Hello World! It's me, thread #3!
    Hello World! It's me, thread #4!
```
    

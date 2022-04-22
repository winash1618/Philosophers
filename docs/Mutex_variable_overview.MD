# Mutex variable overview:
## Introduction:
  - Whenever we have a resource that is shared amongst several processes/threads, like the global data, any chunk of code that accesses that resource is referred to as a critical section, meaning a chunk of code in which different processes/threads can interfere with one another. The critical section problem is to control access to the resources manipulated in critical sections to avoid problems, and any acceptable solution must satisfy the following three criteria:
    - mutual exlusion (mutex) - that only one process/thread can be in a critical section with respect to the shared resource at the same time,
    - progress - that no process/thread that is not in a critical section with respect to the shared resource can prevent other processes/threads from entering their critical sections, and
    - bounded wait - that any process/thread that wants to get into a critical section with respect to the shared resource eventually will enter that critical section.
    - Mutex is an abbreviation for “mutual exclusion”. Mutex variables are one of the primary means of implementing thread synchronization and for protecting shared data when multiple writes occur.
  - A typical sequence in the use of a mutex is as follows:
    - Create and initialize a mutex variable
    - Several threads attempt to lock the mutex
    - Only one succeeds and that thread owns the mutex
    - The owner thread performs some set of actions
    - The owner unlocks the mutex
    - Another thread acquires the mutex and repeats the process
    - Finally the mutex is destroyed
## Pthreads mutex
  - A mutex variable acts like a “lock” protecting access to a shared data resource. The basic concept of a mutex as used in Pthreads is that only one thread can lock (or own) a mutex variable at any given time. Thus, even if several threads try to lock a mutex only one thread will be successful. No other thread can own that mutex until the owning thread unlocks that mutex. Threads must “take turns” accessing protected data.
 - There is a special data-structure called a mutex that is used to regulate access to critical sections. It provides two operations: lock and unlock. Immediately before entering a critical section associated with mutex M, a process P tries to lock M --- in facier parlence: it tries to aquire a lock on M. If some other process has already aquired a lock on M, process P is suspended until the mutex is no longer locked, i.e. until the process that currently has the lock performs an unlockoperation on M. Pthreads implements mutexes, and as long as threads use it properly, by locking immediately prior to entering a critical section and unlocking immediately after that critical section, the mutex provides a solution to the mutual exclusion problem. Pthreads has a special type pthread_mutex_t for mutexes, and the following operations:
    - int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr); ← the second argument will be NULL for our examples
    - int pthread_mutex_destroy(pthread_mutex_t *mutex);
    - int pthread_mutex_lock(pthread_mutex_t *mutex);
    - int pthread_mutex_unlock(pthread_mutex_t *mutex);
  - the pthread_mutex_t object you're using needs to be global, so all the threads can access it.
### Creating and Destroying Mutexes
  - Mutex variables must be declared with type pthread_mutex_t, and must be initialized before they can be used. There are two ways to initialize a mutex variable:
    - Statically, when it is declared. For example: pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER;
    - Dynamically, with the pthread_mutex_init() routine. This method permits setting mutex object attributes, attr.
  ```
    SYNOPSIS
       #include <pthread.h>
       
       int pthread_mutex_init(pthread_mutex_t *restrict mutex,
              const pthread_mutexattr_t *restrict attr);
       pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
  ```
  - The mutex is initially unlocked.
  - The attr object is used to establish properties for the mutex object, and must be of type pthread_mutexattr_t if used (may be specified as NULL to accept defaults). The Pthreads standard defines three optional mutex attributes:
    - Protocol: Specifies the protocol used to prevent priority inversions for a mutex.
    - Prioceiling: Specifies the priority ceiling of a mutex.
    - Process-shared: Specifies the process sharing of a mutex.
  - Note that not all implementations may provide the three optional mutex attributes.
  - pthread_mutex_destroy() should be used to free a mutex object which is no longer needed.
```
SYNOPSIS
       #include <pthread.h>

       int pthread_mutex_destroy(pthread_mutex_t *mutex);
RETURN VALUE
       If successful,  the  pthread_mutex_destroy()  and  pthread_mutex_init()
       functions  shall  return  zero;  otherwise,  an  error  number shall be
       returned to indicate the error.
```
## Locking and Unlocking Mutexes
  - The pthread_mutex_lock() routine is used by a thread to acquire a lock on the specified mutex variable. If the mutex is already locked by another thread, this call will block the calling thread until the mutex is unlocked.
```
  SYNOPSIS
         #include <pthread.h>

         int pthread_mutex_lock(pthread_mutex_t *mutex);
         int pthread_mutex_unlock(pthread_mutex_t *mutex);

  RETURN VALUE
         If  successful,  the  pthread_mutex_lock()  and  pthread_mutex_unlock()
         functions  shall  return  zero;  otherwise,  an  error  number shall be
         returned to indicate the error.
```
  - pthread_mutex_trylock() will attempt to lock a mutex. However, if the mutex is already locked, the routine will return immediately with a “busy” error code. This routine may be useful in preventing deadlock conditions, as in a priority-inversion situation.
  - pthread_mutex_unlock() will unlock a mutex if called by the owning thread. Calling this routine is required after a thread has completed its use of protected data if other threads are to acquire the mutex for their work with the protected data. An error will be returned if:
    - If the mutex was already unlocked
    - If the mutex is owned by another thread
  - There is nothing “magical” about mutexes…in fact they are akin to a “gentlemen’s agreement” between participating threads. It is up to the code writer to ensure that the necessary threads all make the the mutex lock and unlock calls correctly. The following scenario demonstrates a logical error:
```
        Thread 1
        Lock
        A = 2
        Unlock	

        Thread 2
        Lock
        A = A+1
        Unlock

        Thread 3
        A = A*B
```

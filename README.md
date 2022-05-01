# Philosophers
## tips
- (*variable_name).data is same as varialble_name->data
- gcc 4.c libft/ft_printf/libftprintf.a -pthread
- valgrind --tool=helgrind ./a.out 
- The first @ in Makefile for example (@$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@) can suppress the executing commands being shown in the terminal.
- Inorder to makefile with ft_printf you need to include the header file in the header file .
- valgrind --leak-check=full \ --show-leak-kinds=all \ --track-origins=yes \ --verbose \ --log-file=valgrind-out.txt \ ./executable exampleParam1
## Doubts and Clarification
  - How to access specific obect using pthread_mutex_lock? the thing i understood is that when you call mutex lock the mutex will lock  what ever between mutex lock and unlock with a specific mutex id or something else i don't konw, this is my understanding i don't know if it is right or wrong. So if you want another thread to access the area that is currently locked you need to do mutex unlock with the specific mutex variable you locked with. Unless this happens no other thread access whatever inside the locked area.
  - So in our case we have forks that needs to be locked, ie while eating, a philosopher will have two forks so inorder to lock it we must call mutex lock with a specific id. and do the work inside it after that you can unlock it. this is my understanding as of now.
  - When i created 2.c and ran the program expecting that it will give me 80000, but it was only giving me 50000 to 75000 range. This means that only the code written between lock and unlock is being protected not the global shared data and all. here the global variable shared is accessed by both the functions at the same time because they have two different mutex variable.
  - The local variables and function parameters are specific for each threads so you don't have to worry about them unless you are passing it another function with its address. read the [pdf](http://lemuria.cis.vtc.edu/~pchapin/TutorialPthread/pthread-Tutorial.pdf) for more details.
  - if you access the value when you are changing it, then it will become a data race. see in mutex_reborn/6.c you are accessing data->tt also you are changing it at the same time. I think you should put all of this critical areas inside a lock with same address as shown in mutex_reborn2/3.c i put it under data->task[3]. 
  - Inorder to avoid order violation of the threads locking and unlocking you should lock and unlock in the same order. Because if you have more than one lock in the program and you opened it in a specific order and you close it in some other order this will create order violation in helgrind. Inorder to avoid this you will have to use many techniques according to the situation you are facing. Like if you are changing the number of threads as even or odd you should specify what to do in your program when this problem arises.
  - There is also problem with ft_printf because if tries to access it with multiple threads at the same time then you will get garbage printing in your stdout in order to avoid this you should allways put those inside a lock.
  - I did'nt test but i believe that one array of fork locks and another single lock is enough in our case.
## Resources
  - https://hpc-tutorials.llnl.gov/posix/
  - https://www.cse.iitk.ac.in/users/swarnendu/courses/spring2019-cs636/
  - [CS636: Shared Memory Programming and POSIX Threads Swarnendu Biswas](https://github.com/winash1618/Philosophers/blob/main/Shared%20Memory%20Programming.pdf)
  - https://cse.iitkgp.ac.in/~abhij/course/lab/
  - http://www.cs.iit.edu/~iraicu/teaching/EECS211/index.html
  - https://www.iitp.ac.in/~arijit/dokuwiki/doku.php?id=teaching
  - https://www.cse.iitb.ac.in/~mythili/os/ps/concurrency/ps-concurrency.pdf
  - https://csci315f21.courses.bucknell.edu/lab/ 
  - http://lemuria.cis.vtc.edu/~pchapin/TutorialPthread/pthread-Tutorial.pdf
  - https://docs.oracle.com/cd/E19455-01/806-5257/sync-12/index.html
  - https://stackoverflow.com/questions/65007137/thread-never-gets-the-lock-pthread-mutex-lock
  - https://www.geeksforgeeks.org/mutex-lock-for-linux-thread-synchronization/
  - https://www.ee.ryerson.ca/~courses/coe518/Labs/lab4/lisi.edu-dining-Philosopherecture8.pdf
  - https://docs.oracle.com/cd/E19205-01/820-0619/gepji/index.html
  - https://valgrind.org/docs/manual/hg-manual.html
  - https://www.gnu.org/software/make/manual/make.html Makefile tutorial by Gnu
  - https://stackoverflow.com/questions/5134891/how-do-i-use-valgrind-to-find-memory-leaks
 
## Philosophers learning process
  - [Getting started](docs/intro_to_functions.MD)
  - [POSIX Threads Programming](docs/threads.MD)
  - 

# What is a pthread?
- Pthreads are defined as a set of C language programming types and procedure calls, implemented with a pthread.h header/include file and a thread library - though this library may be part of another library, such as libc, in some implementations.
- The implementation of threads we'll be using is called pthreads - for "posix threads". 
- You'll need to include pthread.h for most everything we do with threads. Any function whose prototype looks like void* foo(void *p); can be a thread; meaning that if you call the function the right way, it'll go off and do its computing while, at the same time, the calling code continues doing its thing.
- Programs having the following characteristics may be well suited for pthreads:
  - Work that can be executed, or data that can be operated on, by multiple tasks simultaneously:
  - Block for potentially long I/O waits
  - Use many CPU cycles in some places but not others
  - Must respond to asynchronous events
  - Some work is more important than other work (priority interrupts)

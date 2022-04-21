# What is a thread?
## What is a process?
- Before understanding a thread, one first needs to understand a UNIX process. A process is created by the operating system, and requires a fair amount of “overhead”. Processes contain information about program resources and program execution state, including:
  - Process ID, process group ID, user ID, and group ID
  - Environment
  - Working directory
  - Program instructions
  - Registers
  - Stack
  - Heap
  - File descriptors
  - Signal actions
  - Shared libraries
  - Inter-process communication tools (such as message queues, pipes, semaphores, or shared memory).    
- We can divide an application into distinct communicating processes. Each process is completely independent in the following sense: their memory spaces are completely separate. The stack, the heap and static areas of memory for each process are not simply separate, but actually protected from one another. Process A cannot touch Process B's memory. The OS and hardware enforce this. That's why Google Chrome assigns each tab its own process. One tab crashing won't affect the other tabs.
- The strength of the multiprocess architecture is also sometimes a weakness. Sharing data amongst processes is a bit of a pain, because you can't simply share variables.
## Threads
- Technically, a thread is defined as an independent stream of instructions that can be scheduled to run as such by the operating system. But what does this mean?
- To the software developer, the concept of a “procedure” that runs independently from its main program may best describe a thread.
- To go one step further, imagine a main program (a.out) that contains a number of procedures. Then imagine all of these procedures being able to be scheduled to run simultaneously and/or independently by the operating system. That would describe a “multi-threaded” program.
- A family of threads is like a set of processes that all share the same memory. Each thread has its own stack, but even those addresses are accessible to other threads in the same process ... though it'd be inviting disaster to try. But threads share the same heap, initialized and uninitialized global, and text segments.
- Threads use and exist within these process resources, yet are able to be scheduled by the operating system and run as independent entities largely because they duplicate only the bare essential resources that enable them to exist as executable code.
- This independent flow of control is accomplished because a thread maintains its own:
  - Stack pointer
  - Registers
  - Scheduling properties (such as policy or priority)
  - Set of pending and blocked signals
  - Thread specific data.



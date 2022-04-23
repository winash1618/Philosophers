# [Rules for Multithreaded Programming](http://lemuria.cis.vtc.edu/~pchapin/TutorialPthread/pthread-Tutorial.pdf)
## What data is shared?
  - Static duration data (data that lasts as long as the program does). This
includes global data and static local data. The case of static local data is
only significant if two (or more) threads execute the function containing
the static local at the same time.
  - Dynamically allocated data that has had its address put into a static
variable. For example, if a function uses malloc() or new to allocate an
object and then places the address of that object into a variable that is
accessible by more than one thread, the dynamically allocated object will
then be accessible by more than one thread.
  - The data members of a class object that has two (or more) of its member
functions called by different threads at the same time.
## What data is not shared?
  - Local variables. Even if two threads call the same function they will have
different copies of the local variables in that function. This is because the
local variables are kept on the stack and every thread has its own stack.
  - Function parameters. In languages like C the parameters to functions are
also put on the stack and thus every thread will have its own copy of those
as well.
## Note:
- Since local variables and function parameters can’t be shared they are immune
to race conditions. Thus you should use local variables and function parameters
whenever possible. Avoid using global data. Be aware, however, that taking
the address of a local variable and passing that address to place where another
thread can read it amounts to sharing the local variable with that other thread.
## What type of simultaneous access causes a problem?
- Whenever one thread tries to update an object, no other threads should
be allowed to touch the object (for either reading or writing). Mutual
exclusion should be enforced with some sort of mutex-like object (or by
some other suitable means). 
## What type of simultaneous access is safe?
- If multiple threads only read the value of an object, there should be no
problem. Be aware, however, that complicated objects often update internal information even when, from the outside, they are only being read.
Some objects maintain a cache or keep track of usage statistics internally
even for reads. Simultaneous reads on such an object might not be safe.
- If one thread writes to one object while another thread touches a totally
independent object, there should be no problem. Be aware, however, that
many functions and objects do share some data internally. What appears
to be two separate objects might really be using a shared data structure
behind the scenes.
- Certain types of objects are updated in an uninterruptable way. Thus
simultaneous reads and writes to such objects are safe because it is impossible for the object to be in an inconsistent state during the update.
Such updates are said to be atomic. The bad news is that the types that
support atomic updates are usually very simple (for example: int) and
there is no good way to know for sure exactly which types they are. The
C standard provides the type sig atomic t for this purpose. It is defined in <signal.h> and is a kind of integer. Simultaneous updates to an
object declared to be volatile sig atomic t are safe. Mutexes are not
necessary in this case
## What can I count on?
- Unless a function is specifically documented as being thread-safe, you should
assume that it is not. Many libraries make extensive use of static data internally
and unless those libraries were designed with multiple threads in mind that static
data is probably not being properly protected with mutexes.
- Similarly you should regard the member functions of a class as unsafe for multiple threads unless it has been specifically documented to be otherwise. It is
easy to see that there might be problems if two threads try to manipulate the
same object. However, even if two threads try to manipulate different objects
there could still be problems. For various reasons, many classes use internal
static data or try to share implementation details among objects that appear
to be distinct from the outside.
- If you use a non thread-safe function in one of your functions, your function
will be rendered non thread-safe as well. However, you are free to use a non
thread-safe function in a multithreaded program provided it is never called by
two or more threads at the same time. You can either arrange to use such
functions in only one thread or protect calls to such functions with mutexes.
Keep in mind that many functions share data internally with other functions.
If you try to protect calls to a non thread-safe function with a mutex you must
also protect calls to all the other related functions with the same mutex. This
is often difficult.

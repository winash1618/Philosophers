#include <stdio.h>
#include <sys/time.h>

int main()
{
    struct timeval tv;

    gettimeofday(&tv, NULL);

    printf("Seconds since 1/1/1970: %lu\n",tv.tv_sec);
    printf("Microseconds: %d\n",tv.tv_usec);
    return(0);
}
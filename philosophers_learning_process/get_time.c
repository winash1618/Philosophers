#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int main()
{
    struct timeval tv;
	static double time;
	double time1;
    gettimeofday(&tv, 0);
	time = tv.tv_sec + tv.tv_usec/1000000;
	sleep(2);
	gettimeofday(&tv, 0);
	time1 = tv.tv_sec + tv.tv_usec/1000000.0;
	printf("%.15f", time1 - time);
    

    return(0);
}
#include <stdio.h>
#include <time.h>
#include<unistd.h>

int main(void)
{
    struct timespec tstart={0,0}, tend={0,0};
    clock_gettime(CLOCK_MONOTONIC, &tstart);
    usleep(10000);
    clock_gettime(CLOCK_MONOTONIC, &tend);
    printf("some_long_computation took about %.5f seconds\n",
           ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) - 
           ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec));



    return 0;
}
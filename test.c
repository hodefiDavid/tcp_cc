//
// Created by david on 20/12/2020.
//
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

void main() {

    struct timeval stop, start;
    gettimeofday(&start, NULL);
//do stuff
    sleep(2);
    gettimeofday(&stop, NULL);
    double dt = (double)((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec) / 1000000;
    printf("took %f us\n", dt);
}

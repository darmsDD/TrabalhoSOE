#ifndef SENSOR_H
#define SENSOR_H

#include <wiringPi.h>
#include <unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<signal.h>
#include<pthread.h>

#define trigger 2
#define echo 3

void * sensor(void * args);

#endif

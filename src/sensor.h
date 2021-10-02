#ifndef SENSOR_H
#define SENSOR_H

#include <wiringPi.h>
#include<stdio.h>
#include<math.h>
#include<pthread.h>
#include<signal.h>
#include<unistd.h>

#define trigger 2
#define echo 3
#define IN1 7
#define IN2 9
#define IN3 15
#define IN4 16

void * sensor(void * args);

#endif

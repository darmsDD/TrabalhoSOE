#ifndef SENSOR_H
#define SENSOR_H

#include <wiringPi.h>
#include<stdio.h>
#include<math.h>
#include<pthread.h>
#include<signal.h>
#include<unistd.h>
#include <softPwm.h>

#define frontal1_trigger 2
#define frontal1_echo 3
#define frontal2_trigger 4
#define frontal2_echo 5

#define traseiro1_trigger 12
#define traseiro1_echo 13
#define traseiro2_trigger 6
#define traseiro2_echo 10

#define lateral1_trigger 11
#define lateral1_echo 31
#define lateral2_trigger 2
#define lateral2_echo 3

// definições dos pinos para os motores
#define IN1 8
#define IN2 9
#define IN3 16
#define IN4 15
#define IN5 7
#define IN6 1


struct sensores {
    int id_sensor;
    char * continuaThread;
};

void * sensor(void * args);

#endif

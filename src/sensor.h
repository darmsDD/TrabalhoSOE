#ifndef SENSOR_H
#define SENSOR_H

#include <wiringPi.h>
#include<stdio.h>
#include<math.h>
#include<pthread.h>
#include<signal.h>
#include<unistd.h>

#define frontal1_trigger 2
#define frontal1_echo 3
#define frontal2_trigger 2
#define frontal2_echo 3

#define traseiro1_trigger 2
#define traseiro1_echo 3
#define traseiro2_trigger 2
#define traseiro2_echo 3

#define lateral2_trigger 2
#define lateral2_echo 3
#define lateral1_trigger 2
#define lateral1_echo 3

// definições dos pinos para os motores
#define IN1 7
#define IN2 9
#define IN3 15
#define IN4 16


struct sensores {
    int id_sensor;
    char * continuaThread;
    int * freio;
}

void * sensor(void * args);

#endif

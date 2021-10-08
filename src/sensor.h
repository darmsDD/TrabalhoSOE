#ifndef SENSOR_H
#define SENSOR_H

#include <wiringPi.h>
#include<stdio.h>
#include<math.h>
#include<pthread.h>
#include<signal.h>
#include<unistd.h>
#include <softPwm.h>
#include "motor.h"

#define frontal1_trigger 4
#define frontal1_echo 5
#define frontal2_trigger 4
#define frontal2_echo 5

#define traseiro1_trigger 12
#define traseiro1_echo 13
#define traseiro2_trigger 6
#define traseiro2_echo 10

#define lateral1_trigger 0
#define lateral1_echo  2
#define lateral2_trigger 12
#define lateral2_echo 13




struct sensores {
    int id_sensor;
    char * continuaThread;
    double distancia;
    int num;
};

struct sensores estrutura_sensores[3];
void * sensor(void * args);


#endif

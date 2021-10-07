#ifndef SENSOR_H
#define SENSOR_H

#include <wiringPi.h>
#include<stdio.h>
#include<math.h>
#include<pthread.h>
#include<signal.h>
#include<unistd.h>
#include <softPwm.h>

#define frontal1_trigger 0
#define frontal1_echo 2
#define frontal2_trigger 4
#define frontal2_echo 5

#define traseiro1_trigger 12
#define traseiro1_echo 13
#define traseiro2_trigger 6
#define traseiro2_echo 10

#define lateral1_trigger 4
#define lateral1_echo 5
#define lateral2_trigger 12
#define lateral2_echo 13

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
    double distancia;
};

void * sensor(void * args);

void gira_carrinho(int lateral1, int lateral2);
void para_carrinho();


#endif

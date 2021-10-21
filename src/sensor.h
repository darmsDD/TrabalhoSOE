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

#define frontal_esquerda_trigger 4
#define frontal_esquerda_echo 5
#define frontal_direita_trigger  12
#define frontal_direita_echo 13

#define traseiro_esquerdo_trigger 11
#define traseiro_esquerdo_echo 31
#define traseiro_direito_trigger 4
#define traseiro_direito_echo 5

#define lateral_esquerda_trigger 0
#define lateral_esquerda_echo  2
#define lateral_direita_trigger 6
#define lateral_direita_echo 10

#define frontal_esquerda 0
#define frontal_direita 1
#define traseiro_esquerda 2
#define traseiro_direita 3
#define lateral_esquerdo 4
#define lateral_direito 5


struct sensores {
    int id_sensor;
    char * continuaThread;
    double distancia;
    int num;
};

struct sensores estrutura_sensores[4];
void * sensor(void * args);


#endif

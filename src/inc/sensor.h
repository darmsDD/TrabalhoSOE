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

#define frontal_esquerda_trigger 6
#define frontal_esquerda_echo 10
#define frontal_direita_trigger  21
#define frontal_direita_echo 22

#define traseiro_trigger 12
#define traseiro_echo 13

#define lateral_esquerda_trigger 0
#define lateral_esquerda_echo  2
#define lateral_direita_trigger 4
#define lateral_direita_echo 5

#define frontal_esquerda 0
#define frontal_direita 1
#define traseiro 2
#define lateral_esquerdo 3
#define lateral_direito 4

// 6 10 lateral direita
// 4 5 frontal esquerda
// 21 22 traseiro
// 12 13 frontal direita

struct sensores {
    int id_sensor;
    char * continuaThread;
    double distancia;
    int num;
};

struct sensores estrutura_sensores[5];
void * sensor(void * args);

void distancia_valida(int cont,double media,int id,struct sensores * estrutura_sensor);
#endif

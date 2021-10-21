#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include "sensor.h"
#include <softPwm.h>
#include "motor.h"
#include<signal.h>

#define frontal_esquerda 0
#define frontal_direita 1
#define traseiro_esquerda 2
#define traseiro_direita 3
#define lateral_esquerdo 4
#define lateral_direito 5


pthread_t sensor_frontal[2],sensor_lateral[2],sensor_traseiro[2];
char keepThreading = 1;


#endif
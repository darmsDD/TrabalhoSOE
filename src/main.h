#ifndef MAIN_H
#define MAIN_H

#include<stdlib.h>
#include "sensor.h"
#include <softPwm.h>
#include"mapa.h"

#define frontal1 0
#define frontal2 1
#define traseiro1 2
#define traseiro2 3
#define lateral1 4
#define lateral2 4

pthread_t sensor_frontal[2],sensor_lateral[2],sensor_traseiro[2];
char keepThreading = 1;


#endif
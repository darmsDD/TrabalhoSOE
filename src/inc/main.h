#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <softPwm.h>
#include <signal.h>
#include "prioridadeThread.h"
#include "sensor.h"
#include "mapa.h"
#include "motor.h"


pthread_t sensor_frontal[2],sensor_lateral[2],sensor_traseiro,t_mapa,t_obstaculos;
char keepThreading = 1;


#endif
#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include "sensor.h"
#include <softPwm.h>
#include "motor.h"
#include<signal.h>


pthread_t sensor_frontal[2],sensor_lateral[2],sensor_traseiro;
char keepThreading = 1;


#endif
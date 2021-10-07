#ifndef MOTOR_H
#define MOTOR_H

#include <wiringPi.h>
#include <softPwm.h>

#define IN1 8
#define IN2 9
#define IN3 16
#define IN4 15
#define IN5 7
#define IN6 1


void gira_carrinho(int lateral1, int lateral2);
void para_carrinho();
void anda_pra_frente();
void anda_pra_tras();

#endif
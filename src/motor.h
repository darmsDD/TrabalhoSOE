#ifndef MOTOR_H
#define MOTOR_H

#include <wiringPi.h>
#include <softPwm.h>
#include<signal.h>
#include<stdio.h>
#include<unistd.h>

#define IN1 8
#define IN2 9
#define IN3 16
#define IN4 15
#define IN5 7
#define IN6 1


void gira_carrinho(double lateral1, double lateral2);
void para_carrinho();
void anda_pra_frente();
void anda_pra_tras();
void gira_pra_esquerda();
void gira_pra_direita();
void ponto_morto();
void inicia_motor();

#endif
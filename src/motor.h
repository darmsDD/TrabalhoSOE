#ifndef MOTOR_H
#define MOTOR_H

#include <wiringPi.h>
#include <softPwm.h>
#include<signal.h>
#include<stdio.h>
#include<unistd.h>

#define RODA_ESQUERDA_1 8
#define RODA_ESQUERDA_2 9
#define RODA_DIREITA_1 16
#define RODA_DIREITA_2 15
#define PWM_RODA_ESQUERDA 7
#define PWM_RODA_DIREITA 1


void gira_carrinho(double lateral_esquerda, double lateral_direita);
void para_carrinho();
void anda_pra_frente();
void anda_pra_tras();
void gira_pra_esquerda();
void gira_pra_direita();
void ponto_morto();
void inicia_motor();

#endif
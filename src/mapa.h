#ifndef MAPA_H
#define MAPA_H

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<math.h>
#include<unistd.h>
#include<signal.h>
#include<string.h>
#include"sensor.h"

#define tamanho_carrinho 14
#define N 5000

void * desenha_mapa();
void * obstaculos(void * args);
void * desenha_mapa();
void imprime_mapa();



#endif
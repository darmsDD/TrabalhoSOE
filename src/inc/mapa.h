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

#define largura_carrinho 27
#define comprimento_carrinho 26
#define N 1000

void * desenha_mapa(void * args);
void * obstaculos(void * args);
void * desenha_mapa();
void imprime_mapa();



#endif
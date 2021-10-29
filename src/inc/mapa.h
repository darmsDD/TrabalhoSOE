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
void switch_obstaculos(int direc,int distancia_obstaculo,int desloc_escrita,int tamanho_carrinho);
void preenche_mapa_obstaculo(int l,int c,int vertical,int sensor);
void altera_posicao(int opcao);
void altera_direcao();



#endif
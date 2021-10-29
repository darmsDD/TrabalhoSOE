#ifndef PRIORIDADE_THREAD_H
#define PRIORIDADE_THREAD_H


#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include<unistd.h>


void cria_thread_com_prioridade(pthread_t *t,int prioridade,void *(*funcao)(void *),void * args);




#endif
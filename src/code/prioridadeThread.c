#include "../inc/prioridadeThread.h"

void cria_thread_com_prioridade(pthread_t *t,int prioridade,void *(*funcao)(void *),void * args){
    int rc;
    pthread_attr_t attr;
    struct sched_param param;

    rc = pthread_attr_init (&attr);
    rc = pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
	if (rc) {
		printf("pthread setschedpolicy failed\n");
		//return ret;
	}

    rc = pthread_attr_getschedparam (&attr, &param);
    param.sched_priority=prioridade;
    rc = pthread_attr_setschedparam (&attr, &param);
    pthread_attr_getschedparam (&attr, &param);
    //printf("prio %d\n",param.sched_priority);
    pthread_create (t, &attr,funcao, args);
   
    return;

}

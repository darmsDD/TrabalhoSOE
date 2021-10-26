
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <stdint.h>
#include <pthread.h>
#include <sys/mman.h>
#include <signal.h>
#include <limits.h>
#include <sched.h>

void * thread_func(void * args){
    int a = *((int *)args);
    //printf("%d\n",a);
    //sleep(3);
    for(int i=0;i<1000;i++){
        printf("p.%d i.%d\n",a,i);
    }
    
    pthread_exit(0);
}


void cria_thread_com_prioridade(pthread_t *t,int *prioridad){

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
    param.sched_priority=*prioridad;
    rc = pthread_attr_setschedparam (&attr, &param);
    pthread_attr_getschedparam (&attr, &param);
    printf("prio %d\n",param.sched_priority);
    pthread_create (t, &attr,&thread_func, prioridad);


    return;

}


int main()
{
    pthread_t  t[5];
    int a = 5,b = 97;
    cria_thread_com_prioridade(&t[1],&a);
    cria_thread_com_prioridade(&t[0],&b);
    
    //cria_thread_com_prioridade(&t[1],30);
    //cria_thread_com_prioridade(&t[1],20);

    
    for(int i=0;i<2;i++){
        pthread_join(t[i],NULL);
    }

    return 0;
}
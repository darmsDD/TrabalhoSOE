#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

struct pu {

    int a;
    int b;


};


void * func(void * args){

    struct pu *p2 = (struct pu *)args;
    struct pu * frente = p2;
    struct pu * lado = p2 + 1;


    printf("%d %d\n",frente->a,frente->b);
    printf("%d %d\n",lado->a,lado->b);
    frente->a = 50;



    pthread_exit(0);
}


int main(){
   
    struct pu p[2];
    p[0].a = 5;
    p[0].b = 10;
    p[1].a = 1;
    p[1].b = 2;
    pthread_t t1;
    pthread_create(&t1,NULL,&func,p);
    pthread_join(t1,NULL);
    printf("%d\n",p[0].a);



    return 0;

}
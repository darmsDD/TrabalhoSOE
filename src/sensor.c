#include "sensor.h"


void * sensor(void * args){
  
    char * keepThreading = (char *)args;
	
	pinMode(trigger, OUTPUT);
    pinMode(echo, INPUT);
    
    digitalWrite(trigger,LOW);

    printf (" Aguardando o sensor estabilizar\n");

    delay(1000);
   
    while(*keepThreading){
        //printf("Cálculo de distância \n");
        double elem[20],media=0.0;
        char leitura_invalida=0;
        short int quantidade = 10;
        for(short int i=0,j=0;i<10;i++){
            digitalWrite(trigger,HIGH);
            delayMicroseconds(10);
            digitalWrite(trigger,LOW);

            int inicia_programa,inicio_pulso,fim_pulso,duracao_pulso;
            inicia_programa = micros();

            while (digitalRead(echo)==0){
                inicio_pulso = micros();
                if((inicio_pulso - inicia_programa) > 50000){
                    leitura_invalida = 1;
                    break;
                } 
            }
            if(leitura_invalida){
                quantidade--;
                leitura_invalida=0;
                continue;
            }
            
            while(digitalRead(echo)==1){
                fim_pulso=micros();
            }

            duracao_pulso = fim_pulso - inicio_pulso;
            
            //printf("%d\n",duracao_pulso);
            
            double distance = (double)duracao_pulso* 0.017150;
            //printf("Distance: %.2lf cm\n\n",distance);
            elem[j]=distance;
            media+= distance;
            j++;
        }
        if(quantidade==0)continue;

        media/=quantidade;
        
       
        double desvio_padrao =0.0;
        for(short int i=0;i<quantidade;i++){
            desvio_padrao += (elem[i]-media) * (elem[i]-media);
        }
        desvio_padrao/=quantidade;
        if(sqrt(desvio_padrao<=1)){
            printf("Distância = %lf\n",media);
            int freio = digitalRead(IN1) &  digitalRead(IN2) &  digitalRead(IN3) &  digitalRead(IN4);
            if(media<=10 && freio !=1){
                printf("freio\n");
                digitalWrite(IN3, HIGH);
                digitalWrite(IN4, HIGH);
                digitalWrite(IN1, HIGH);
                digitalWrite(IN2, HIGH);
            }
        }
        
    }

    pthread_exit(0);
}
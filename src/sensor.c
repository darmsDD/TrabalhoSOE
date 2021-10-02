#include "sensor.h"


int trigger[]{
    frontal1_trigger,
    frontal2_trigger,
    traseiro1_trigger,
    traseiro2_trigger,
    lateral1_trigger,
    lateral2_trigger
}
int echo[]{
    frontal1_echo,
    frontal2_echo,
    traseiro1_echo,
    traseiro2_echo,
    lateral1_echo,
    lateral2_echo
}


void * sensor(void * args){
  
	struct * sensores estrutura_sensor = (struct * sensores) args;
    
    int trigger1 = trigger[estrutura_sensor->id_sensor];
    int echo1 = echo[estrutura_sensor->id_sensor];
    
    pinMode(trigger1, OUTPUT);
    pinMode(echo1, INPUT);
    
    digitalWrite(trigger1,LOW);

    printf (" Aguardando o sensor estabilizar\n");

    delay(1000);
   
    while(estrutura_sensor->continuaThread){
        //printf("Cálculo de distância \n");
        double elem[20],media=0.0;
        char leitura_invalida=0;
        short int quantidade = 10;
        for(short int i=0,j=0;i<10;i++){
            digitalWrite(trigger1,HIGH);
            delayMicroseconds(10);
            digitalWrite(trigger1,LOW);

            int inicia_programa,inicio_pulso,fim_pulso,duracao_pulso;
            inicia_programa = micros();

            while (digitalRead(echo1)==0){
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
            
            while(digitalRead(echo1)==1){
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
            //int freio = digitalRead(IN1) &  digitalRead(IN2) &  digitalRead(IN3) &  digitalRead(IN4);
            if(media<=10 && estrutura_sensor-> freio == 0){
                printf("freio\n");
                softPwmWrite(IN1,100);
                softPwmWrite(IN2,100);
                softPwmWrite(IN3,100);
                softPwmWrite(IN4,100);
                estrutura_sensor-> freio = 1;
            }
        }
        
    }

    pthread_exit(0);
}
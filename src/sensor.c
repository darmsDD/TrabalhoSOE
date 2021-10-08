#include "sensor.h"


int trigger[] = {
    frontal1_trigger,
    frontal2_trigger,
    traseiro1_trigger,
    traseiro2_trigger,
    lateral1_trigger,
    lateral2_trigger
};
int echo[] = {
    frontal1_echo,
    frontal2_echo,
    traseiro1_echo,
    traseiro2_echo,
    lateral1_echo,
    lateral2_echo
};

void * sensor(void * args){
  
	struct sensores * estrutura_sensor = (struct sensores *)  args;
    
    int cont = estrutura_sensor->num;
    int id = estrutura_sensor->id_sensor;
    int trigger1 = trigger[id];
    int echo1 = echo[id];
    
    pinMode(trigger1, OUTPUT);
    pinMode(echo1, INPUT);
    
    digitalWrite(trigger1,LOW);

    printf (" Aguardando o sensor %d estabilizar\n", id);

    delay(1000);
   
    while(*(estrutura_sensor->continuaThread)){
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
                if((fim_pulso - inicio_pulso) > 50000){
                    leitura_invalida = 1;
                    break;
                } 
            }
            
            if(leitura_invalida){
                quantidade--;
                leitura_invalida=0;
                continue;
            }
            duracao_pulso = fim_pulso - inicio_pulso;
           
            
            double distance = (double)duracao_pulso* 0.017150;
           
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
            estrutura_sensores[cont].distancia = media;
            //printf("Distância do sensor %d = %lf,\n\n\n",id,estrutura_sensores[cont].distancia);
            int freio = digitalRead(IN1) &  digitalRead(IN2) &  digitalRead(IN3) &  digitalRead(IN4);
            if(media<=10 && freio == 0 && estrutura_sensor->id_sensor==0){
                para_carrinho();
                gira_carrinho(estrutura_sensores[2].distancia,estrutura_sensores[1].distancia);
                delay(710);
                para_carrinho();
                delay(1000);
                anda_pra_frente();
            }
           
        }
        
        
    }

    pthread_exit(0);
}
#include "sensor.h"


int trigger[] = {
    frontal_esquerda_trigger,
    frontal_direita_trigger,
    traseiro_esquerdo_trigger,
    traseiro_direito_trigger,
    lateral_esquerda_trigger,
    lateral_direita_trigger
};
int echo[] = {
    frontal_esquerda_echo,
    frontal_direita_echo,
    traseiro_esquerdo_echo,
    traseiro_direito_echo,
    lateral_esquerda_echo,
    lateral_direita_echo
};

char nome_sensores [][20] = 
    {"frontal_esquerda","frontal_direita",
    "traseiro_esquerda","traseiro_direita ",
    "lateral_esquerdo","lateral_direito"};


void * sensor(void * args){
  
	struct sensores * estrutura_sensor = (struct sensores *)  args;
    
    int cont = estrutura_sensor->num;
    int id = estrutura_sensor->id_sensor;
    int trigger1 = trigger[id];
    int echo1 = echo[id];
    
    pinMode(trigger1, OUTPUT);
    pinMode(echo1, INPUT);
    
    digitalWrite(trigger1,LOW);

    printf (" Aguardando o sensor %s estabilizar\n", nome_sensores[id]);

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
            //printf("Distância do sensor %s = %lf,\n\n\n",nome_sensores[id],estrutura_sensores[cont].distancia);
            int freio = digitalRead(RODA_ESQUERDA_1) &  digitalRead(RODA_ESQUERDA_2) &  digitalRead(RODA_DIREITA_1) &  digitalRead(RODA_DIREITA_2);
            if(media<=10 && freio == 0 && (estrutura_sensor->id_sensor==0 || estrutura_sensor->id_sensor==1){
                para_carrinho();
                gira_carrinho(estrutura_sensores[3].distancia,estrutura_sensores[2].distancia);
                delay(1650);
                para_carrinho();
                delay(1000);
                anda_pra_frente();
            }
           
        }
        
        
    }

    pthread_exit(0);
}

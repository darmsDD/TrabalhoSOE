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

void gira_carrinho(int lateral1, int lateral2){
    

    if(lateral1>10){
        //gira pra esquerda
        digitalWrite(IN1,HIGH);
        digitalWrite(IN2,LOW);
        digitalWrite(IN3,HIGH);
        digitalWrite(IN4,HIGH);
        softPwmWrite(IN5,100);
    } else if(lateral2>10){
        //gira pra direita
        digitalWrite(IN1,HIGH);
        digitalWrite(IN2,HIGH);
        digitalWrite(IN3,HIGH);
        digitalWrite(IN4,LOW);
        softPwmWrite(IN6,100);
    } else{
        printf("Carrinho parando\n");
        kill(getpid(),SIGINT);
    }


}


void para_carrinho(){
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,HIGH);
    softPwmWrite(IN5,0);
}

void * sensor(void * args){
  
	struct sensores * estrutura_sensor = (struct sensores *)  args;
    //printf("%d = ",estrutura_sensor->id_sensor);
    int trigger1 = trigger[estrutura_sensor->id_sensor];
    int echo1 = echo[estrutura_sensor->id_sensor];
    
    pinMode(trigger1, OUTPUT);
    pinMode(echo1, INPUT);
    
    digitalWrite(trigger1,LOW);

    printf (" Aguardando o sensor %d estabilizar\n", estrutura_sensor->id_sensor);

    delay(1000);
    printf("%d\n",trigger1);
    printf("%d\n",echo1);
   
    while(*(estrutura_sensor->continuaThread)){
         //printf (" Aguardando o sensor %d estabilizar\n", estrutura_sensor->id_sensor);
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
            //printf("passei aqui\n");
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
            //printf("haha\n");
            //printf("%d\n",duracao_pulso);
            
            double distance = (double)duracao_pulso* 0.017150;
            //printf("Distance: %.2lf cm\n\n",distance);
            elem[j]=distance;
            media+= distance;
            j++;
        }
         //printf("keep= %d id = %d\n",*(estrutura_sensor->continuaThread),estrutura_sensor->id_sensor);
        if(quantidade==0)continue;

        media/=quantidade;
        
       
        double desvio_padrao =0.0;
        for(short int i=0;i<quantidade;i++){
            desvio_padrao += (elem[i]-media) * (elem[i]-media);
        }
        desvio_padrao/=quantidade;
        if(sqrt(desvio_padrao<=1)){
            printf("Distância do sensor %d = %lf\n\n\n",estrutura_sensor->id_sensor,media);
            delay(2000);
            int freio = digitalRead(IN1) &  digitalRead(IN2) &  digitalRead(IN3) &  digitalRead(IN4);
            if(media<=10 && freio == 0 && estrutura_sensor->id_sensor==0){
                printf("freia e gira\n");
                para_carrinho();
                delay(500);
                kill(getpid(),SIGUSR1);
            }
           
        }
        
        
    }

    pthread_exit(0);
}
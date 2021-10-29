#include "../inc/sensor.h"

pthread_mutex_t cadeado = PTHREAD_MUTEX_INITIALIZER;
int trigger[] = {
    frontal_esquerda_trigger,
    frontal_direita_trigger,
    traseiro_trigger,
    lateral_esquerda_trigger,
    lateral_direita_trigger
};
int echo[] = {
    frontal_esquerda_echo,
    frontal_direita_echo,
    traseiro_echo,
    lateral_esquerda_echo,
    lateral_direita_echo
};
int movimento_realizado=0,movimentacao=0;

char nome_sensores [][20] = 
    {"frontal_esquerda","frontal_direita",
    "traseiro","lateral_esquerdo","lateral_direito"};


void distancia_valida(int cont,double media,int id,struct sensores * estrutura_sensor)
{
    int esquerda = 1,direita=0;
    estrutura_sensores[cont].distancia = media;
    //if(id==0)printf("Distância do sensor %s = %lf,\n\n\n",nome_sensores[id],estrutura_sensores[cont].distancia);
    //delay(2000);
    if(media<=10 && (estrutura_sensor->id_sensor==frontal_esquerda || estrutura_sensor->id_sensor==frontal_direita)){
        //printf("frente\n");
        pthread_mutex_lock(&cadeado);
        //printf("frente2\n");
        
        if(movimento_realizado==1) {
            pthread_mutex_unlock(&cadeado);
            movimento_realizado=0;
            return;
        }    
        //printf("%d\n", estrutura_sensor->id_sensor);
        int lado = objeto_na_frente(1,estrutura_sensores[3].distancia,estrutura_sensores[2].distancia);
        //printf("frente3\n");
        if(lado!=-1){
            movimentacao = (lado==esquerda)?1:2;
        }
        
        movimento_realizado=1;
        pthread_mutex_unlock(&cadeado);
        
    } else if(media<=5 && (estrutura_sensor->id_sensor==lateral_esquerdo || estrutura_sensor->id_sensor==lateral_direito)){
        //printf("lateral\n");
        //pthread_mutex_lock(&cadeado);
        int lado = objeto_na_frente(0,estrutura_sensores[3].distancia,estrutura_sensores[2].distancia);
        if(lado == esquerda){
            gira_pra_direita();
            movimentacao = 3;
        } else if(lado == direita){
            gira_pra_esquerda();
            movimentacao = 4;
        }
        else{
            return;
        }
        delay(600);
        para_depois_anda();
        //pthread_mutex_unlock(&cadeado);
    }
}


void * sensor(void * args){
	struct sensores * estrutura_sensor = (struct sensores *)  args;
    int cont = estrutura_sensor->num;
    int id = estrutura_sensor->id_sensor;
    int trigger1 = trigger[id];
    int echo1 = echo[id];
    int quantidadeCerto=0,quantidadeErrada = 0;
    pinMode(trigger1, OUTPUT);
    pinMode(echo1, INPUT);
    
    digitalWrite(trigger1,LOW);

    printf (" Aguardando o sensor %s estabilizar\n", nome_sensores[id]);

    delay(1000);
    int k=1;
    unsigned int tempo=0;
    while(*(estrutura_sensor->continuaThread)){
        int init = micros();
        double elem[20],media=0.0;
        char leitura_invalida=0;
        short int quantidade = 5;
        for(short int i=0,j=0;i<5;i++){
            digitalWrite(trigger1,HIGH);
            delayMicroseconds(10);
            digitalWrite(trigger1,LOW);

            int inicia_programa,inicio_pulso,fim_pulso,duracao_pulso;
            inicia_programa = micros();
            
            while (digitalRead(echo1)==0){
                inicio_pulso = micros();
                if((inicio_pulso - inicia_programa) > 2910){
                    leitura_invalida = 1;
                    break;
                } 
               
            }
           
            // if(leitura_invalida){
            //     quantidade--;
            //     leitura_invalida=0;
            //     continue;
            // }
            
            while(digitalRead(echo1)==1){
                fim_pulso=micros();
                if((fim_pulso - inicio_pulso) > 2910){
                    leitura_invalida = 1;
                    break;
                } 
            }
            
            // if(leitura_invalida){
            //     quantidade--;
            //     leitura_invalida=0;
            //     continue;
            // }
            duracao_pulso = fim_pulso - inicio_pulso;
            double distance = (double)duracao_pulso* 0.017150;
            elem[j]=distance;
            media+= distance;
            j++;
            delayMicroseconds(200);
        }
        if(quantidade==0)continue;

        media/=quantidade;
       
        double desvio_padrao =0.0;
        for(short int i=0;i<quantidade;i++){
            desvio_padrao += (elem[i]-media) * (elem[i]-media);
        }

        desvio_padrao/=quantidade;
        if(desvio_padrao<=1){
            quantidadeCerto++;
            distancia_valida(cont,media,id,estrutura_sensor);
        } else{
            quantidadeErrada++;
        }
       
        int finish = micros();
        tempo+= finish-init;
        //printf("%d duracao total = %d(microsegundos), %d\n",k,finish-init,tempo);
        k++;
    }
    k--;
    double tempo2 = tempo/(k*1.0);
    
    arquivo_existe(id);
    FILE * teste_sensor;
    char arquivo[60] = "planilhaSensores/";
    strncat(arquivo,nome_sensores[id],20);
    teste_sensor = fopen(arquivo,"a");
    
    fprintf(teste_sensor,"%s, %d, %lf, %lf%%\n",nome_sensores[id],k,tempo2,(quantidadeCerto*100.0)/(quantidadeCerto+quantidadeErrada));
    fclose(teste_sensor);
    pthread_exit(0);
}

void libera_lock(){
    pthread_mutex_unlock(&cadeado);
}

void arquivo_existe(int id){
    FILE * teste_sensor;
    char arquivo[60] = "planilhaSensores/";
    strncat(arquivo,nome_sensores[id],20);
    
    teste_sensor = fopen(arquivo,"r");
    if(teste_sensor){
        fclose(teste_sensor);
        return;
    }else{
        teste_sensor = fopen(arquivo,"a");
        fprintf(teste_sensor,"Sensor, Leituras, Tempo Médio, Taxa de leituras corretas\n");
        fclose(teste_sensor);
    }

}
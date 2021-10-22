#include "main.h"



extern pthread_mutex_t cadeado;
extern pthread_mutex_t cadeado_mapa;

void desligaSistema(){
    
    keepThreading=0;
    para_carrinho();
    pthread_join(t_mapa,NULL);
    pthread_join(t_obstaculos,NULL);
    imprime_mapa();
   
    pthread_join(sensor_frontal[0],NULL);
    pthread_join(sensor_lateral[0],NULL);
    pthread_join(sensor_lateral[1],NULL);
    pthread_join(sensor_frontal[1],NULL);
    pthread_join(sensor_traseiro,NULL);
    pthread_mutex_destroy(&cadeado);
    digitalWrite(frontal_esquerda_trigger,LOW);
    digitalWrite(lateral_esquerda_trigger,LOW);
    digitalWrite(lateral_direita_trigger,LOW);
   
    exit(0);
}


int main()
{


    signal(SIGINT,desligaSistema);
	wiringPiSetup();
    
    
    int id[]={frontal_esquerda,frontal_direita,lateral_esquerdo,lateral_direito,traseiro};
    for(int i=0;i<5;i++){
        estrutura_sensores[i].id_sensor = id[i];
        estrutura_sensores[i].continuaThread = &keepThreading ;
        estrutura_sensores[i].num = i;
    }

    pthread_create(&sensor_frontal[0],NULL,&sensor,&estrutura_sensores[0]);
    pthread_create(&sensor_frontal[1],NULL,&sensor,&estrutura_sensores[1]);
    pthread_create(&sensor_lateral[0],NULL,&sensor,&estrutura_sensores[2]);
    pthread_create(&sensor_lateral[1],NULL,&sensor,&estrutura_sensores[3]);
    pthread_create(&sensor_traseiro,NULL,&sensor,&estrutura_sensores[4]);
    
   

    inicia_motor();

    delay(2000);
    pthread_create(&t_obstaculos,NULL,&obstaculos,&estrutura_sensores);
    delay(1000);
    pthread_create(&t_mapa,NULL,&desenha_mapa,&estrutura_sensores[0]);
    for(int i=0;i<10;i++){
        printf("%ds\n",i);
        delay(1000);
    }
    anda_pra_frente();

    while(1){
        printf("Digite\n1 para sentido horário\n2 para anti-horário\n3 para ponto morto\n4 para freio\n");
        printf("5 para girar para direita\n6 para gira para esquerda\n\n");
        char opcao;
        scanf(" %c",&opcao);
        switch (opcao)
        {
        case  '1'/* horário */:
            anda_pra_frente();
            break;
        case  '2'/* anti-horário */:
            anda_pra_tras();
            break;
        case  '3'/* ponto morto */:
            ponto_morto();
            break;
        case  '4'/* freio */:
            para_carrinho();
            break;
        
        case '5'/* giro pra direita*/:
            gira_pra_direita();
            break;

        case '6'/* giro pra esquerda*/:
            gira_pra_esquerda();
            break;

        default:
            break;
        }
    }
    
    
	return 0;
}

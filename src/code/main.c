#include "../inc/main.h"



extern pthread_mutex_t cadeado;
extern pthread_mutex_t cadeado_mapa;

void desligaSistema(){
    
    keepThreading=0;
    para_carrinho();
    pthread_join(t_mapa,NULL);
    pthread_join(t_obstaculos,NULL);
    libera_lock();
   
    pthread_join(sensor_frontal[0],NULL);
    pthread_join(sensor_lateral[0],NULL);
    pthread_join(sensor_lateral[1],NULL);
    pthread_join(sensor_frontal[1],NULL);
    pthread_join(sensor_traseiro,NULL);
    pthread_mutex_destroy(&cadeado);
    digitalWrite(frontal_esquerda_trigger,LOW);
    digitalWrite(lateral_esquerda_trigger,LOW);
    digitalWrite(lateral_direita_trigger,LOW);
   

    imprime_mapa();

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

    inicia_motor();
    
    

    //pthread_create(&sensor_frontal[0],NULL,&sensor,&estrutura_sensores[0]);
    // pthread_create(&sensor_frontal[1],NULL,&sensor,&estrutura_sensores[1]);
    // pthread_create(&sensor_lateral[0],NULL,&sensor,&estrutura_sensores[2]);
    // pthread_create(&sensor_lateral[1],NULL,&sensor,&estrutura_sensores[3]);
    // pthread_create(&sensor_traseiro,NULL,&sensor,&estrutura_sensores[4]);
    
    cria_thread_com_prioridade(&sensor_frontal[0],99,&sensor,&estrutura_sensores[0]);
    cria_thread_com_prioridade(&sensor_frontal[1],99,&sensor,&estrutura_sensores[1]);
    cria_thread_com_prioridade(&sensor_lateral[0],50,&sensor,&estrutura_sensores[2]);
    cria_thread_com_prioridade(&sensor_lateral[1],50,&sensor,&estrutura_sensores[3]);
    cria_thread_com_prioridade(&sensor_traseiro,50,&sensor,&estrutura_sensores[4]);

    

    //delay(2000);
    for(int i=5;i>0;i--){
        printf("%ds\n",i);
        delay(1000);
    }
    
    

    //delay(2000);
    cria_thread_com_prioridade(&t_obstaculos,40,&obstaculos,&estrutura_sensores);
    cria_thread_com_prioridade(&t_mapa,40,&desenha_mapa,&keepThreading);

    //  pthread_create(&t_obstaculos,NULL,&obstaculos,&estrutura_sensores);
    //  pthread_create(&t_mapa,NULL,&desenha_mapa,&keepThreading);
    anda_pra_frente();

    while(1){
        printf("Digite\n1 para sentido hor??rio\n2 para anti-hor??rio\n3 para ponto morto\n4 para freio\n");
        printf("5 para girar para direita\n6 para gira para esquerda\n\n");
        char opcao;
        scanf(" %c",&opcao);
        switch (opcao)
        {
        case  '1'/* hor??rio */:
            anda_pra_frente();
            break;
        case  '2'/* anti-hor??rio */:
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

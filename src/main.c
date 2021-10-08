#include "main.h"

void desligaSistema(int signal){
    
    para_carrinho();
    keepThreading=0;
    printf("hahha\n");
    pthread_join(sensor_frontal[0],NULL);
   //pthread_join(sensor_frontal[1],NULL);
    pthread_join(sensor_lateral[0],NULL);
    pthread_join(sensor_lateral[1],NULL);
    //pthread_join(sensor_traseiro[0],NULL);
    printf("hahha2\n");
    digitalWrite(frontal1_trigger,LOW);
    digitalWrite(lateral1_trigger,LOW);
    digitalWrite(lateral2_trigger,LOW);
    exit(0);
}


int main()
{

    //mapas();
    //return 0;

    signal(SIGINT,desligaSistema);
 // Pino GPIO4 é o 7 na WiringPi
	wiringPiSetup();
    
    
    int id[]={0,4,5};
    for(int i=0;i<3;i++){
        estrutura_sensores[i].id_sensor = id[i];
        estrutura_sensores[i].continuaThread = &keepThreading ;
        estrutura_sensores[i].num = i;
    }

    pthread_create(&sensor_frontal[0],NULL,&sensor,&estrutura_sensores[0]);
    pthread_create(&sensor_lateral[0],NULL,&sensor,&estrutura_sensores[1]);
    pthread_create(&sensor_lateral[1],NULL,&sensor,&estrutura_sensores[2]);
    /*pthread_create(&sensor_frontal[1],NULL,&sensor,&estrutura_sensores[1]);
    pthread_create(&sensor_traseiro[0],NULL,&sensor,&estrutura_sensores[2]);
    pthread_create(&sensor_traseiro[1],NULL,&sensor,&estrutura_sensores[3]);
    pthread_create(&sensor_lateral[0],NULL,&sensor,&estrutura_sensores[4]);
    //pthread_create(&sensor_lateral[1],NULL,&sensor,&estrutura_sensores[5]);
    */

    inicia_motor();

    delay(2000);
  
    while(1){
        printf("Digite 1 para sentido horário\n2 para anti-horário\n3 para ponto morto\n4 para freio\n5 para girar para direita\n6 para gira para esquerda\n");
        char opcao;
        scanf(" %c",&opcao);
        int velocidade;
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
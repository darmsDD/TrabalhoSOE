#include "main.h"

void desligaSistema(int signal){
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,HIGH);
    
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

void giroCarrinho(int signal){

    gira_carrinho(estrutura_sensores[1].distancia,estrutura_sensores[2].distancia);
    delay(500);
    para_carrinho();


}

int main()
{

    //mapas();
    //return 0;

    signal(SIGUSR1,giroCarrinho);
    signal(SIGINT,desligaSistema);
 // Pino GPIO4 é o 7 na WiringPi
	wiringPiSetup();
    
    
    int id[]={0,4,5};
    for(int i=0;i<3;i++){
        estrutura_sensores[i].id_sensor = id[i];
        estrutura_sensores[i].continuaThread = &keepThreading ;
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


    //delay(2000);

    pinMode(IN1,OUTPUT);
    pinMode(IN2,OUTPUT);
    pinMode(IN3,OUTPUT);
    pinMode(IN4,OUTPUT);
    softPwmCreate(IN5,0,100);
    softPwmCreate(IN6,0,100);
  
    while(1){
        printf("Digite 1 para sentido horário\n2 para anti-horário\n3 para ponto morto\n4 para freio\n");
        char opcao;
        scanf(" %c",&opcao);
        int velocidade;
        switch (opcao)
        {
        case  '1'/* horário */:
            
            printf("Digite a velocidade\n");
            //scanf("%d",&velocidade);
            digitalWrite(IN1,LOW);
            digitalWrite(IN2,HIGH);
            digitalWrite(IN3, LOW);
            digitalWrite(IN4, HIGH);
            softPwmWrite(IN6,100);
            softPwmWrite(IN5,100);
            
            break;
        case  '2'/* anti-horário */:
            digitalWrite(IN3, HIGH);
            digitalWrite(IN4, LOW);
            digitalWrite(IN1, HIGH);
            digitalWrite(IN2, LOW);
            softPwmWrite(IN5,100);
            softPwmWrite(IN6,100);
            break;
        case  '3'/* ponto morto */:
            
            digitalWrite(IN1, LOW);
            digitalWrite(IN2, LOW);
            digitalWrite(IN3, LOW);
            digitalWrite(IN4, LOW);
            //softPwmWrite(IN5,0);
            //softPwmWrite(IN6,0);
            break;
        case  '4'/* freio */:

            digitalWrite(IN1, HIGH);
            digitalWrite(IN2, HIGH);
            digitalWrite(IN3, HIGH);
            digitalWrite(IN4, HIGH);
            //softPwmWrite(IN5,0);
            //softPwmWrite(IN6,0);
            break;
        
        case '5'/* giro pra direita*/:

            digitalWrite(IN1, LOW);
            digitalWrite(IN2, HIGH);
            digitalWrite(IN3, HIGH);
            digitalWrite(IN4, HIGH);
            softPwmWrite(IN5,100);
            //softPwmWrite(IN6,0);
            break;

        case '6'/* giro pra esquerda*/:

            digitalWrite(IN1, HIGH);
            digitalWrite(IN2, HIGH);
            digitalWrite(IN3, LOW);
            digitalWrite(IN4, HIGH);
            softPwmWrite(IN6,100);
            //softPwmWrite(IN6,0);
            break;

        default:
            break;
        }




    }
    
    
	return 0;
}
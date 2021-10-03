#include "main.h"

void desligaSistema(int signal){
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,HIGH);
    
    keepThreading=0;
    pthread_join(sensor_frontal[0],NULL);
    digitalWrite(frontal1_trigger,LOW);
    exit(0);
}

int main()
{

    signal(SIGINT,desligaSistema);
 // Pino GPIO4 é o 7 na WiringPi
	wiringPiSetup();
    
    struct sensores estrutura_sensores[5];
    for(int i=0;i<5;i++){
        estrutura_sensores[i].id_sensor = i;
        estrutura_sensores[i].continuaThread = &keepThreading ;
    }
    pthread_create(&sensor_frontal[0],NULL,&sensor,&estrutura_sensores[0]);
    pthread_create(&sensor_frontal[1],NULL,&sensor,&estrutura_sensores[1]);
    pthread_create(&sensor_traseiro[0],NULL,&sensor,&estrutura_sensores[2]);
    pthread_create(&sensor_traseiro[1],NULL,&sensor,&estrutura_sensores[3]);
    pthread_create(&sensor_lateral[0],NULL,&sensor,&estrutura_sensores[4]);
    //pthread_create(&sensor_lateral[1],NULL,&sensor,&estrutura_sensores[5]);
    


    delay(2000);

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
            scanf("%d",&velocidade);
            digitalWrite(IN1,LOW);
            digitalWrite(IN2,HIGH);
            digitalWrite(IN3, LOW);
            digitalWrite(IN4, HIGH);
            softPwmWrite(IN6,velocidade);
            softPwmWrite(IN5,velocidade - 5);
            
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
        
        
        default:
            break;
        }




    }
    
    
	return 0;
}
#include "main.h"

void desligaSistema(int signal){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    digitalWrite(trigger,LOW);
    exit(0);
}

void motorPodeSerLigado(int signal){
    printf("Robô está mais longe, ative os motores conforme desejar\n");
}

int main()
{

    signal(SIGINT,desligaSistema);
    signal(SIGUSR1,motorPodeSerLigado);
 // Pino GPIO4 é o 7 na WiringPi
	wiringPiSetup();
    pthread_t sensor_id;
    double distancia;
    pthread_create(&sensor_id,NULL,&sensor,&distancia);
    sleep(2);

	pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
  
    while(1){
        printf("Digite 1 para sentido horário\n2 para anti-horário\n3 para ponto morto\n4 para freio\n");
        char opcao;
        scanf(" %c",&opcao);
        if(distancia<10){
            printf("O carrinho está muito perto, motores desligando");
            digitalWrite(IN1, LOW);
            digitalWrite(IN2, LOW);
            digitalWrite(IN3, LOW);
            digitalWrite(IN4, LOW);
            pause();
            scanf(" %c",&opcao);
        }
        switch (opcao)
        {
        case  '1'/* horário */:
            digitalWrite(IN3, HIGH);
            digitalWrite(IN4, LOW);
            digitalWrite(IN1, HIGH);
            digitalWrite(IN2, LOW);
            
            break;
        case  '2'/* anti-horário */:
            digitalWrite(IN1, LOW);
            digitalWrite(IN2, HIGH);
            digitalWrite(IN3, LOW);
            digitalWrite(IN4, HIGH);
            break;
        case  '3'/* ponto morto */:
            digitalWrite(IN1, LOW);
            digitalWrite(IN2, LOW);
            digitalWrite(IN3, LOW);
            digitalWrite(IN4, LOW);
            break;
        case  '4'/* freio */:
            digitalWrite(IN1, HIGH);
            digitalWrite(IN2, HIGH);
            digitalWrite(IN3, HIGH);
            digitalWrite(IN4, HIGH);
            break;
        
        
        default:
            break;
        }




    }


   
    pause();
    
    
	return 0;
}
#include "main.h"


pthread_t sensor_id;
void desligaSistema(int signal){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    pthread_cancel(sensor_id);
    digitalWrite(trigger,LOW);
    exit(0);
}

void pertoObjeto(int signal){
    printf("Robo está muito perto, parando\n");
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, HIGH);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);
    delay(1000);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    kill(getpid(),SIGUSR2);

}

int main()
{

    signal(SIGINT,desligaSistema);
    signal(SIGUSR1,pertoObjeto);
 // Pino GPIO4 é o 7 na WiringPi
	wiringPiSetup();
   
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
        
        switch (opcao)
        {
        case  '1'/* horário */:
            digitalWrite(IN1, LOW);
            digitalWrite(IN2, HIGH);
            digitalWrite(IN3, LOW);
            digitalWrite(IN4, HIGH);
            
            break;
        case  '2'/* anti-horário */:
            digitalWrite(IN3, HIGH);
            digitalWrite(IN4, LOW);
            digitalWrite(IN1, HIGH);
            digitalWrite(IN2, LOW);
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
    
    
	return 0;
}
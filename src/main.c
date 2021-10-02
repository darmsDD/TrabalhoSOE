#include "main.h"

void desligaSistema(int signal){
    softPwmWrite(IN1,0);
    softPwmWrite(IN2,0);
    softPwmWrite(IN3,0);
    softPwmWrite(IN4,0);
    
    keepThreading=0;
    pthread_join(sensor_id,NULL);
    digitalWrite(trigger,LOW);
    exit(0);
}

int main()
{

    int freio =0;
    signal(SIGINT,desligaSistema);
 // Pino GPIO4 é o 7 na WiringPi
	wiringPiSetup();
    
    struct sensores estrutura_sensores;
    estrutura_sensores.id_sensor;
    estrutura_sensores.continuaThread = &keepThreading ;
    estrutura_sensores.freio = &freio;
    pthread_create(&sensor_frontal[0],NULL,&sensor,&estrutura_sensores);
   /* pthread_create(&sensor_frontal[1],NULL,&sensor,&keepThreading);
    pthread_create(&sensor_lateral[0],NULL,&sensor,&keepThreading);
    pthread_create(&sensor_lateral[1],NULL,&sensor,&keepThreading);
    pthread_create(&sensor_traseiro[0],NULL,&sensor,&keepThreading);
    pthread_create(&sensor_traseiro[1],NULL,&sensor,&keepThreading);
    */
    


    sleep(2);

    softPwmCreate(IN1, 0, 100);
    softPwmCreate(IN2, 0, 100);
    softPwmCreate(IN3, 0, 100);
    softPwmCreate(IN4, 0, 100);
    
  
    while(1){
        printf("Digite 1 para sentido horário\n2 para anti-horário\n3 para ponto morto\n4 para freio\n");
        char opcao;
        scanf(" %c",&opcao);
        
        switch (opcao)
        {
        case  '1'/* horário */:
            freio=0;
            softPwmWrite(IN1,0);
            softPwmWrite(IN2,30);
            softPwmWrite(IN3,0);
            softPwmWrite(IN4,30);

            //digitalWrite(IN1, LOW);
            //digitalWrite(IN2, HIGH);
            //digitalWrite(IN3, LOW);
            //digitalWrite(IN4, HIGH);
            
            break;
        case  '2'/* anti-horário */:
            freio = 0;
            softPwmWrite(IN1,30);
            softPwmWrite(IN2,0);
            softPwmWrite(IN3,30);
            softPwmWrite(IN4,0);

            //digitalWrite(IN3, HIGH);
            //digitalWrite(IN4, LOW);
            //digitalWrite(IN1, HIGH);
            //digitalWrite(IN2, LOW);
            break;
        case  '3'/* ponto morto */:
            freio = 0;
            softPwmWrite(IN1,0);
            softPwmWrite(IN2,0);
            softPwmWrite(IN3,0);
            softPwmWrite(IN4,0);


            //digitalWrite(IN1, LOW);
            //digitalWrite(IN2, LOW);
            //digitalWrite(IN3, LOW);
            //digitalWrite(IN4, LOW);
            break;
        case  '4'/* freio */:

            softPwmWrite(IN1,100);
            softPwmWrite(IN2,100);
            softPwmWrite(IN3,100);
            softPwmWrite(IN4,100);
            freio = 1;

            //digitalWrite(IN1, HIGH);
            //digitalWrite(IN2, HIGH);
            //digitalWrite(IN3, HIGH);
            //digitalWrite(IN4, HIGH);
            break;
        
        
        default:
            break;
        }




    }
    
    
	return 0;
}
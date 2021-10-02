#include <wiringPi.h>
#include <unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>

int IN1 = 7,IN2=9,IN3=15,IN4=16;

void paraMotor(int signal){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    exit(0);
}

int main()
{

    signal(SIGINT,paraMotor);
 // Pino GPIO4 é o 7 na WiringPi
	wiringPiSetup();
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
        case  '1'  :
            digitalWrite(IN1, HIGH);
            digitalWrite(IN2, LOW);
            digitalWrite(IN3, HIGH);
            digitalWrite(IN4, LOW);
            break;
        case  '2'  :
            digitalWrite(IN1, LOW);
            digitalWrite(IN2, HIGH);
            digitalWrite(IN3, LOW);
            digitalWrite(IN4, HIGH);
            break;
        case  '3'  :
            digitalWrite(IN1, LOW);
            digitalWrite(IN2, LOW);
            digitalWrite(IN3, LOW);
            digitalWrite(IN4, LOW);
            break;
        case  '4' :
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
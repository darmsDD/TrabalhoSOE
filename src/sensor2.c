#include <wiringPi.h>
#include<stdio.h>




 
int main(){ 
    // Pino GPIO4 é o 7 na WiringPi
    int trigger = 7,echo =0;
	wiringPiSetup();
	pinMode(trigger, OUTPUT);
    pinMode(echo, INPUT);
    
    digitalWrite(trigger,LOW);

    printf (" Aguardando o sensor estabilizar\n");

    delay(1000);
   
        //printf("Cálculo de distância \n");
    
    digitalWrite(trigger,HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger,LOW);

    int inicio_pulso,fim_pulso,duracao_pulso;
    
    while (digitalRead(echo)==0){
       inicio_pulso = micros(); 
        
    }
    
    while(digitalRead(echo)==1){
        fim_pulso=micros();
    }

    duracao_pulso = fim_pulso - inicio_pulso;
    
    printf("%d\n",duracao_pulso);
    
    double distance = (double)duracao_pulso*1.0e-6 * 17150;
    printf("Distance: %.2lf cm\n\n",distance);
    return 0;
}
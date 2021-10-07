#include "motor.h"

void gira_carrinho(int lateral1, int lateral2){
    if(lateral1>10){
        //gira pra esquerda
        digitalWrite(IN1,HIGH);
        digitalWrite(IN2,LOW);
        digitalWrite(IN3,HIGH);
        digitalWrite(IN4,HIGH);
        softPwmWrite(IN5,100);
    } else if(lateral2>10){
        //gira pra direita
        digitalWrite(IN1,HIGH);
        digitalWrite(IN2,HIGH);
        digitalWrite(IN3,HIGH);
        digitalWrite(IN4,LOW);
        softPwmWrite(IN6,100);
    } else{
        printf("Carrinho parando\n");
        kill(getpid(),SIGINT);
    }


}


void para_carrinho(){
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,HIGH);
    softPwmWrite(IN5,0);
    softPwmWrite(IN6,0);
}

void anda_pra_frente(){
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    softPwmWrite(IN6,100);
    softPwmWrite(IN5,100);
}

void anda_pra_tras(){
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    softPwmWrite(IN5,100);
    softPwmWrite(IN6,100);
}
#include "motor.h"

void gira_carrinho(double lateral1, double lateral2){
    printf("lateral1:%lf lateral2:%lf\n",lateral1,lateral2);
    if(lateral1>10){
        printf("gira esquerda\n");
        //gira pra esquerda
        gira_pra_esquerda();
    } else if(lateral2>10){
        printf("gira direita\n");
        //gira pra direita
        gira_pra_direita();
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

void gira_pra_direita(){
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
    softPwmWrite(IN6,100);
    softPwmWrite(IN5,0);
}

void gira_pra_esquerda(){
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,HIGH);
    softPwmWrite(IN5,100);
    softPwmWrite(IN6,0);
}

void ponto_morto(){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}

void inicia_motor(){
    pinMode(IN1,OUTPUT);
    pinMode(IN2,OUTPUT);
    pinMode(IN3,OUTPUT);
    pinMode(IN4,OUTPUT);
    softPwmCreate(IN5,0,100);
    softPwmCreate(IN6,0,100);
}
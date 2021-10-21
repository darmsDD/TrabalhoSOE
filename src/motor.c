#include "motor.h"

void gira_carrinho(double lateral_esquerda, double lateral_direita){
    
    if(lateral_esquerda>10){
        gira_pra_esquerda();
    } else if(lateral_direita>10){
        gira_pra_direita();
    } else{
        para_carrinho();
    }

}


void para_carrinho(){
    digitalWrite(RODA_ESQUERDA_1,HIGH);
    digitalWrite(RODA_ESQUERDA_2,HIGH);
    digitalWrite(RODA_DIREITA_1,HIGH);
    digitalWrite(RODA_DIREITA_2,HIGH);
    softPwmWrite(PWM_RODA_ESQUERDA,0);
    softPwmWrite(PWM_RODA_DIREITA,0);
}

void anda_pra_frente(){
    digitalWrite(RODA_ESQUERDA_1,LOW);
    digitalWrite(RODA_ESQUERDA_2,HIGH);
    digitalWrite(RODA_DIREITA_1, LOW);
    digitalWrite(RODA_DIREITA_2, HIGH);
    softPwmWrite(PWM_RODA_DIREITA,80);
    softPwmWrite(PWM_RODA_ESQUERDA,100);
}

void anda_pra_tras(){
    digitalWrite(RODA_DIREITA_1, HIGH);
    digitalWrite(RODA_DIREITA_2, LOW);
    digitalWrite(RODA_ESQUERDA_1, HIGH);
    digitalWrite(RODA_ESQUERDA_2, LOW);
    softPwmWrite(PWM_RODA_ESQUERDA,100);
    softPwmWrite(PWM_RODA_DIREITA,80);
}

void gira_pra_direita(){
    digitalWrite(RODA_ESQUERDA_1,HIGH);
    digitalWrite(RODA_ESQUERDA_2,HIGH);
    digitalWrite(RODA_DIREITA_1,HIGH);
    digitalWrite(RODA_DIREITA_2,LOW);
    softPwmWrite(PWM_RODA_DIREITA,100);
    softPwmWrite(PWM_RODA_ESQUERDA,0);
}

void gira_pra_esquerda(){
    digitalWrite(RODA_ESQUERDA_1,HIGH);
    digitalWrite(RODA_ESQUERDA_2,LOW);
    digitalWrite(RODA_DIREITA_1,HIGH);
    digitalWrite(RODA_DIREITA_2,HIGH);
    softPwmWrite(PWM_RODA_ESQUERDA,100);
    softPwmWrite(PWM_RODA_DIREITA,0);
}

void ponto_morto(){
    digitalWrite(RODA_ESQUERDA_1, LOW);
    digitalWrite(RODA_ESQUERDA_2, LOW);
    digitalWrite(RODA_DIREITA_1, LOW);
    digitalWrite(RODA_DIREITA_2, LOW);
}

void inicia_motor(){
    pinMode(RODA_ESQUERDA_1,OUTPUT);
    pinMode(RODA_ESQUERDA_2,OUTPUT);
    pinMode(RODA_DIREITA_1,OUTPUT);
    pinMode(RODA_DIREITA_2,OUTPUT);
    softPwmCreate(PWM_RODA_ESQUERDA,0,100);
    softPwmCreate(PWM_RODA_DIREITA,0,100);
}

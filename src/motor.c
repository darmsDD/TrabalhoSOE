#include "motor.h"

int gira_carrinho(double lateral_esquerda, double lateral_direita){
    int retorna = 0;
    if(lateral_esquerda>30){
        gira_pra_esquerda();
        retorna = 1;
    } else if(lateral_direita>30){
        gira_pra_direita();
        retorna = 0;
    } else{
        retorna = -1;
        para_carrinho();
    }
    return retorna;


}

int objeto_na_frente(int opcao, double sensor_esquerdo,double sensor_direito){
    //printf("etapa1\n");
    para_carrinho();
    delay(2000);
    int lado = gira_carrinho(sensor_esquerdo,sensor_direito);
    /qprintf("etapa2\n");
    if(opcao==1){
        delay(1650);
    } else {
        delay(800);
    }
    
    if(lado!=-1){para_depois_anda();}
    //printf("etapa3\n");
    return lado;
}

void para_depois_anda(){
    para_carrinho();
    delay(1000);
    anda_pra_frente();
    //delay(1000);
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

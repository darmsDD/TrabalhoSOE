#include <wiringPi.h>
#include<stdio.h>
#include<math.h>



 
int main(){ 
    // Pino GPIO4 é o 7 na WiringPi
    int trigger = 7,echo =0;
	wiringPiSetup();
	pinMode(trigger, OUTPUT);
    pinMode(echo, INPUT);
    
    digitalWrite(trigger,LOW);

    printf (" Aguardando o sensor estabilizar\n");

    delay(1000);
    for(short int j=1;j<=10;j++){
        //printf("Cálculo de distância \n");
        double elem[20],media=0.0;
        char leitura_invalida=0;
        for(short int i=0;i<20;i++){
            digitalWrite(trigger,HIGH);
            delayMicroseconds(10);
            digitalWrite(trigger,LOW);

            int inicia_programa,inicio_pulso,fim_pulso,duracao_pulso;
            inicia_programa = micros();

            while (digitalRead(echo)==0){
                inicio_pulso = micros();
                if((inicio_pulso - inicia_programa)*10e-6 > 2){
                    leitura_invalida = 1;
                    break;
                } 
            }
            if(leitura_invalida){
                continue;
            }
            
            while(digitalRead(echo)==1){
                fim_pulso=micros();
            }

            duracao_pulso = fim_pulso - inicio_pulso;
            
            //printf("%d\n",duracao_pulso);
            
            double distance = (double)duracao_pulso*1.0e-6 * 17150;
            //printf("Distance: %.2lf cm\n\n",distance);
            elem[i]=distance;
            media+=distance;
        }
        media/=20;
        double desvio_padrao =0.0;
        for(short int i=0;i<20;i++){
            desvio_padrao += (elem[i]-media) * (elem[i]-media);
        }
        desvio_padrao/=20;
        if(sqrt(desvio_padrao<0.3)){
            printf("%d- Distância = %lf\n",j,media);
        } else{
            printf("%d- Descarta distância = %lf\n",j,media);
        }
    
       
    }
    return 0;
}
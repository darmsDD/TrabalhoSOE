#include <wiringPi.h>
#include <unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<time.h>
#include<math.h>

int trigger = 7,echo =0;
void paraMotor(int signal){
    digitalWrite(trigger, LOW);
    
    exit(0);
}

int main()
{


    signal(SIGINT,paraMotor);
 // Pino GPIO4 é o 7 na WiringPi
	wiringPiSetup();
	pinMode(trigger, OUTPUT);
    pinMode(echo, INPUT);
    
    digitalWrite(trigger,LOW);

    printf (" Aguardando o sensor estabilizar\n");

    sleep(2);
    double total=0,ant=-1,ant2=-1;
    char flag =0;
    int quantidade=20;
    for(char i = 0;i<20;i++){
        //printf("Cálculo de distância \n");

        struct timespec tstart={0,0}, tend={0,0}, tbegin= {0,0};
        clock_gettime(CLOCK_MONOTONIC, &tbegin);
        digitalWrite(trigger,HIGH);
        usleep(10);
        digitalWrite(trigger,LOW);

        double pulse_start_time,pulse_end_time,pulse_duration;
        
        while (digitalRead(echo)==0){
            clock_gettime(CLOCK_MONOTONIC, &tstart);
            if(tstart.tv_sec - tbegin.tv_sec>4){
                continue;
            }
            
        }
        
        while(digitalRead(echo)==1){
            clock_gettime(CLOCK_MONOTONIC, &tend);
        }
        
        // printf("N1%d\n",tstart.tv_nsec);
        // printf("S1 %d\n",tstart.tv_sec);
        // printf("N2 %d\n",tend.tv_nsec);
        // printf("S2%d\n",tend.tv_sec);


        pulse_end_time = (double)tend.tv_sec + 1.0e-9*tend.tv_nsec;
        // printf("%.9lf\n",pulse_end_time);
        pulse_start_time = (double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec;
        // printf("%.9lf\n",pulse_start_time);
        pulse_duration = pulse_end_time - pulse_start_time;
        
        double distance = pulse_duration * 17150;
        printf("Distance: %.2lf cm\n\n",distance);

        
        if(flag==1){
            if(fabs(distance-ant)>3){
                total+= ant2 + distance;
            } else{
                total+= ant + distance;
                ant2= ant;
            } 
            ant=distance;
            flag=0;
            continue;
        }


        else if(fabs(distance-ant)>3 && i>0){
           if(i==2){
               total-=ant;
               ant2 = ant;
               ant = distance;
               flag=1;
           } 
            quantidade--;
            printf("Fora da curva\n");
            continue;
           
        }

        ant2 = ant;
        ant = distance;
        total+=distance;
        //usleep(1000);
    }
    
    printf("Total = %lf \n",total/quantidade);
  
    
    
    
	return 0;
}
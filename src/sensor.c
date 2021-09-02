#include <wiringPi.h>
#include <unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<time.h>

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

    printf("Cálculo de distância ");

    digitalWrite(trigger,HIGH);
    usleep(10);
    digitalWrite(trigger,LOW);

    double pulse_start_time,pulse_end_time,pulse_duration;
    struct timespec tstart={0,0}, tend={0,0};
    while (digitalRead(echo)==0){
        clock_gettime(CLOCK_MONOTONIC, &tstart);
    }
    while(digitalRead(echo)==1){
        clock_gettime(CLOCK_MONOTONIC, &tend);
    }
      pulse_end_time = (double)tend.tv_sec + 1.0e-9*tend.tv_nsec;
      pulse_start_time = (double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec;
      pulse_duration = pulse_end_time - pulse_start_time;
      double distance = pulse_duration * 17150;
      printf("Distance: %.2lf cm",distance);


  
    
    
    
	return 0;
}
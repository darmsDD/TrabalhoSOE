WFLAGS = -W -Wall -Wshadow -pedantic -lwiringPi -lpthread -lm
all: sensorOriginal sensor2 motor

motor: motor.c 
	gcc $(WFLAGS) -o motor.out motor.c

sensorOriginal: sensorOriginal.c
	gcc $(WFLAGS) -o sensorOriginal.out sensorOriginal.c

sensor2: sensor2.c
	gcc $(WFLAGS) -o sensor2.out sensor2.c

clean:
	rm -f *.o *.out
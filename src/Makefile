WFLAGS = -W -Wall -Wshadow -pedantic -lwiringPi
all: motor.out sensor.out
motor.out: motor.c
	gcc $(WFLAGS) -o motor.out motor.c
sensor.out: sensor.c
	gcc $(WFLAGS) -o sensor.out sensor.c

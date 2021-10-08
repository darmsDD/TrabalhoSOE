WFLAGS = -W -Wall -Wshadow -pedantic -lwiringPi -lpthread -lm
all: main.out 
main.out : main.o sensor.o motor.o
	gcc $(WFLAGS) main.o sensor.o  motor.o -o main.out
main.o: main.c
	gcc $(WFLAGS) -c main.c
sensor.o: sensor.c
	gcc $(WFLAGS) -c sensor.c
motor.o:
	gcc $(WFLAGS) -c motor.c

clean:
	rm -f *.o *.out
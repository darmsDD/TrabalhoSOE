WFLAGS = -W -Wall -Wshadow -pedantic -lwiringPi -lpthread -lm
all: main.out
	./main.out
main.out : main.o sensor.o motor.o mapa.o prioridadeThread.o
	gcc $(WFLAGS) main.o sensor.o  motor.o mapa.o prioridadeThread.o -o main.out
main.o: code/main.c
	gcc $(WFLAGS) -c code/main.c
sensor.o: code/sensor.c
	gcc $(WFLAGS) -c code/sensor.c
motor.o: code/motor.c
	gcc $(WFLAGS) -c code/motor.c
mapa.o: code/mapa.c
	gcc $(WFLAGS) -c code/mapa.c
prioridadeThread.o: code/prioridadeThread.c
	gcc $(WFLAGS) -c code/prioridadeThread.c

clean:
	rm -f *.o *.out
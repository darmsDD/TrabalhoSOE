WFLAGS = -W -Wall -Wshadow -pedantic -lwiringPi -lpthread
all: main.out 
main.out : main.o sensor.o
	gcc $(WFLAGS) main.o sensor.o -o main.out
main.o: main.c
	gcc $(WFLAGS) -c main.c
sensor.o: sensor.c
	gcc $(WFLAGS) -c sensor.c

sensorOriginal: sensorOriginal.c
	gcc $(WFLAGS) -o sensorOriginal.out sensorOriginal.c
	./sensorOriginal.out

sensor2: sensor2.c
	gcc $(WFLAGS) -o sensor2.out sensor2.c
	./sensor2.out
clean:
	rm -f *.o *.out
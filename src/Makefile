WFLAGS = -W -Wall -Wshadow -pedantic -lwiringPi -lpthread -lm
all: main.out 
main.out : main.o sensor.o mapa.o
	gcc $(WFLAGS) main.o sensor.o  mapa.o -o main.out
main.o: main.c
	gcc $(WFLAGS) -c main.c
sensor.o: sensor.c
	gcc $(WFLAGS) -c sensor.c
mapa.o:
	gcc $(WFLAGS) -c mapa.c

clean:
	rm -f *.o *.out
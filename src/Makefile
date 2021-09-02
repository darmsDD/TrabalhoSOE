WFLAGS = -W -Wall -Wshadow -pedantic -lwiringPi -lpthread
all: main.out 
main.out : main.o sensor.o
	gcc $(WFLAGS) main.o sensor.o -o main.out
main.o: main.c
	gcc $(WFLAGS) -c main.c
sensor.o: sensor.c
	gcc $(WFLAGS) -c sensor.c

clean:
	rm -f *.o *.out
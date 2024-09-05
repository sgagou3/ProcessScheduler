CC=gcc
CFLAGS=-c -Wall -Werror -g

all: main

main: task.o sim.o main.o
	$(CC) task.o sim.o main.o -o main -lm

task.o: task.c
	$(CC) $(CFLAGS) task.c
	
sim.o: sim.c
	$(CC) $(CFLAGS) sim.c

main.o: main.c
	$(CC) $(CFLAGS) main.c

run: main
	./main

clean:
	/bin/rm -f main *.o 

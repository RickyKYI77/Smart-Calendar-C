CC = gcc
CFLAGS = -Wall -Wextra -g

all: main

main: main.o calendar.o
	$(CC) $(CFLAGS) -o main main.o calendar.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

calendar.o: calendar.c
	$(CC) $(CFLAGS) -c calendar.c

clean:
	rm -f *.o main

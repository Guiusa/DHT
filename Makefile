FLAGS = -Wall
CC = gcc
PROG = main.c
OUT = dht

all:
	$(CC) $(FLAGS) dht.c $(PROG) -o $(OUT)
purge:
	rm dht

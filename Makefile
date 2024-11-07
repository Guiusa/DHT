FLAGS = -Wall
CC = gcc
PROG = main.c
OUT = mydht

all:
	$(CC) $(FLAGS) dht.c $(PROG) -o $(OUT) -lm
debug:
	$(CC) $(FLAGS) -DDEBUG dht.c $(PROG) -o $(OUT) -lm
purge:
	rm ${OUT}

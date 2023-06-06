CC=gcc
CFLAGS=-O1 -Wall

e2: e2.h e2.c e2_main.c
	$(CC) $(CFLAGS) e2.c e2_main.c -o e2

.phony: clean

clean:
	rm -rf e2 archive.dat

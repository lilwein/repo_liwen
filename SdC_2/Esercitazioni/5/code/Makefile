CFLAGS=-m32 -g -Wall
all: riepilogo

riepilogo: riepilogo.c common.h
	gcc $(CFLAGS) -o riepilogo riepilogo.c -lrt -pthread

.PHONY: clean
clean:
	rm -f riepilogo

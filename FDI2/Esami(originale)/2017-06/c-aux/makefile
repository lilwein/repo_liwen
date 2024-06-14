all: driver.o bst.o queue.o
	gcc -g -o driver driver.o bst.o queue.o

driver.o: bst.h bst.o driver.c
	gcc -g -c driver.c

bst.o: queue.h bst.h bst.c
	gcc -g -c bst.c

queue.o: queue.h queue.c
	gcc -g -c queue.c

clean:
	-rm ./*.o
	-rm driver

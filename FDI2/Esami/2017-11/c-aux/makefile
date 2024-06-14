all: driver.o bst.o queue.o
	gcc -g -Wreturn-type -Wextra -o driver driver.o bst.o queue.o
	chmod u+x driver

driver.o: driver.c
	gcc -g -Wreturn-type -Wextra -c driver.c

bst.o: bst.h bst.c
	gcc -g -Wreturn-type -Wextra -c bst.c

queue.o: queue.h queue.c
	gcc -g -Wreturn-type -Wextra -c queue.c

clean:
	-rm ./*.o
	-rm driver

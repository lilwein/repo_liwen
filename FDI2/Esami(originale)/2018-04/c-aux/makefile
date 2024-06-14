all: driver.o bst.o 
	gcc -g -Wreturn-type -Wextra -o driver driver.o bst.o
	chmod u+x driver

driver.o: driver.c
	gcc -g -Wreturn-type -Wextra -c driver.c

bst.o: bst.h bst.c
	gcc -g -Wreturn-type -Wextra -c bst.c

clean:
	-rm ./*.o
	-rm driver

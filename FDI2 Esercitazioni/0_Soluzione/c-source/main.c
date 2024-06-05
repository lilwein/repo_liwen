#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

// prototipi 
void launcher(int*, int);
int *randArray(int);
void printArray(int*, int);


//
void bubbleSort(int*, int);



int * randArray(int n) {
    srand(time(NULL));
    int *v = malloc(n*sizeof(int));
    for(int i = 0; i < n; i++) v[i] = rand();
    return v;
}

void launcher(int *a, int n) {
    printArray(a, n);
    printf("Lancio il Bubble Sort... ");
    clock_t begin = clock();
    bubbleSort(a, n);
    clock_t end = clock();
    printf("fatto. Tempo: %g msec.\n", (double)(end - begin) * 1000 / CLOCKS_PER_SEC);
    printArray(a, n);
	free(a); // Liberiamo la memoria allocata
    // t2-t1 è il tempo impiegato da bubbleSort
}

void printArray(int *a, int n) {
    printf("L'array ha %d elementi\n", n);
    for(int i = 0; i < n; i++) printf("array[%d] = %d\n", i, a[i]);
    printf("Fine array.\n");
}


int main(int argc, char *argv[]) {
    // test
    // for (int i = 0; i < argc; i++) printf("argomento n. %d è %s\n", i, argv[i]);
    
    if(argc == 1)
        printf("Lanciare con argomento \"rnd\" seguito da N (numero int)\n"
               "per ordinare un vettore random di N elementi, \n"
               "oppure specificando gli interi del vettore sulla riga di comando.\n");
    else if(strcmp("rnd", argv[1]) == 0) {
        assert(argc == 3);
        int n = atoi(argv[2]);
        launcher(randArray(n), n);
    } else {
        int *v = malloc((argc-1)*sizeof(int));
        for (int i = 0; i < argc-1; i++) v[i] = atoi(argv[i+1]);
        launcher(v, argc-1);
    }
    return 0;
}

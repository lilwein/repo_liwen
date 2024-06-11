#ifndef SORT_H
#define	SORT_H

typedef struct {
    int *arr;
    int size;
} array;

void swap(int *xp, int *yp);
void sortAlgCaller(void (*sort_alg)(array*), array *a);
int nextInt(int max);

/* sorting algs - aggiungerne nuovi se utile*/

void mergeSort(array*);
void heapSort(array*);
void insertionSort(array*);
void selectionSort(array*);
void quickSort(array*);
void radixSort(array*);
void bucketSort(array*);
void bubbleSort(array*);
void purposelyWrongBubbleSort(array*);

#endif	/* SORT_H */


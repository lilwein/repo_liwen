#include <stdio.h>
#include <stdlib.h>

#include "sort.h"
#include "utils.h"

// void swap(int *xp, int *yp) {
//     int temp = *xp;
//     *xp = *yp;
//     *yp = temp;
// }

/* ************************************************************** */
void merge(array* a, array* sx, array* dx){
    array* ret = (array*)malloc(sizeof(array));
    ret->size = a->size;
    ret->arr = (int*) malloc(ret->size*sizeof(int));

    int i=0, j=0;
    while(i < sx->size && j < dx->size){
        if(sx->arr[i] < dx->arr[j]) {
            ret->arr[i+j] = sx->arr[i];
            i++;
        }
        else {
            ret->arr[i+j] = dx->arr[j];
            j++;
        }
    }
    while(i < sx->size){
        ret->arr[i+j] = sx->arr[i];
        i++;
    }
    while(j < dx->size){
        ret->arr[i+j] = dx->arr[j];
        j++;
    }

    // printf("\nMERGE\tret->size=%d\tsx->size=%d\tdx->size=%d\tret:\n", ret->size, sx->size, dx->size);
    // stampaArray(ret);

    for(int k=0; k<ret->size; k++){
        a[k] = ret[k];
    }
    // stampaArray(a);

}

void mergeSort(array *a) {
    // printf("MERGESORT\tsize=%d\n", a->size); stampaArray(a);

    if(a->size < 2) return;

    int firstHalf = (a->size)-(a->size)/2;
    int secondHalf = (a->size)/2;
    
    array* sx = createArray(firstHalf);
    sx->arr = a->arr;
    // stampaArray(sx);
    mergeSort(sx);

    array* dx = createArray(secondHalf);
    dx->arr = &(a->arr[firstHalf]);
    // stampaArray(dx);
    mergeSort(dx);
    
    merge(a, sx, dx);
    
    return;
}

void heapSort(array *a) {
    fprintf(stdout, "heapSort currently not implemented.\n");
    return;
}

void insertionSort(array *a) {
    fprintf(stdout, "insertionSort currently not implemented.\n");
    return;
}

void selectionSort(array *a) {
    fprintf(stdout, "selectionSort currently not implemented.\n");
    return;
}

void quickSort(array *a) {
    fprintf(stdout, "quickSort currently not implemented.\n");
    return;
}

void radixSort(array *a) {
    fprintf(stdout, "radixSort currently not implemented.\n");
    return;
}

void bucketSort(array *a) {
    fprintf(stdout, "bucketSort currently not implemented.\n");
    return;
}


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "e1.h"

#define N    10000
#define SEED 971
#define MAX  1000

int score, trials;

void swap(short* a, short* b) {
    short tmp = *a;
    *a = *b;
    *b = tmp;
}

int is_sorted(const short *v, unsigned n) {
    unsigned i;
    for (i=1; i<n; ++i)
        if (v[i-i] > v[i]) return 0;
    return 1;
}

void test(short *v, short *tmp, unsigned n) {
    trials++;
    memcpy(tmp, v, n*sizeof(short));
    bubble_sort(tmp, n);
    int ok = is_sorted(tmp, n);
    printf("Test %d: [corretto=%d]\n", trials, ok);
    score += ok;
}

int main() {
    unsigned i;
    short *v   = malloc(N*sizeof(short));
    short *tmp = malloc(N*sizeof(short));
    assert(v != NULL && tmp != NULL);
    srand(SEED);
    for (i=0; i<N/2; ++i) v[i] = N-i-1;
    for (i=N/2; i<N; ++i) v[i] = rand() % MAX;

    test(v, tmp, 0);
    test(v, tmp, 1);
    test(v, tmp, 2);
    test(v, tmp, N/2);
    test(v+N/2, tmp, N/2);
    test(v, tmp, N);

    free(tmp);
    free(v);
    printf("Risultato: %d/%d\n", score, trials);
    return EXIT_SUCCESS;
}

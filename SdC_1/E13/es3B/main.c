#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "col2row.h"

#define N 10000

int main() {
    int i, j, **a = malloc(N*sizeof(int*)), s = 0;
    assert(a!=NULL);
    for (i=0; i<N; ++i) {
        assert((a[i]=malloc(N*sizeof(int))) != NULL);
        for (j=0; j<N; ++j) a[i][j] = 1;
    }
    col2row(a, N, 9, 5);
    for (i=0; i<N; ++i) for (j=0; j<N; ++j) s += a[i][j];
    printf("sum = %d [corretto=299940000]\n", s);
    return 0;
}

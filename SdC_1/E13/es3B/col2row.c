#include "col2row.h"

static int sum(int** a, int n, int j) {
    int i, s;
    for (i=s=0; i<n; ++i) s += a[i][j];
    return s;
}

void col2row(int** a, int n, int i, int j) {
    int k;
    for (k=0; k<n; ++k)
        a[i][k] += sum(a, n, j);
}

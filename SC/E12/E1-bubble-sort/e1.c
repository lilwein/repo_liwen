#include "e1.h"

void bubble_sort(short *v, unsigned n) {
    unsigned i, again;
    do {
        again = 0;
        for (i=1; i<n; ++i)
            if (v[i-1] > v[i]) {
                swap(&v[i-1], &v[i]);
                again = 1;
            }
    } while(again);
}

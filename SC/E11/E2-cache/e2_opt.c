#include "e2.h"

long f_opt(const short *v, unsigned n){
    // completare la funzione
    long x = 0;
    unsigned i = 0;
    for (i = 0; i < n; i++)
		x += v[i];
    return x;
}

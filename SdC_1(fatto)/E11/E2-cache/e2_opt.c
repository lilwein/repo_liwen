#include "e2.h"
#define STRIDE 64


long f_opt(const short *v, unsigned n){
	long x = 0;
	unsigned i;
	for(i=0; i<n; i++) x += v[i];
	return x;
}

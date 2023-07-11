#include "e2.h"
#define STRIDE 64

/*long f_opt(const short *v, unsigned n){
    	long x = 0;
	unsigned i, j;
	for (j=0; j<n; j+=STRIDE)
    		for (i=0; i+2<STRIDE; i+=3){    
			x += v[i+j];
			x += v[(i+1)+j];
			x += v[(i+2)+j];
		}
for (; i<STRIDE; ++i)  
	for (; j<n; j+=STRIDE)
    		
			x += v[i+j];
    	return x;
}*/
long f_opt(const short *v, unsigned n){
    // completare la funzione
    long x = 0;
    unsigned i = 0;
    for (i = 0; i+2 < n; i+=3){
		x += v[i];
		x += v[i+1];
		x += v[i+2];
	}
	for(; i<n; i++)
		x += v[i];
    return x;
}

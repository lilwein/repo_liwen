#include <string.h>
#include "e3.h"

char charfreq(const char* s) {
    unsigned freq[256];
    memset(freq, 0, 256*sizeof(unsigned));

    while (*s) freq[*s++]++;

    unsigned maxi = 0;
    unsigned maxf = freq[0];
    int i;
    for (i=1; i<256; ++i){
        if (freq[i]>maxf) {
            maxi = i;
            maxf = freq[i];
        }
    }
    return maxi;
}

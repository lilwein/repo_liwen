// Inserire la soluzione qui...

#include <string.h>
#include "e1.h"

void uint2bin(unsigned x, char bin[32]){
    int idx;
    for (idx = 31; idx>=0; idx--){
        bin[idx] = (x & 1)? '1' : '0';
        x = x >> 1;
    }
}

#include "e1.h"

int is_prefix(const char* s1, const char* s2){
    while (*s1 && *s1++ == *s2++);
    return *s1 == 0;
}

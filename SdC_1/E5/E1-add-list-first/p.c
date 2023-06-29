#include <stdio.h>
#include <stdlib.h>
// #include "e1.h"

typedef struct node_t {
    short elem;
    struct node_t *next;
    struct node_t *nexta;
} node_t;

int main(){
    printf("\n%ld\n\n", sizeof(node_t));
    return 0;
}
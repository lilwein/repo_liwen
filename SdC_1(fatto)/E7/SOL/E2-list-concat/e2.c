#include <stdlib.h>
#include "e2.h"

void list_concat(node_t **l1, node_t *l2) {
    node_t *p = *l1;
    if (p==NULL) *l1 = l2;
    else {
        while (p->next!=NULL) p = p->next;
        p -> next = l2;
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "e2.h"

int score, trials;

node_t* test(short b1[], short b2[], int n1, int n2) {

    trials++;

    int res;
    node_t *l1, *l2, *ok;

    short* buf = malloc((n1+n2)*sizeof(short));
    assert(buf != NULL);
    memcpy(buf, b1, n1*sizeof(short));
    memcpy(buf+n1, b2, n2*sizeof(short));

    res  = list_new_from_buffer(&ok, buf, (n1+n2));
    res |= list_new_from_buffer(&l1, b1, n1);
    res |= list_new_from_buffer(&l2, b2, n2);
    assert(res==0);
    free(buf);

    list_concat(&l1, l2);

    printf("Test %d:\n", trials);
    printf(" -- Calcolato: ");
    list_print(l1);
    printf(" -- Corretto:  ");
    list_print(ok);

    score += list_equal(l1, ok);
}

int main() {
    short b1[] = { 0, 1, 2, 3, 4, 5, 5, 6, 8, 90 };
    int n1 = sizeof(b1)/sizeof(short);

    short b2[] = { 10, 20, 30, 40, 50, 50, 60, 80 };
    int n2 = sizeof(b2)/sizeof(short);

    short b3[] = {  };
    int n3 = sizeof(b3)/sizeof(short);

    test(b1, b2, n1, n2);
    test(b2, b1, n2, n1);
    test(b2, b3, n2, n3);
    test(b3, b2, n3, n2);
    test(b3, b3, n3, n3);

    printf("Risultato: %d/%d\n", score, trials);
    return 0;
}

void list_new(node_t **l) {
    *l = NULL;
}


int list_add_first(node_t **l, short elem) {
    node_t *p = *l;
    node_t *n = malloc(sizeof(node_t));
    if (n == NULL) return -1;           // allocation error
    n->elem = elem;
    n->next = p;
    *l = n;
    return 0;
}

int list_new_from_buffer(node_t **l, short* buf, int n){
    *l = NULL;
    while (--n >= 0)
        if (list_add_first(l, buf[n])) return -1;
    return 0;
}

void list_print(const node_t *p) {
    int s = 0;
    printf("[");
    for (; p!=NULL; p=p->next)
        printf("%d ", p->elem);
    printf("]\n");
}

int list_equal(const node_t *l1, const node_t *l2) {
    while(l1 && l2) {
        if (l1->elem != l2->elem) return 0;
        l1 = l1 -> next;
        l2 = l2 -> next;
    }
    return l1==NULL && l2 == NULL;
}

void list_delete(node_t **l) {
    node_t *p = *l;
    while (p != NULL) {
        node_t *dead = p;
        p = p->next;
        free(dead);
    }
    *l = NULL;
}

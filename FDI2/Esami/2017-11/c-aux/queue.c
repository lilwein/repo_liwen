/* versione C */

/*
    realizza coda generica
*/

#ifndef QUEUE
#define QUEUE

#include <stdlib.h>
#include <assert.h>
#include "queue.h"

queue *newQueue() {
    queue *q = malloc(sizeof(queue));
    assert(q!=NULL);
    q->head=q->tail=NULL;
    q->size = 0;
    return q;
}

void enqueue(queue *q, void *item) {
    queueItem *it = malloc(sizeof(queueItem));
    assert(it!=NULL);
    it->item = item;
    it->next = NULL;
    if(q->tail != NULL) q->tail->next = it;
    q->tail = it;
    if(q->head == NULL) q->head = it;
    q->size++;
    return;
}

void *dequeue(queue *q) {
    queueItem *hd = q->head;
    if(hd==NULL) return NULL;
    void *ret;
    q->head = q->head->next; // se 1 solo elem. head diventa NULL
    q->size--;
    if(q->size==0) q->tail = NULL; // head è già a NULL
    /*
        equivalentemente:
        if(q->head==NULL) q->tail==NULL;
    */
    ret = hd->item;
    free(hd);
    return ret;
}

boolean isEmptyQueue(queue *q) {
    assert(q!=NULL);
    assert(q->size >= 0);
    if(q->size == 0) return TRUE;
    else return FALSE;
}

#endif

/* versione C */

/*
    realizza coda generica
*/

#ifndef _QUEUEH
#define _QUEUEH

#include <stdlib.h>
#include <assert.h>

#ifndef _BOOLEAN
typedef unsigned char boolean;
#define TRUE (unsigned char)1
#define FALSE (unsigned char)0
#define _BOOLEAN
#endif

typedef struct queueItem {
    void *item;
    struct queueItem *next;
} queueItem;

typedef struct queue {
    queueItem *head;
    queueItem *tail;
    int size;
} queue;

queue *newQueue();

void enqueue(queue*, void*);

void *dequeue(queue*);

boolean isEmptyQueue(queue*);

#endif


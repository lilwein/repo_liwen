#ifndef __NODE_T__
#define __NODE_T__

typedef struct node_t {    // base
    short elem;            // offset: 0 |xx..|   (base)
    struct node_t *next;   // offset: 4 |xxxx|  4(base)
} node_t;                  // sizeof: 8

void list_new(node_t **l);
int  list_new_from_buffer(node_t **l, short* buf, int n);
int  list_equal(const node_t *l1, const node_t *l2);
void list_print(const node_t *p);
void list_delete(node_t **l);
int  list_add_first(node_t **l, short elem);
void list_concat(node_t **l1, node_t *l2);
int  list_size(const node_t *p);
int  list_delete_firtst(node_t **l, short elem);

#endif

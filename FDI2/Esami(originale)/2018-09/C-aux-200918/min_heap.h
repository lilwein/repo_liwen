#ifndef __MIN_HEAP_H__
#define	__MIN_HEAP_H__
    
#define MIN_HEAP_DATA_TYPE void *
#define MIN_HEAP_DATA_TYPE_PRINTF "%s"
#define MIN_HEAP_MAX_SIZE 100

typedef void min_heap;
    
typedef struct _min_heap_struct_entry {
    int index;
    double key;
    MIN_HEAP_DATA_TYPE value;
} min_heap_struct_entry;

/*
 * Crea un nuovo heap
 */
min_heap * min_heap_new();

/*
 * Restituisce il valore minore del heap mh
 */
min_heap_struct_entry * min_heap_min(min_heap * mh);

/*
 * Inserisce nel heap mh, il valore value, con priorità p 
 */
min_heap_struct_entry * min_heap_insert(min_heap * mh, double p, MIN_HEAP_DATA_TYPE value);

/*
 * Ritorna 1 se mh è vuoto, 0 altrimenti
 */
int min_heap_is_empty(min_heap * mh);

/*
 * Restituisce e rimuove il valore minore del heap mh 
 */
min_heap_struct_entry * min_heap_remove_min(min_heap * mh);

/*
 * Ritorna il numero di elementi presenti nel heap mh
 */
int min_heap_size(min_heap *mh);

/*
 * Ordina l'array che inizia all'indirizzo v, di size elementi, utilizzando heapsort
 */
void heapsort(double* v, int size);

/*
 * Cambia l'oggetto puntato da e con value, nel heap mh
 */
min_heap_struct_entry * min_heap_replace_value(min_heap * mh, min_heap_struct_entry * e, MIN_HEAP_DATA_TYPE value);

/*
 * Cambia la priorità dell'oggetto puntato da e in key, nel heap mh
 */
min_heap_struct_entry * min_heap_replace_key(min_heap * mh, min_heap_struct_entry * e, double key);

/*
 * Rimuove l'oggetto e dal heap mh
 */
min_heap_struct_entry * min_heap_remove(min_heap * mh, min_heap_struct_entry * e);

/*
 * Elimina il heap mh e libera la memoria allocata
 */
void min_heap_free(min_heap *mh);


#endif	/* __MIN_HEAP_H__ */


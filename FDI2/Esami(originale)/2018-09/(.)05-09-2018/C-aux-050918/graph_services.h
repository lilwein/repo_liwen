#include "graph.h"
#include "linked_list.h"
#include "min_heap.h"

#ifndef __GRAPH_SERVICES_H__
#define __GRAPH_SERVICES_H__

typedef struct city{
    char* name;
    double x;
    double y;
} city;

/*
 * Data una lista contenente un elenco di citta', ritorna un puntatore al grafo completo avente:
 * - un nodo per ogni citta'
 * - un arco per ogni coppia di citta' (x,y) avente come peso la distanza euclidea tra x ed y
 */
graph* get_complete_graph(linked_list* l);

/*
 * Dato un grafo, ritorna un puntatore al minheap costituito dagli archi del grafo, usando il peso degli archi come priorita'.
 */
min_heap* get_min_heap_edges(graph* g);

/*
 * Dato un grafo, ritorna una lista degli archi che rappresentano un Minimum Spanning Tree del grafo.
 */
linked_list* get_mst(graph* g);

#endif // !__GRAPH_SERVICES_H__

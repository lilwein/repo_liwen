#include "graph.h"
#include "linked_list.h"

#ifndef __GRAPH_SERVICES_H__
#define __GRAPH_SERVICES_H__

/**
 * Dato un grafo g, la funziona ritorna il numero delle sue componenti connesse.
*/
int conn_comp(graph* g);

/**
 * Dato un grafo g, la funzione modifica il grafo contraendone tutti i vertici di grado 2
 */ 
void contract(graph* g);

/**
 * Dato un grafo g, ritorna il numero di sottografi completi di 3 nodi contenuti in g
 */
int count_k3(graph* g);

#endif // !__GRAPH_SERVICES_H__

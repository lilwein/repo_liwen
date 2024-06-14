#ifndef __GRAPH_H__
#define	__GRAPH_H__

#include "linked_list.h"

typedef enum { UNEXPLORED, EXPLORED, EXPLORING } STATUS;

typedef struct graph {
	double** mat;
	int n_vertices;
	int n_edges;
} graph;

/**
Crea un nuovo grafo con n_nodi, nodi.
*/
graph * graph_new(int n_nodi);

/**
Stampa su stdout una rappresentazione del grafo.
*/
void graph_print(graph* g);

/**
Elimina il grafo g.
*/
void graph_delete(graph * g);

#endif	/* __GRAPH_H__ */


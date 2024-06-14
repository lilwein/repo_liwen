#ifndef __GRAPH_SERVICES__
#define __GRAPH_SERVICES__

#include "graph.h"
#include <stdlib.h>

/*
 * Struttura Punto, con coordinate x e y.
*/
typedef struct point {
	double x;
	double y;
} point;

/*
* Funzione ausiliara che dati due noti x ed y collegati da un arco,
* restituisce un codice univoco assegnato all'arco.
*/
int edge_to_code(int x, int y);

/*
 * Funzione ausiliara che dato un codice, restituisce in un array
 * di 2 elementi, i nodi collegati dall'arco associato al codice.
*/
int* code_to_edge(int x);

/*
 * Dato un array di n punti, con coordinate x ed y, la funzione ritorna
 * un puntatore al grafo rappresentato dai potenziali collegamenti
 * di tutti i punti, rappresentato con matrice di adiacenze. Il peso
 * di ciascun arco x <-> y e' rappresentato dalla distanza euclidea dei nodi
 * x ed y.
*/
graph* make_graph(point** points, int n);

/*
 * Dato un grafo g, la funzione ritorna un nuovo grafo g', con gli archi che rappresentano
 * un albero ricoprente che descrive la cablatura da impiegare per l'interconnesione
 * di tutti i punti, minimizzando la quantita' di cavo impiegato. 
*/
graph* get_best_connections(graph* g);

/*
 * Dato un grafo ed un suo nodo v, la funzione ritorna l'altezza dell'albero
 * avente v come radice.
*/
int get_tree_height(graph* g, int v);

#endif // !__GRAPH_SERVICES__
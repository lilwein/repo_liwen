#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

graph * graph_new(int n_nodi) {
	graph* g = (graph*) malloc(sizeof(graph));
	g->n_vertices = n_nodi;
	g->n_edges = 0;
	g->mat = (double**) malloc(sizeof(double*) * n_nodi);
	for(int i = 0; i < n_nodi; ++i){
		g->mat[i] = (double*) malloc(sizeof(double) * n_nodi);
		for(int j = 0; j < n_nodi; ++j){
			g->mat[i][j] = -1;
		}
	}
	return g;
}

void graph_print(graph* g){
	for(int i = 0; i < g->n_vertices; ++i){
		printf("\t%d\t", i);
	}
	printf("\n");
	for(int i = 0; i < g->n_vertices; ++i){
		printf("%d\t", i);
		for( int j = 0; j < g->n_vertices; ++j){
			printf("%f\t", g->mat[i][j]);
		}
		printf("\n");
	}
	printf("The graph has %d nodes and %d edges.\n", g->n_vertices, g->n_edges);
}

void graph_delete(graph* g){
	for(int i = 0; i < g->n_vertices; ++i){
		free(g->mat[i]);
	}
	free(g->mat);
	free(g);
}
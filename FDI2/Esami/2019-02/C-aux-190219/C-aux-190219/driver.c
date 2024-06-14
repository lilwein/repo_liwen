#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "graph_services.h"
#include "min_heap.h"
#include "partition.h"

void print_help() {
	printf("Richiesto argomento: {test, graph, gbc, gth}\n");
}

int main(int argc, char** argv) {
	if (argc != 2) {
		print_help();
		return EXIT_FAILURE;
	}
	else if (strcmp(argv[1], "test") == 0) {
		graph* g = graph_new(4);
		g->mat[0][1] = 1.2;
		g->mat[0][2] = 3.7;
		g->mat[0][3] = 0.8;
		g->mat[1][0] = 1.2;
		g->mat[1][2] = 2.8;
		g->mat[1][3] = 5.3;
		g->mat[2][0] = 3.7;
		g->mat[2][1] = 2.8;
		g->mat[2][3] = 1.7;
		g->mat[3][0] = 0.8;
		g->mat[3][1] = 5.3;
		g->mat[3][2] = 1.7;
		printf("The graph has %d nodes.\n", g->n_vertices);
		graph_print(g);
		printf("The code for %d,%d is: %d\n", 1, 1, edge_to_code(1, 1));
		printf("The code for %d,%d is: %d\n", 1, 2, edge_to_code(1, 2));
		printf("The code for %d,%d is: %d\n", 2, 1, edge_to_code(2, 1));
		printf("The code for %d,%d is: %d\n", 35, 23, edge_to_code(35, 23));
		printf("The code for %d,%d is: %d\n", 23, 35, edge_to_code(23, 35));

		int cod1 = edge_to_code(1, 2);
		int cod2 = edge_to_code(2, 1);
		int cod3 = edge_to_code(23, 42);
		int cod4 = edge_to_code(42, 23);

		int* edg1 = code_to_edge(cod1);
		int* edg2 = code_to_edge(cod2);
		int* edg3 = code_to_edge(cod3);
		int* edg4 = code_to_edge(cod4);

		printf("The edge of %d is: %d,%d\n", cod1, edg1[0], edg1[1]);
		printf("The edge of %d is: %d,%d\n", cod2, edg2[0], edg2[1]);
		printf("The edge of %d is: %d,%d\n", cod3, edg3[0], edg3[1]);
		printf("The edge of %d is: %d,%d\n", cod4, edg4[0], edg4[1]);
		free(edg1);
		free(edg2);
		free(edg3);
		free(edg4);

		graph_delete(g);
	}
	else if (strcmp(argv[1], "graph") == 0){
		point* a = (point*) malloc(sizeof(point));
		a->x = 1.2;
		a->y = 2.5;
		point* b = (point*) malloc(sizeof(point));
		b->x = 2.2;
		b->y = 3.7;
		point* c = (point*) malloc(sizeof(point));
		c->x = 5;
		c->y = 1;
		point* d = (point*) malloc(sizeof(point));
		d->x = 4.2;
		d->y = 2.2;

		point** points = (point**) malloc(sizeof(point*) * 4);
		points[0] = a;
		points[1] = b;
		points[2] = c;
		points[3] = d;

		graph* g = make_graph(points, 4);
		graph_print(g);
		graph_delete(g);

		free(a);
		free(b);
		free(c);
		free(d);
		free(points);
	}
	else if (strcmp(argv[1], "gbc") == 0){
		graph* g = graph_new(4);
		g->mat[0][1] = 1.2;
		g->mat[0][2] = 3.7;
		g->mat[0][3] = 0.8;
		g->mat[1][0] = 1.2;
		g->mat[1][2] = 2.8;
		g->mat[1][3] = 5.3;
		g->mat[2][0] = 3.7;
		g->mat[2][1] = 2.8;
		g->mat[2][3] = 1.7;
		g->mat[3][0] = 0.8;
		g->mat[3][1] = 5.3;
		g->mat[3][2] = 1.7;
		g->n_edges = 6;
		graph_print(g);
		graph* g1 = get_best_connections(g);
		printf("\n");
		printf("The best connections are:\n");
		graph_print(g1);
		graph_delete(g);
		graph_delete(g1);
	}
	else if(strcmp(argv[1], "gth") == 0){
		graph* g = graph_new(4);
		g->mat[0][1] = 1.2;
		g->mat[0][3] = 0.8;
		g->mat[1][0] = 1.2;
		g->mat[2][3] = 1.7;
		g->mat[3][0] = 0.8;
		g->mat[3][2] = 1.7;
		g->n_edges = 3;
		graph_print(g);
		printf("The height with root %d is: %d\n", 0, get_tree_height(g, 0));
		printf("The height with root %d is: %d\n", 1, get_tree_height(g, 1));
		printf("The height with root %d is: %d\n", 2, get_tree_height(g, 2));
		printf("The height with root %d is: %d\n", 3, get_tree_height(g, 3));
		
		graph_delete(g);
	}
}


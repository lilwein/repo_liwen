#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#include "linked_list.h"
#include "graph.h"
#include "graph_services.h"

void print_help() {
    printf("Manca argomento: {nconn, contract, count}\n");
}

int main(int argc, char** argv) {
	if (argc != 2) {
		print_help();
		return EXIT_FAILURE;
	}
	else if (strcmp(argv[1], "nconn") == 0){
		graph* g = graph_new();
		graph_node* a = graph_add_node(g, "a");
		graph_node* b = graph_add_node(g, "b");
		graph_node* c = graph_add_node(g, "c");
		
		graph_add_edge(g, a, b);
		graph_add_edge(g, a, c);
		graph_add_edge(g, c, b);

		printf("################################\n");
		printf("Primo test\n");
		printf("################################\n");
		graph_print(g);
		printf("n_conn_comp -> %d\n", conn_comp(g));
		printf("\n");
		graph_delete(g);

		g = graph_new();
		a = graph_add_node(g, "a");
		b = graph_add_node(g, "b");
		c = graph_add_node(g, "c");
	
		printf("################################\n");
		printf("Secondo test\n");
		printf("################################\n");
		graph_print(g);
		printf("n_conn_comp -> %d\n", conn_comp(g));
		graph_delete(g);
		printf("\n");

		g = graph_new();
		a = graph_add_node(g, "a");
		b = graph_add_node(g, "b");
		c = graph_add_node(g, "c");
		graph_node* d = graph_add_node(g, "d");

		graph_add_edge(g, a, b);
		graph_add_edge(g, b, c);
		graph_add_edge(g, c, d);

		printf("################################\n");
		printf("Terzo test\n");
		printf("################################\n");
		graph_print(g);
		printf("n_conn_comp -> %d\n", conn_comp(g));
		graph_delete(g);
		printf("\n");

		g = graph_new();
		a = graph_add_node(g, "a");
		b = graph_add_node(g, "b");
		c = graph_add_node(g, "c");
		d = graph_add_node(g, "d");
		graph_add_node(g, "e");
		
		graph_add_edge(g, a, b);
		graph_add_edge(g, c, d);

		printf("################################\n");
		printf("Quarto test\n");
		printf("################################\n");
		graph_print(g);
		printf("n_conn_comp -> %d\n", conn_comp(g));
		graph_delete(g);
		printf("\n");
	}
	else if (strcmp(argv[1], "contract") == 0){
		graph* g = graph_new();
		graph_node* a = graph_add_node(g, "a");
		graph_node* b = graph_add_node(g, "b");
		graph_node* c = graph_add_node(g, "c");
		graph_node* d = graph_add_node(g, "d");
		graph_node* e = graph_add_node(g, "e");

		graph_add_edge(g, a, b);
		graph_add_edge(g, a, c);
		graph_add_edge(g, d, e);
		graph_add_edge(g, a, d);

		printf("################################\n");
		printf("Primo test\n");
		printf("################################\n");
		graph_print(g);
		printf("\n");
		printf("Contracted graph:\n");
		contract(g);
		graph_print(g);
		graph_delete(g);

		g = graph_new();
		a = graph_add_node(g, "a");
		b = graph_add_node(g, "b");
		c = graph_add_node(g, "c");
		d = graph_add_node(g, "d");
		e = graph_add_node(g, "e");

		graph_add_edge(g, a, b);
		graph_add_edge(g, a, c);
		graph_add_edge(g, b, c);
		graph_add_edge(g, d, e);

		printf("################################\n");
		printf("Secondo test\n");
		printf("################################\n");
		graph_print(g);
		printf("\n");
		printf("Contracted graph:\n");
		contract(g);
		graph_print(g);
		graph_delete(g);
	}
	else if (strcmp(argv[1], "count") == 0){
		graph* g = graph_new();
		graph_node* a = graph_add_node(g, "a");
		graph_node* b = graph_add_node(g, "b");
		graph_node* c = graph_add_node(g, "c");
		graph_node* d = graph_add_node(g, "d");
		graph_node* e = graph_add_node(g, "e");
		graph_node* f = graph_add_node(g, "f");
		
		graph_add_edge(g, a, b);
		graph_add_edge(g, a, d);
		graph_add_edge(g, d, b);
		graph_add_edge(g, d, e);
		graph_add_edge(g, d, f);
		graph_add_edge(g, b, c);

		printf("################################\n");
		printf("Primo test\n");
		printf("################################\n");
		graph_print(g);
		printf("n_k3 -> %d\n", count_k3(g));
		printf("\n");
		graph_delete(g);

		g = graph_new();
		a = graph_add_node(g, "a");
		b = graph_add_node(g, "b");
		c = graph_add_node(g, "c");
		d = graph_add_node(g, "d");
		e = graph_add_node(g, "e");

		graph_add_edge(g, a, b);
		graph_add_edge(g, a, c);
		graph_add_edge(g, d, b);
		graph_add_edge(g, b, c);
		graph_add_edge(g, d, c);
		graph_add_edge(g, d, e);
		graph_add_edge(g, e, b);
		
		printf("################################\n");
		printf("Secondo test\n");
		printf("################################\n");
		graph_print(g);
		printf("n_k3 -> %d\n", count_k3(g));
		printf("\n");
		graph_delete(g);

		g = graph_new();
		a = graph_add_node(g, "a");
		b = graph_add_node(g, "b");
		c = graph_add_node(g, "c");
		d = graph_add_node(g, "d");
		e = graph_add_node(g, "e");
		f = graph_add_node(g, "f");

		graph_add_edge(g, a, b);
		graph_add_edge(g, b, c);
		graph_add_edge(g, c, d);
		graph_add_edge(g, d, e);
		graph_add_edge(g, e, f);

		printf("################################\n");
		printf("Terzo test\n");
		printf("################################\n");
		graph_print(g);
		printf("n_k3 -> %d\n", count_k3(g));
		printf("\n");
		graph_delete(g);
	}
	else{
        print_help();
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>

#include "linked_list.h"
#include "min_heap.h"
#include "graph.h"
#include "graph_services.h"

void print_help() {
    printf("Manca argomento: {comp_graph, set_weights, min_wire}\n");
}

linked_list* get_list(){
	linked_list* to_ret = linked_list_new();

	centrale* c1 = (centrale*) malloc(sizeof(centrale));
	c1->name = "Roma"; c1->x = 41.890; c1->y = 12.500;
	linked_list_insert_tail(to_ret, c1);
	
	centrale* c2 = (centrale*) malloc(sizeof(centrale));
	c2->name = "Milano"; c2->x = 45.480; c2->y = 9.190;
	linked_list_insert_tail(to_ret, c2);

	centrale* c3 = (centrale*) malloc(sizeof(centrale));
	c3->name = "Napoli"; c3->x = 40.850; c3->y = 14.270;
	linked_list_insert_tail(to_ret, c3);

	centrale* c4 = (centrale*) malloc(sizeof(centrale));
	c4->name = "Torino"; c4->x = 45.080; c4->y = 7.680;
	linked_list_insert_tail(to_ret, c4);
	
	centrale* c5 = (centrale*) malloc(sizeof(centrale));
	c5->name = "Palermo"; c5->x = 38.120; c5->y = 13.360;
	linked_list_insert_tail(to_ret, c5);

	centrale* c6 = (centrale*) malloc(sizeof(centrale));
	c6->name = "Genova"; c6->x = 44.420; c6->y = 8.930;
	linked_list_insert_tail(to_ret, c6);

	centrale* c7 = (centrale*) malloc(sizeof(centrale));
	c7->name = "Bologna"; c7->x = 44.500; c7->y = 11.340;
	linked_list_insert_tail(to_ret, c7);

	centrale* c8 = (centrale*) malloc(sizeof(centrale));
	c8->name = "Firenze"; c8->x = 43.780; c8->y = 11.240;
	linked_list_insert_tail(to_ret, c8);

	centrale* c9 = (centrale*) malloc(sizeof(centrale));
	c9->name = "Catania"; c9->x = 37.500; c9->y = 15.080;
	linked_list_insert_tail(to_ret, c9);

	centrale* c10 = (centrale*) malloc(sizeof(centrale));
	c10->name = "Bari"; c10->x = 41.120; c10->y = 16.870;
	linked_list_insert_tail(to_ret, c10);

	return to_ret;
}

int main(int argc, char** argv) {
	if (argc != 2) {
		print_help();
		return EXIT_FAILURE;
	}
	if (strcmp(argv[1], "comp_graph") == 0) {
		linked_list* l1 = get_list();
		graph* g = get_complete_graph(l1);
		graph_print_powplant(g);
		linked_list_delete(l1);
		graph_delete(g);
	}
	else if (strcmp(argv[1], "set_weights") == 0){
		linked_list* l1 = get_list();
		graph* g = get_complete_graph(l1);
		set_weights_in_graph(g);
		
		graph_print_powplant(g);
		graph_delete(g);
		linked_list_delete(l1);
	}
	else if (strcmp(argv[1], "min_wire") == 0){
		linked_list* l1 = get_list();
		graph* g = get_complete_graph(l1);
		set_weights_in_graph(g);
		linked_list* list = get_min_wire(g);
		
		linked_list_iterator* it = linked_list_iterator_new(list);
		graph_edge* edg;
		for(edg = linked_list_iterator_getvalue(it); linked_list_iterator_hasnext(it); edg = linked_list_iterator_next(it)){
			printf("%s <-> %s : %f\n", ((centrale*)edg->n1->object)->name, ((centrale*)edg->n2->object)->name, edg->weight);
		}
		linked_list_iterator_delete(it);
		linked_list_delete(list);
		graph_delete(g);
		linked_list_delete(l1);
	}
	else{
        print_help();
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>

#include "linked_list.h"
#include "min_heap.h"
#include "partition.h"
#include "graph.h"
#include "graph_services.h"

void print_help() {
    printf("Manca argomento: {comp_graph, heap_edges, mst}\n");
}

linked_list* get_cities(){
	linked_list* to_ret = linked_list_new();

	city* c1 = (city*) malloc(sizeof(city));
	c1->name = "Roma"; c1->x = 41.890; c1->y = 12.500;
	linked_list_insert_tail(to_ret, c1);
	
	city* c2 = (city*) malloc(sizeof(city));
	c2->name = "Milano"; c2->x = 45.480; c2->y = 9.190;
	linked_list_insert_tail(to_ret, c2);

	city* c3 = (city*) malloc(sizeof(city));
	c3->name = "Napoli"; c3->x = 40.850; c3->y = 14.270;
	linked_list_insert_tail(to_ret, c3);

	city* c4 = (city*) malloc(sizeof(city));
	c4->name = "Torino"; c4->x = 45.080; c4->y = 7.680;
	linked_list_insert_tail(to_ret, c4);
	
	city* c5 = (city*) malloc(sizeof(city));
	c5->name = "Palermo"; c5->x = 38.120; c5->y = 13.360;
	linked_list_insert_tail(to_ret, c5);

	city* c6 = (city*) malloc(sizeof(city));
	c6->name = "Genova"; c6->x = 44.420; c6->y = 8.930;
	linked_list_insert_tail(to_ret, c6);

	city* c7 = (city*) malloc(sizeof(city));
	c7->name = "Bologna"; c7->x = 44.500; c7->y = 11.340;
	linked_list_insert_tail(to_ret, c7);

	city* c8 = (city*) malloc(sizeof(city));
	c8->name = "Firenze"; c8->x = 43.780; c8->y = 11.240;
	linked_list_insert_tail(to_ret, c8);

	city* c9 = (city*) malloc(sizeof(city));
	c9->name = "Catania"; c9->x = 37.500; c9->y = 15.080;
	linked_list_insert_tail(to_ret, c9);

	city* c10 = (city*) malloc(sizeof(city));
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
		linked_list* l1 = get_cities();
		graph* g = get_complete_graph(l1);
		graph_print(g);
		linked_list_delete(l1);
		graph_delete(g);
	}
	else if (strcmp(argv[1], "heap_edges") == 0){
		linked_list* l1 = get_cities();
		graph* g = get_complete_graph(l1);
		min_heap* mh = get_min_heap_edges(g);
		
		graph_edge* item;
		int i = 1;
		while(!min_heap_is_empty(mh)){
			item = (graph_edge*) min_heap_remove_min(mh)->value;
			printf("%d  %s <-> %s : %f\n", i, item->n1->name, item->n2->name, item->weight);
			i++;
		}
		graph_delete(g);
		linked_list_delete(l1);
		min_heap_free(mh);
	}
	else if (strcmp(argv[1], "mst") == 0){
		linked_list* l1 = get_cities();
		graph* g = get_complete_graph(l1);
		linked_list* mst_list = get_mst(g);

		linked_list_delete(mst_list);
		graph_delete(g);
		linked_list_delete(l1);
	}
	else{
        print_help();
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
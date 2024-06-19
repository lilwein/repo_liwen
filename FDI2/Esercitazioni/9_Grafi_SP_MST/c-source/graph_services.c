#include "graph_services.h"
#include "min_heap.h"
#include "partition.h"

#include <stdio.h>
#include <stdlib.h>

void printStatus(graph* g){
    printf("AUX FUNCTION\n");
    linked_list* nodes = g->nodes;
    linked_list_iterator* aux = linked_list_iterator_new(nodes);
    while(linked_list_iterator_hasnext(aux)){
        graph_node* node = (graph_node*) linked_list_iterator_getvalue(aux);
        printf("%s: %d\n", (char*)node->value, node->status);
        linked_list_iterator_next(aux);
    }
    printf("\n");
}

void bfs(graph* g) {
	linked_list* nodes = g->nodes;
    linked_list_iterator* aux = linked_list_iterator_new(nodes);
    while(linked_list_iterator_hasnext(aux)){
        graph_node* node = (graph_node*) linked_list_iterator_getvalue(aux);
        node->status = UNEXPLORED;
        linked_list_iterator_next(aux);
    }

    aux = linked_list_iterator_new(nodes);
    graph_node* source = (graph_node*) linked_list_iterator_getvalue(aux);


    linked_list* level = linked_list_new();
    linked_list_enqueue(level, source);
    linked_list_iterator* it_level = linked_list_iterator_new(level);
    
    int distance = 0;
    printf("%s\n", (char*)source->value);

    while(linked_list_iterator_hasnext(it_level)){  
        linked_list* next_level = linked_list_new();

        while(linked_list_iterator_hasnext(it_level)){            
            graph_node* node = (graph_node*) linked_list_iterator_getvalue(it_level);
            linked_list* edges = node->out_edges;
            linked_list_iterator* it_edges = linked_list_iterator_new(edges);
            
            while(linked_list_iterator_hasnext(it_edges)){
                graph_edge* edge = (graph_edge*) linked_list_iterator_getvalue(it_edges);
                graph_node* opposite = edge->target;
                if(opposite->status == UNEXPLORED){
                    opposite->status = EXPLORED;
                    linked_list_enqueue(next_level, opposite);
                    printf("%s\n", (char*)opposite->value);
                }
                linked_list_iterator_next(it_edges);
            }
            
            linked_list_iterator_next(it_level);
        }
        
        // printf("list of level %d:\t", distance);
        distance++;
        // linked_list_print_graph_node(level);

        level = next_level;
        linked_list_iterator_delete(it_level);
        it_level = linked_list_iterator_new(level);
    }
}

void single_source_shortest_path(graph* g, graph_node* source) {
	
}

void mst(graph* g) {
	
}
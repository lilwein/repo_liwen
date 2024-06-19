#include "graph_services.h"
#include "min_heap.h"
#include "partition.h"

#include <stdio.h>
#include <stdlib.h>

#define MAX_DISTANCE (1<<30)

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
    // printf("%s\n", (char*)source->value);

    while(linked_list_iterator_hasnext(aux)){
        graph_node* n = (graph_node*) linked_list_iterator_getvalue(aux);
        
        if(n->status == UNEXPLORED){
            printf("%s\n", (char*)n->value);

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
        linked_list_iterator_next(aux);
    }
}

void single_source_shortest_path(graph* g, graph_node* source) {

    min_heap* pq = min_heap_new();

    linked_list* g_nodes = g->nodes;
    linked_list_iterator* aux = linked_list_iterator_new(g_nodes);
    while(linked_list_iterator_hasnext(aux)){
        graph_node* node = (graph_node*) linked_list_iterator_getvalue(aux);
        node->status = UNEXPLORED;
        if(node == source) node->dist = 0;
        else node->dist = MAX_DISTANCE;
        min_heap_insert(pq, node->dist, node);
        linked_list_iterator_next(aux);
    }
	source->dist = 0;

    printf("size: %d\n", min_heap_size(pq));
    
    aux = linked_list_iterator_new(g_nodes);

    while(min_heap_size(pq)){
        min_heap_struct_entry* entry = min_heap_remove_min(pq);
        // int distance = entry->key;
        graph_node* node = (graph_node*) entry->value;

        linked_list* edges = node->out_edges;
        linked_list_iterator* it_edge = linked_list_iterator_new(edges);
        while(linked_list_iterator_hasnext(it_edge)){
            graph_edge* edge = (graph_edge*) linked_list_iterator_getvalue(it_edge);
            graph_node* opposite = edge->target;
            int weight = node->dist + edge->weight;

            if(weight < opposite->dist) {
                min_heap_struct_entry* entry_opp = min_heap_insert(pq, opposite->dist, opposite);
                opposite->dist = weight;
                min_heap_replace_key(pq, entry_opp, weight);
            }
            linked_list_iterator_next(it_edge);
        }
    }

    aux = linked_list_iterator_new(g_nodes);
    while(linked_list_iterator_hasnext(aux)){
        graph_node* node = (graph_node*) linked_list_iterator_getvalue(aux);
        printf("node: %s\t min_dist: %d\n", (char*)node->value, node->dist);
        linked_list_iterator_next(aux);
    }

}

void mst(graph* g) {
    partition* partition = partition_new(g->properties->n_vertices);
    min_heap* heap = min_heap_new();

	linked_list* nodes = g->nodes;
    linked_list_iterator* aux = linked_list_iterator_new(nodes);
    for(int i=0; linked_list_iterator_hasnext(aux); i++){
        graph_node* node = (graph_node*) linked_list_iterator_getvalue(aux);
        node->map = i;
        partition_makeset(partition,i);

        linked_list* edges = node->out_edges;
        linked_list_iterator* it_edges = linked_list_iterator_new(edges);
        while(linked_list_iterator_hasnext(it_edges)){
            graph_edge* edge = (graph_edge*) linked_list_iterator_getvalue(it_edges);
            min_heap_insert(heap, edge->weight, edge);

            linked_list_iterator_next(it_edges);
        }
        
        linked_list_iterator_next(aux);
    }
    
    linked_list* list = linked_list_new();
    while(min_heap_size(heap)){
        min_heap_struct_entry* entry = min_heap_remove_min(heap);
        graph_edge* edge = (graph_edge*) entry->value;
        graph_node* source = edge->source;
        graph_node* target = edge->target;

        int source_index = partition_find(partition, source->map);
        int target_index = partition_find(partition, target->map);
        if(source_index != target_index){
            partition_union(partition, source_index, target_index);
            linked_list_enqueue(list, edge);
        }
    }

    aux = linked_list_iterator_new(list);
    while(linked_list_iterator_hasnext(aux)){
        graph_edge* edge = (graph_edge*) linked_list_iterator_getvalue(aux);
        printf("(%s,%s)\n", (char*)edge->source->value, (char*)edge->target->value);

        linked_list_iterator_next(aux);
    }


}
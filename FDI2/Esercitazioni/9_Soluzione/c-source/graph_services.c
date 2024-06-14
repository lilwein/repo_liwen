#include "graph_services.h"
#include "min_heap.h"
#include "partition.h"

#include <stdio.h>
#include <stdlib.h>

static void bfs_from_node(graph_node* n) {
	linked_list* queue = linked_list_new();
	linked_list_enqueue(queue, n);
	n->status = EXPLORED;
	while (!linked_list_size(queue) == 0) {
		linked_list_node* llnd = (linked_list_node*)linked_list_dequeue(queue);
		graph_node* nd = (graph_node*)linked_list_node_getvalue(llnd);
		free(llnd);
		printf("%s\n", (char*)(nd->value));
		linked_list_iterator* it = linked_list_iterator_new(nd->out_edges);
		graph_edge* edge = (graph_edge*)linked_list_iterator_getvalue(it);
		for (; linked_list_iterator_hasnext(it); edge = (graph_edge*)linked_list_iterator_next(it)) {
			graph_node* nxt = edge->target;
			if (nxt->status == UNEXPLORED) {
				nxt->status = EXPLORED;
				linked_list_enqueue(queue,nxt);
			}
		}
		linked_list_iterator_delete(it);
	}
	linked_list_delete(queue);
}

void bfs(graph* g) {
	linked_list_iterator * lli = linked_list_iterator_new(g->nodes);
	graph_node * n = (graph_node *)linked_list_iterator_getvalue(lli);
	while (linked_list_iterator_hasnext(lli)) {
		n->status = UNEXPLORED;
		n->timestamp = 0;
		n = (graph_node*)linked_list_iterator_next(lli);
	}
	linked_list_iterator_delete(lli);

	lli = linked_list_iterator_new(g->nodes);
	n = (graph_node*)linked_list_iterator_getvalue(lli);
	for (; linked_list_iterator_hasnext(lli); n = (graph_node*)linked_list_iterator_next(lli)) {
		if (n->status == UNEXPLORED)
			bfs_from_node(n);
	}
	linked_list_iterator_delete(lli);
}

void single_source_shortest_path(graph* g, graph_node* source) {
	min_heap * pqueue = min_heap_new();

	const int INFINITY = 100000; // = "Infinito" 
								 // (NB.: deve essere maggiore della somma di tutti i pesi del grafo, altrimenti � scorretto)
	linked_list_iterator * lli = linked_list_iterator_new(g->nodes);
	graph_node * u = (graph_node*)linked_list_iterator_getvalue(lli);
	while (linked_list_iterator_hasnext(lli)) {
		if (u == source) {
			min_heap_insert(pqueue, 0, u);
			u->dist = 0;
		}
		else {
			min_heap_insert(pqueue, INFINITY, u);
			u->dist = INFINITY;
		}
		u = (graph_node*)linked_list_iterator_next(lli);
	}
	linked_list_iterator_delete(lli);

	// Ciclo principale
	while (!min_heap_is_empty(pqueue)) {
		min_heap_struct_entry * hu = min_heap_remove_min(pqueue);
		graph_node *u = (graph_node*)hu->value;
		free(hu);

		lli = linked_list_iterator_new(u->out_edges);
		graph_edge* edge = (graph_edge*)linked_list_iterator_getvalue(lli);
		while (linked_list_iterator_hasnext(lli)) {
			graph_node *v = edge->target;
			if (u->dist + edge->weight < v->dist) {
				min_heap_insert(pqueue, u->dist + edge->weight, v);
				v->dist = u->dist + edge->weight;
			}
			edge = (graph_edge*)linked_list_iterator_next(lli);
		}
		linked_list_iterator_delete(lli);
	}
	min_heap_free(pqueue);
	lli = linked_list_iterator_new(g->nodes);
	u = (graph_node *)linked_list_iterator_getvalue(lli);
	while (linked_list_iterator_hasnext(lli)) {
		printf("%s %d\n", (char*)(u->value), u->dist);
		u = (graph_node*)linked_list_iterator_next(lli);
	}
	linked_list_iterator_delete(lli);
}

void mst(graph* g) {
	partition *p;
	int i;

	p = partition_new(g->properties->n_vertices);
	linked_list_iterator* lli = linked_list_iterator_new(g->nodes);
	graph_node * node = (graph_node*)linked_list_iterator_getvalue(lli);
	for(i = 0 ; linked_list_iterator_hasnext(lli); i++, node = (graph_node*)linked_list_iterator_next(lli)){
		node->map = i;
		partition_makeset(p, i);
	}
	linked_list_iterator_delete(lli);
	
	min_heap* pqueue = min_heap_new();
	lli = linked_list_iterator_new(g->nodes);
	node = (graph_node*)linked_list_iterator_getvalue(lli);
	for ( ; linked_list_iterator_hasnext(lli); node = (graph_node*)linked_list_iterator_next(lli)) {
		linked_list_iterator* in_lli = linked_list_iterator_new(node->out_edges);
		graph_edge* edge = (graph_edge*)linked_list_iterator_getvalue(in_lli);
		for (; linked_list_iterator_hasnext(in_lli); edge = (graph_edge*)linked_list_iterator_next(in_lli)) {
			min_heap_insert(pqueue, edge->weight, edge);
		}
		linked_list_iterator_delete(in_lli);
	}
	linked_list_iterator_delete(lli);
	// Ciclo principale
	while (!min_heap_is_empty(pqueue)) {
		min_heap_struct_entry* hu = min_heap_remove_min(pqueue);
		graph_edge* edge = (graph_edge*) hu->value;
		int smap = edge->source->map;
		int tmap = edge->target->map;
		int s_set = partition_find(p, smap);
		int t_set = partition_find(p, tmap);
		if  (s_set != t_set) {
			printf("%s %s\n", (char*)(edge->source->value), (char*)(edge->target->value));
			partition_union(p, s_set, t_set);
		}
		free(hu);
	}
	min_heap_free(pqueue);
	partition_delete(p);
}
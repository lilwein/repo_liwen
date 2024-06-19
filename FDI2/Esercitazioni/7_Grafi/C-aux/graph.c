#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef enum {UNEXPLORED, EXPLORED, EXPLORING} STATUS;

struct graph_node{
    void * value;
    linked_list * out_edges;

    // keep track status
    STATUS state;
    int timestamp;
};

struct graph{
    linked_list * nodes;

	int n_vertices;
	int n_edges;
};

graph * graph_new() {
	graph* new = (graph*) malloc(sizeof(graph));
	new->nodes = linked_list_new();
	new->n_vertices = 0;
	new->n_edges = 0;
	return new;
}

linked_list * graph_get_nodes(graph * g) {
	return g->nodes;
}

linked_list * graph_get_neighbors(graph * g, graph_node * n) {
	return n->out_edges;
}

void * graph_get_node_value(graph_node * n) {
	return n->value;
}

static int compare_value(void* v1, void* v2){
	return *((char*)v1) == *((char*)v2);
}

graph_node * graph_add_node(graph * g, void * value) {
	linked_list* nodes = graph_get_nodes(g);
	linked_list_node* aux = nodes->head;
	while(aux){
		graph_node* node = aux->value;
		if(compare_value(node->value, value)) return node;
		aux = aux->next;
	}

	graph_node* new = (graph_node*) malloc(sizeof(graph_node));
	new->value = value;
	linked_list* out_edges = linked_list_new();
	new->out_edges = out_edges;
	new->state = UNEXPLORED;
	new->timestamp = -1;

	linked_list_add(nodes, (void*) new);
	g->n_vertices ++;

	return new;
}

void graph_add_edge(graph * g, graph_node * v1, graph_node * v2) {
    linked_list* v1_edges = graph_get_neighbors(g,v1);
	linked_list* v2_edges = graph_get_neighbors(g,v2);
	
	// printf("ADD EDGE\n");
	// printf("%s:\t", (char*)v1->value); print_list(v1_edges);
	// printf("%s:\t", (char*)v2->value); print_list(v2_edges);

	linked_list_node* aux = v1_edges->head;
	while(aux){
		graph_node* node = (graph_node*) aux->value;
		void* value = node->value;
		if(compare_value(value, v2->value)) {
			return;
		}
		aux = aux->next;
	}
	// printf("%s, %s\n", (char*)v1->value, (char*)v2->value);
	linked_list_add(v1_edges, v2);
	linked_list_add(v2_edges, v1);

	g->n_edges ++;
}

void graph_remove_edge(graph* g, graph_node* v1, graph_node* v2) {
	int edges_removed = 0;

	linked_list* v1_edges = graph_get_neighbors(g,v1);
	linked_list* v2_edges = graph_get_neighbors(g,v2);

	// printf("REMOVE EDGE\n");
	// printf("%s:\t", (char*)v1->value); print_list(v1_edges);
	// printf("%s:\t", (char*)v2->value); print_list(v2_edges);

	linked_list_node* aux = v1_edges->head;
	while(aux){
		graph_node* node = (graph_node*) aux->value;
		void* value = node->value;
		if(compare_value(value, v2->value)) {
			edges_removed ++;
			linked_list_remove(v1_edges, aux);
			break;
		}
		aux = aux->next;
	}
	aux = v2_edges->head;
	while(aux){
		graph_node* node = (graph_node*) aux->value;
		void* value = node->value;
		if(compare_value(value, v1->value)) {
			edges_removed ++;
			linked_list_remove(v2_edges, aux);
			break;
		}
		aux = aux->next;
	}
	assert(edges_removed==0 || edges_removed==2);
	if(edges_removed==2) g->n_edges --;
}

int static graph_remove_edge_v1_from_v2(graph* g, graph_node* v1, graph_node* v2) {
	int edges_removed = 0;
	linked_list* v2_edges = graph_get_neighbors(g,v2);

	// printf("REMOVE EDGE\n");
	// printf("%s:\t", (char*)v1->value); print_list(v1_edges);
	// printf("%s:\t", (char*)v2->value); print_list(v2_edges);

	linked_list_node* aux = v2_edges->head;
	while(aux){
		graph_node* node = (graph_node*) aux->value;
		void* value = node->value;
		if(compare_value(value, v1->value)) {
			edges_removed = 1;
			linked_list_remove(v2_edges, aux);
			break;
		}
		aux = aux->next;
	}
	// printf("\n%s:\t", (char*)v1->value); print_list(v1_edges);
	// printf("%s:\t", (char*)v2->value); print_list(v2_edges);

	assert(edges_removed==0 || edges_removed==1);
	if(edges_removed) g->n_edges --;
	return edges_removed;
}

void graph_remove_node(graph* g, graph_node* v) {
	linked_list* edges = graph_get_neighbors(g,v);

	linked_list_node* aux = edges->head;
	while(aux){
		graph_node* node = (graph_node*) aux->value;
		graph_remove_edge_v1_from_v2(g, v, node);
		aux = aux->next;
	}
	
	aux = g->nodes->head;
	while(aux){
		if(aux->value == v){
			linked_list_remove(g->nodes, aux);
			break;
		}
		aux = aux->next;
	}

	g->n_vertices --;
}

void graph_delete(graph * g) {
	if(g==NULL) return;

	linked_list* nodes = graph_get_nodes(g);
	linked_list_node* aux = nodes->head;
	while(aux){
		graph_node* node = (graph_node*) aux->value;
		linked_list_delete(node->out_edges);
		free(node);
		aux = aux->next;
	}
	linked_list_delete(nodes);
	free(g);
}

graph* graph_read_ff(FILE* input) {
	graph* ret = graph_new();
	if (input == NULL)
		return ret;
	int v, e;
	fscanf(input, "%d", &v);
	fscanf(input, "%d", &e);

	int i;
	for (i = 0; i < e; i++) {
		void *v1 = malloc(sizeof(int));
		void *v2 = malloc(sizeof(int));
		fscanf(input, " %c", (char*)v1);
		fscanf(input, "	%c", (char*)v2);
		graph_node* gv1 = graph_add_node(ret, v1);
		graph_node* gv2 = graph_add_node(ret, v2);
		graph_add_edge(ret, gv1, gv2);
	}
	if (ret->n_vertices < v) {
		int rem = v - ret->n_vertices;
		int name = (v + 1);
		for (int i = 0; i < rem; i++, name++) {
			void *v1 = malloc(sizeof(int));
			printf("Indicare un carattere per rappresentare il nodo %d senza archi: ", i+1);
			scanf(" %c", (char*)v1);
			graph_add_node(ret, v1);
		}
	}
	return ret;
}

void graph_print_adj(graph* g) {
	linked_list * nodes = graph_get_nodes(g);
	linked_list_iterator * lli = linked_list_iterator_new(nodes);
	//printf("Head: %s, Tail:%s\n", (char*)(((graph_node*)(nodes->head->value))->value), (char*)(((graph_node*)(nodes->tail->value))->value));
	while (lli != NULL) {
		graph_node * node = (graph_node *)linked_list_iterator_getvalue(lli);
		printf("%s : ", (char *)graph_get_node_value(node));

		linked_list * neighbors = graph_get_neighbors(g, node);
		/*if (neighbors == NULL)
		printf("STRANO\n");
		else if ((neighbors->head == neighbors->tail) && neighbors->head == NULL)
		printf("VUOTO");
		else
		printf("Head %s, Tail %s ->", (char*)graph_get_node_value((graph_node*)neighbors->head->value), (char*)graph_get_node_value((graph_node*)neighbors->tail->value));
		*/
		linked_list_iterator * inner_lli = linked_list_iterator_new(neighbors);
		while (inner_lli != NULL) {
			graph_node * n = (graph_node *)linked_list_iterator_getvalue(inner_lli);
			printf("%s ", (char *)graph_get_node_value(n));
			
			// printf("AAAAAAAAAAA\n");
			inner_lli = linked_list_iterator_next(inner_lli);
		}
		printf("\n");

		lli = linked_list_iterator_next(lli);
	}
}

void print_list(linked_list* l){
    linked_list_node* aux = l->head;
    printf("[");
    if(aux){
		graph_node* node = (graph_node*) aux->value;
		void* value = node->value;
        printf("%s", (char*)value);
        aux = aux->next;
    }
    while(aux){
		graph_node* node = (graph_node*) aux->value;
		void* value = node->value;
        printf(", %s", (char*)value);
        aux = aux->next;
    }
    printf("]\n");
}

static void DFS_print(graph_node* node){
	node->state = EXPLORING;
	linked_list* edges = node->out_edges;
	linked_list_node* it_edge = edges->head;
	while(it_edge){
		graph_node* opposite = (graph_node*) it_edge->value;
		if(opposite->state == UNEXPLORED){
			printf("%s, %s\n", (char*)node->value, (char*)opposite->value);
		}
		it_edge = it_edge->next;
	}
	it_edge = edges->head;
	while(it_edge){
		graph_node* opposite = (graph_node*) it_edge->value;
		if(opposite->state == UNEXPLORED){
			DFS_print(opposite);
		}
		it_edge = it_edge->next;
	}
	node->state = EXPLORED;
}

void graph_print(graph* g) {
	printf("Vertices: %d\tEdges: %d\n", g->n_vertices, g->n_edges);

	linked_list* nodes = g->nodes;
	linked_list_node* aux = nodes->head;
	while(aux){
		graph_node* node = (graph_node*) aux->value;
		if(node->state == UNEXPLORED) DFS_print(node);
		aux = aux->next;
	}
}

static void DFS(graph_node* node){
	node->state = EXPLORING;
	linked_list* edges = node->out_edges;
	linked_list_node* it_edge = edges->head;
	while(it_edge){
		graph_node* opposite = (graph_node*) it_edge->value;
		if(opposite->state == UNEXPLORED){
			DFS(opposite);
		}
		it_edge = it_edge->next;
	}
	node->state = EXPLORED;
}

// Numero di componenti connesse
int graph_n_con_comp(graph * g) {
	int ret = 0;

	linked_list* nodes = g->nodes;
	linked_list_node* aux = nodes->head;
	while(aux){
		graph_node* node = (graph_node*) aux->value;
		if(node->state == UNEXPLORED) {
			DFS(node);
			ret++;
		}
		aux = aux->next;
	}
	return ret;
}


static void DFS_path(graph_node* node, linked_list* list){
	linked_list_add(list, node);

	node->state = EXPLORING;
	linked_list* edges = node->out_edges;
	linked_list_node* it_edge = edges->head;
	while(it_edge){
		graph_node* opposite = (graph_node*) it_edge->value;
		if(opposite->state == UNEXPLORED){
			DFS_path(opposite, list);
		}
		it_edge = it_edge->next;
	}
	node->state = EXPLORED;
}

// Componenti connesse
linked_list* graph_get_con_comp(graph* g) {
	linked_list* ret = linked_list_new();

	linked_list* nodes = g->nodes;
	linked_list_node* aux = nodes->head;
	while(aux){
		graph_node* node = (graph_node*) aux->value;
		if(node->state == UNEXPLORED) {
			graph* to_add = graph_new();
			DFS_path(node, to_add->nodes);
			linked_list_add(ret, to_add);
		}
		aux = aux->next;
	}
	return ret;
}


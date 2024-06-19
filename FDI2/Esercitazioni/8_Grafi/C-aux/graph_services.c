#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "linked_list.h"
#include "graph_services.h"


static int sweep_node(graph_node* n, int timestamp){
    int res = 0;
    printf("%s -> timestamp : %d\n", (char*)n->value, n->timestamp);

    linked_list* nodes = n->out_edges;
    linked_list_iterator* aux = linked_list_iterator_new(nodes);
    while(linked_list_iterator_hasnext(aux)){
        graph_node* node = (graph_node*) linked_list_iterator_getvalue(aux);
        if(node->status == UNEXPLORED){
            printf("%s -> %s : TREE\n", (char*)n->value, (char*)node->value);
            int count = timestamp + res +1;
            node->timestamp = count;
            node->status = EXPLORING;
            res += sweep_node(node, count);
        }
        else if(node->status == EXPLORING){
            printf("%s -> %s : BACK\n", (char*)n->value, (char*)node->value);
        }
        else if(node->status == EXPLORED){
            if(timestamp < node->timestamp)
                printf("%s -> %s : FORWARD\n", (char*)n->value, (char*)node->value);
            else if(timestamp > node->timestamp)
                printf("%s -> %s : CROSS\n", (char*)n->value, (char*)node->value);
            else exit(1);
        }
        node->status = EXPLORED;
        linked_list_iterator_next(aux);
    }
    return res + 1;
}

void sweep(graph * g, char * format_string) {
    if(g==NULL) return;
    linked_list* nodes = g->nodes;
    linked_list_iterator* aux = linked_list_iterator_new(nodes);
    while(linked_list_iterator_hasnext(aux)){
        graph_node* node = (graph_node*) linked_list_iterator_getvalue(aux);
        node->status = UNEXPLORED;
        linked_list_iterator_next(aux);
    }
    
    aux = linked_list_iterator_new(nodes);

    int timestamp = 1;
    while(linked_list_iterator_hasnext(aux)){
        graph_node* node = (graph_node*) linked_list_iterator_getvalue(aux);
        if(node->status == UNEXPLORED){
            node->timestamp = timestamp;
            node->status = EXPLORING;
            int res = sweep_node(node, timestamp);
            timestamp += res;
        }
        node->status = EXPLORED;
        linked_list_iterator_next(aux);
    }
}

// static int compare_node_val(graph_node* n1, graph_node* n2){
//     return (char*)n1->value == (char*)n2->value;
// }



static int DDFS(graph_node* n, linked_list* list){
    int ret = 0;
    linked_list* nodes = n->out_edges;
    linked_list_iterator* aux = linked_list_iterator_new(nodes);
    while(linked_list_iterator_hasnext(aux)){
        graph_node* node = (graph_node*) linked_list_iterator_getvalue(aux);
        if(node->status == UNEXPLORED){
            node->status = EXPLORING;
            ret += DDFS(node, list);
        }
        else if(node->status == EXPLORING) ret = 1;
        else if(node->status == EXPLORED);

        linked_list_iterator_next(aux);
    }
    n->status = EXPLORED;
    linked_list_add(list, 0, n);
    // linked_list_print(list);
    return ret;
}

static void scc_aux(graph_node* n, linked_list* list){
    if(n->status != UNEXPLORED) return;
    n->status = EXPLORED;

    linked_list* edges = n->in_edges;
    linked_list_iterator* it_edge = linked_list_iterator_new(edges);
    while(linked_list_iterator_hasnext(it_edge)){
        graph_node* opposite = (graph_node*) linked_list_iterator_getvalue(it_edge);
        scc_aux(opposite, list);

        linked_list_iterator_next(it_edge);
    }
    n->status = EXPLORED;
    linked_list_enqueue(list, n);
}

// Componenti fortemente connessi (grafi diretti)
void strong_connected_components(graph  *g) {
    linked_list* list = linked_list_new();

    linked_list* nodes = g->nodes;
    linked_list_iterator* aux = linked_list_iterator_new(nodes);
    while(linked_list_iterator_hasnext(aux)){
        graph_node* node = (graph_node*) linked_list_iterator_getvalue(aux);
        if(node->status == UNEXPLORED){
            node->status = EXPLORING;
            DDFS(node,list);
        }

        node->status = EXPLORED;
        linked_list_iterator_next(aux);
    }

    aux = linked_list_iterator_new(nodes);
    while(linked_list_iterator_hasnext(aux)){
        graph_node* node = (graph_node*) linked_list_iterator_getvalue(aux);
        node->status = UNEXPLORED;
        linked_list_iterator_next(aux);
    }

    aux = linked_list_iterator_new(list);
    while(linked_list_iterator_hasnext(aux)){
        graph_node* node = (graph_node*) linked_list_iterator_getvalue(aux);
        if(node->status == UNEXPLORED){
            linked_list* ret = linked_list_new();
            scc_aux(node, ret);

            printf("Sottografo fortemente connesso\n");
            linked_list_iterator* it_ret = linked_list_iterator_new(ret);
            while(linked_list_iterator_hasnext(it_ret)){
                graph_node* opposite = (graph_node*) linked_list_iterator_getvalue(it_ret);
                printf("%s\t", (char*)opposite->value);
                linked_list_iterator_next(it_ret);
            }

            printf("\n");
        }
        linked_list_iterator_next(aux);
    }
}



void topological_sort(graph * g){
    int back_edges = 0;
    linked_list* list = linked_list_new();
    linked_list* ret = linked_list_new();

    linked_list* nodes = g->nodes;
    linked_list_iterator* aux = linked_list_iterator_new(nodes);
    while(linked_list_iterator_hasnext(aux)){
        graph_node* node = (graph_node*) linked_list_iterator_getvalue(aux);
        if(node->status == UNEXPLORED){
            node->status = EXPLORING;
            back_edges += DDFS(node, list);
        }
        node->status = EXPLORED;
        linked_list_iterator_next(aux);
    }
    
    printf("Numero di back edeges: %d\n", back_edges);
    if(back_edges) {
        printf("Il grafo ha cicli e quindi non è un DAG.\n");
        return;
    }
    printf("Il grafo non ha cicli e quindi è un DAG.\n");

    aux = linked_list_iterator_new(nodes);
    while(linked_list_iterator_hasnext(aux)){
        graph_node* node = (graph_node*) linked_list_iterator_getvalue(aux);
        node->status = UNEXPLORED;
        linked_list_iterator_next(aux);
    }

    aux = linked_list_iterator_new(list);
    while(linked_list_iterator_hasnext(aux)){
        graph_node* node = (graph_node*) linked_list_iterator_getvalue(aux);
        if(node->status == UNEXPLORED){
            node->status = EXPLORING;
            DDFS(node, ret);
        }
        node->status = EXPLORED;
        linked_list_iterator_next(aux);
    }
    linked_list_print(ret);
}
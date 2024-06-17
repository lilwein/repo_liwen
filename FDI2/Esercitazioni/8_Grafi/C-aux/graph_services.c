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

static int compare_node_val(graph_node* n1, graph_node* n2){
    return (char*)n1->value == (char*)n2->value;
}



static void graph_create_trasposed_DFS(graph* transposed, graph_node* n){
    // graph_node* transp_n;
    // linked_list_iterator* aux = linked_list_iterator_new(transposed->nodes);
    // while(linked_list_iterator_hasnext(aux)){
    //     transp_n = (graph_node*) linked_list_iterator_getvalue(aux);
    //     if(compare_node_val(n, transp_n)){
    //         break;
    //     }
    //     linked_list_iterator_next(aux);
    // }
    // // printf("%s trasposed: %s\n", (char*)n->value, (char*)transp_n->value);
    
    // linked_list* nodes = n->out_edges;
    // printf("out edges of %s: ", (char*)n->value); linked_list_print(nodes);
    // aux = linked_list_iterator_new(nodes);
    // while(linked_list_iterator_hasnext(aux)){
    //     graph_node* node = (graph_node*) linked_list_iterator_getvalue(aux);
    //     if(node->status == UNEXPLORED) node->status = EXPLORING;

    //     linked_list* t_nodes = transposed->nodes;
    //     linked_list_iterator* t_iter = linked_list_iterator_new(t_nodes);
    //     while(linked_list_iterator_hasnext(t_iter)){
    //         graph_node* t_node = (graph_node*) linked_list_iterator_getvalue(t_iter);
    //         if(compare_node_val(t_node, node)){
    //             printf("Add edge from %s to %s\n", (char*)t_node->value, (char*)transp_n->value);
    //             if(node->status == UNEXPLORED) graph_add_edge(transposed, t_node, transp_n);
    //             // break;
    //         }
    //         linked_list_iterator_next(t_iter);
    //     }
    //     graph_create_trasposed_DFS(transposed, node);
        
    //     node->status = EXPLORED;
    //     linked_list_iterator_next(aux);
    // }

}

void strong_connected_components(graph  *g) {
    // graph* transposed = graph_new();

    // linked_list* nodes = g->nodes;
    // linked_list_iterator* aux = linked_list_iterator_new(nodes);
    // while(linked_list_iterator_hasnext(aux)){
    //     graph_node* node = (graph_node*) linked_list_iterator_getvalue(aux);
    //     node->status = UNEXPLORED;

    //     graph_node* t_node = graph_add_node(transposed, node->value);
    //     t_node->status = UNEXPLORED;

    //     linked_list_iterator_next(aux);
    // }

    // aux = linked_list_iterator_new(nodes);
    // while(linked_list_iterator_hasnext(aux)){
    //     graph_node* node = (graph_node*) linked_list_iterator_getvalue(aux);
    //     if(node->status == UNEXPLORED){
    //         node->status = EXPLORING;
    //         graph_create_trasposed_DFS(transposed, node);
    //     }
    //     linked_list_iterator_next(aux);
    // }
    // printf("Trasnposed: \n");
    // graph_print(transposed);
}

static int topo_aux(graph_node* n, linked_list* list){
    int ret = 0;
    linked_list* nodes = n->out_edges;
    linked_list_iterator* aux = linked_list_iterator_new(nodes);
    while(linked_list_iterator_hasnext(aux)){
        graph_node* node = (graph_node*) linked_list_iterator_getvalue(aux);
        if(node->status == UNEXPLORED){
            node->status = EXPLORING;
            ret += topo_aux(node, list);
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
            back_edges += topo_aux(node, list);
        }
        node->status = EXPLORED;
        linked_list_iterator_next(aux);
    }
    // linked_list_print(list);
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
            topo_aux(node, ret);
        }
        node->status = EXPLORED;
        linked_list_iterator_next(aux);
    }
    linked_list_print(ret);
}
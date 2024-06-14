#include <stdlib.h>
#include <math.h>

#include "graph_services.h"
#include "graph.h"
#include "linked_list.h"
#include "partition.h"

/*
 * Date in input due citta' c1 e c2, ritorna la distanza euclidea tra c1 e c2
 */
double dist(city* c1, city* c2){
	double dx = c1->x - c2->x;
	double dy = c1->y - c2->y;
	return sqrt((dx*dx) + (dy*dy));
}

/*
 * Data una lista contenente un elenco di citta', ritorna un puntatore al grafo completo avente:
 * - un nodo per ogni citta'
 * - un arco per ogni coppia di citta' (x,y) avente come peso la distanza euclidea tra x ed y
 */
graph* get_complete_graph(linked_list* cities){

  graph* g = graph_new();

  linked_list* storage = linked_list_new();
  linked_list* tmp = linked_list_new();

  //Add vertex to graph g
  linked_list_iterator* it = linked_list_iterator_new(cities);
  city* c = linked_list_iterator_getvalue(it);
  
  for( ; linked_list_iterator_hasnext(it); c = (city*) linked_list_iterator_next(it)){
    graph_node* node = graph_add_node(g, c->name);
    linked_list_insert_tail(storage, node);
    linked_list_insert_tail(tmp, c);
  }
  linked_list_iterator_delete(it);


  //Add edge between each couple of graph's vertex.
  while(linked_list_size(storage) > 0 && linked_list_size(tmp)){
    linked_list_node* c1 = storage->head;
    linked_list_node* c2 = tmp->head;
    
    graph_node* curr_node = (graph_node*) c1->value;
    city* curr_city = (city*) tmp->head->value;

    while(c1->next != NULL && c2->next != NULL){
      graph_node* next_node = (graph_node*) c1->next->value;
      city* next_city = (city*) c2->next->value;

      double distance = dist(curr_city, next_city);
      //printf("(%s,%s) : %lf\n", curr_city->name, next_city->name, distance);
      graph_add_edge(g, curr_node, next_node, distance);

      c1 = c1->next;
      c2 = c2->next;
    }
    linked_list_remove_head(storage);
    linked_list_remove_head(tmp);
  }
  return g;
}

/*
 * Dato un grafo, ritorna un puntatore al minheap costituito dagli archi del grafo, usando il peso degli archi come priorita'.
 */
min_heap* get_min_heap_edges(graph* g){
  if(g == NULL)
    return NULL;

  min_heap* mh = min_heap_new();

  //Setting up all vertices's tag to UNEXPLORED
  linked_list_iterator* it = linked_list_iterator_new(g->nodes);
  graph_node* node = (graph_node*) linked_list_iterator_getvalue(it);

  for( ; linked_list_iterator_hasnext(it); node = (graph_node*) linked_list_iterator_next(it))
    node->tag = UNEXPLORED;
  linked_list_iterator_delete(it);


  //Insert edges in min heap
  it = linked_list_iterator_new(g->nodes);
  node = (graph_node*) linked_list_iterator_getvalue(it);

  for( ; linked_list_iterator_hasnext(it); node = (graph_node*) linked_list_iterator_next(it)){
    linked_list_iterator* iti = linked_list_iterator_new(node->incident_edges);
    graph_edge* edge = (graph_edge*) linked_list_iterator_getvalue(iti);
    node->tag = DISCOVERY;
    
    for( ; linked_list_iterator_hasnext(iti); edge = (graph_edge*) linked_list_iterator_next(iti)){
      graph_node* opposite = graph_get_edge_opposite(edge, node);
      if(opposite->tag == UNEXPLORED){
	      min_heap_insert(mh, edge->weight, edge);
      }
    }
    linked_list_iterator_delete(iti);
  }
  linked_list_iterator_delete(it);

  return mh;
}

/*
 * Dato un grafo, ritorna una lista degli archi che rappresentano un Minimum Spanning Tree del grafo.
 */
linked_list* get_mst(graph* g){
  if(g == NULL)
    return NULL;

  partition* p = partition_new(g->n_nodes);

  //Make partition for each vertex
  linked_list_iterator* it = linked_list_iterator_new(g->nodes);
  graph_node* node = (graph_node*) linked_list_iterator_getvalue(it);

  for( ; linked_list_iterator_hasnext(it); node = (graph_node*) linked_list_iterator_next(it))
    partition_makeset(p, node->key);
  linked_list_iterator_delete(it);

  min_heap* mh = get_min_heap_edges(g);
  linked_list* storage = linked_list_new();

  //Compute the mst for graph g
  while(min_heap_size(mh) > 0) {
    min_heap_struct_entry* mhe = min_heap_remove_min(mh);
    graph_edge* edge = (graph_edge*) mhe->value;
    //printf("(%s, %s) : %lf\n", edge->n1->name, edge->n2->name, edge->weight);
    graph_node* n1 = edge->n1;
    graph_node* n2 = edge->n2;

    int id1 = partition_find(p, n1->key);
    int id2 = partition_find(p, n2->key);

    //printf("id1 : %d, id2 : %d\n", id1, id2);
    if(id1 != id2){
      partition_union(p, id1, id2);
      linked_list_insert_tail(storage, edge);
    }
  }

  //Clean up
  min_heap_free(mh);
  partition_delete(p);

  //Print mst
  it = linked_list_iterator_new(storage);
  graph_edge* edge = (graph_edge*) linked_list_iterator_getvalue(it);

  printf("MST :\n");
  for( ; linked_list_iterator_hasnext(it); edge = (graph_edge*) linked_list_iterator_next(it)){
    printf("(%s,%s) : %lf\n", edge->n1->name, edge->n2->name, edge->weight);
  }
  linked_list_iterator_delete(it);

  return storage;
}

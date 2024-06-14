#include <stdlib.h>
#include <math.h>

#include "graph_services.h"
#include "graph.h"
#include "linked_list.h"


double dist(centrale* c1, centrale* c2){
	double dx = c1->x - c2->x;
	double dy = c1->y - c2->y;
	return sqrt((dx*dx) + (dy*dy));
}


void graph_print_powplant(graph* g) {
	if (g) {
		linked_list_iterator *it = linked_list_iterator_new(g->nodes);
		graph_node* cur = (graph_node*)linked_list_iterator_getvalue(it);
		while (linked_list_iterator_hasnext(it)) {
			printf("%s: ", ((centrale*)(cur->object))->name);
			linked_list_iterator *it2 = linked_list_iterator_new(cur->incident_edges);
			graph_edge* edge = linked_list_iterator_getvalue(it2);
			while (linked_list_iterator_hasnext(it2)) {
				printf("%s:%f ", edge->n2 == cur ? (((centrale*)(edge->n1->object))->name) : (((centrale*)(edge->n2->object))->name), edge->weight);
				edge = linked_list_iterator_next(it2);
			}
			printf("\n");
			linked_list_iterator_delete(it2);
			cur = linked_list_iterator_next(it);
		}
		linked_list_iterator_delete(it);
		printf("n_nodes:%d,  n_edges:%d\n", g->n_nodes, g->n_edges);
	}
	else {
		printf("ERROR - invocation with NULL in graph_print\n");
		return;
	}
}


graph* get_complete_graph(linked_list* pp){
  if(pp == NULL)
    return NULL;

  graph* g = graph_new();
  linked_list* nodes = linked_list_new();
  linked_list* storage = linked_list_new();

  //Add vertex to input graph
  linked_list_iterator* it = linked_list_iterator_new(pp);
  centrale* c = (centrale*) linked_list_iterator_getvalue(it);

  for( ; linked_list_iterator_hasnext(it); c = (centrale*) linked_list_iterator_next(it)){
    graph_node* node = graph_add_node(g, c);
    linked_list_insert_tail(nodes, node);
    linked_list_insert_tail(storage, c);
  }
  linked_list_iterator_delete(it);


  //Add edges to input graph
  while(linked_list_size(nodes) > 0 && linked_list_size(storage)){
    linked_list_node* lln = nodes->head;
    //linked_list_node* llnc = storage->head;

    graph_node* curr_node = (graph_node*) lln->value;
    //centrale* curr_central = (centrale*) lln->value;

    while(lln->next != NULL /*&& llnc->next != NULL*/){
      graph_node* next_node = (graph_node*) lln->next->value;
      // centrale* next_central = (centrale*) llnc->next->value;

      graph_add_edge(g, curr_node, next_node, INF);

      lln = lln->next;
      //llnc = llnc->next;
    }
    linked_list_remove_head(nodes);
    linked_list_remove_head(storage);
  }
  linked_list_delete(nodes);
  linked_list_delete(storage);

  return g;
}


void set_weights_in_graph(graph* g){
  if(g == NULL)
    return;

  linked_list_iterator* it = linked_list_iterator_new(g->nodes);
  graph_node* node = (graph_node*) linked_list_iterator_getvalue(it);

  for( ; linked_list_iterator_hasnext(it); node = (graph_node*) linked_list_iterator_next(it)){
    min_heap* mh = min_heap_new();

    centrale* curr_central = (centrale*) node->object;
    linked_list_iterator* iti = linked_list_iterator_new(node->incident_edges);
    graph_edge* edge = (graph_edge*) linked_list_iterator_getvalue(iti);

    for( ; linked_list_iterator_hasnext(iti); edge = (graph_edge*) linked_list_iterator_next(iti)){
      graph_node* opposite = graph_get_edge_opposite(edge, node);
      centrale* next_central = (centrale*) opposite->object;
      double distance = dist(curr_central, next_central);

      min_heap_insert(mh, distance, edge);
    }
    linked_list_iterator_delete(iti);
    int counter = 0;

    while(counter < 3) {
      min_heap_struct_entry* mhe = min_heap_remove_min(mh);
      graph_edge* curr_edge = (graph_edge*) mhe->value;

      double curr_dist = dist((centrale*) ((graph_node*) curr_edge->n1)->object
			      ,(centrale*) ((graph_node*) curr_edge->n2)->object);
      curr_edge->weight = curr_dist;
      printf("(%s,%s) : %lf\n", ((centrale*) (((graph_node*)curr_edge->n1)->object))->name,
	     ((centrale*) (((graph_node*)curr_edge->n2)->object))->name, curr_edge->weight);
      counter++;
    }
    min_heap_free(mh);
  }
  linked_list_iterator_delete(it);
}




void primJarnik(graph* g, linked_list* storage){

  linked_list_iterator* it = linked_list_iterator_new(g->nodes);
  graph_node* source = (graph_node*) linked_list_iterator_getvalue(it);
  
  linked_list_iterator_delete(it);

  //Store each vertex in min heap
  graph_node** prev = (graph_node**) malloc(sizeof(graph_node*)*g->n_nodes);
  double* dist = (double*) malloc(sizeof(double)*g->n_nodes);
  min_heap* mh = min_heap_new();

  it = linked_list_iterator_new(g->nodes);
  graph_node* node = (graph_node*) linked_list_iterator_getvalue(it);
  
  
  for( ; linked_list_iterator_hasnext(it);  node = (graph_node*) linked_list_iterator_next(it)){
    if(node != source)
      dist[node->key] = INF;
    else
      dist[node->key] = 0;

    prev[node->key] = NULL;
    min_heap_insert(mh, dist[node->key], node);
  }
  linked_list_iterator_delete(it);
  

  //Build mst of graph
  while(min_heap_size(mh) > 0){
    min_heap_struct_entry* mhe = min_heap_remove_min(mh);
    graph_node* curr = (graph_node*) mhe->value;

    curr->tag = DISCOVERY;
    
    if(prev[curr->key] != NULL){
      graph_edge* e = (graph_edge*) malloc(sizeof(graph_edge));
      e->n1 = prev[curr->key];
      e->n2 = curr;
      e->weight = dist[curr->key];
      
      linked_list_insert_tail(storage, e);
    }
    
    linked_list_iterator* iti = linked_list_iterator_new(curr->incident_edges);
    graph_edge* edge = (graph_edge*) linked_list_iterator_getvalue(iti);

    for( ; linked_list_iterator_hasnext(iti); edge = (graph_edge*) linked_list_iterator_next(iti)){
      graph_node* opp = (curr != edge->n1) ? edge->n1 : edge->n2;

      if(edge->weight < dist[opp->key] && opp->tag == UNEXPLORED){
		dist[opp->key] = edge->weight;
		min_heap_replace_key(mh, mhe, dist[opp->key]);   //come chiave gli metto la distanza piu vicina da qualsiasi altro arco
		prev[opp->key] = curr;
      }
    }
    linked_list_iterator_delete(iti);
  }
  min_heap_free(mh);
}


 

linked_list* get_min_wire(graph* g){
  if(g == NULL)
    return NULL;

  linked_list* result = linked_list_new();

  //Setting vertex's tag to UNEXPLORED
  linked_list_iterator* it = linked_list_iterator_new(g->nodes);
  graph_node* node = (graph_node*) linked_list_iterator_getvalue(it);
  
  for( ; linked_list_iterator_hasnext(it); node = (graph_node*) linked_list_iterator_next(it))
    node->tag = UNEXPLORED;
  
  linked_list_iterator_delete(it);
  
  //Build MST
  //it = linked_list_iterator_new(g->nodes);
  //node = (graph_node*) linked_list_iterator_getvalue(it);

  printf("MST :\n");
  primJarnik(g, result);
  
  return result;
}

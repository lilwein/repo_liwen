#include "graph_services.h"
#include "min_heap.h"
#include "partition.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double dist(point* p1, point* p2){
	double dx = p1->x - p2->x;
	double dy = p1->y - p2->y;
	return sqrt((dx*dx) + (dy*dy));
}

int edge_to_code(int x, int y){
	if(y < x){
		int z = y;
		y = x;
		x = z;
	}
    return (int)((x*100) + y);
}

int* code_to_edge(int x){
    int* ret = (int*) malloc(sizeof(int) * 2);
    double tmp = x/100.;
    ret[0] = (int)(tmp);
    ret[1] = (int)((tmp - ret[0])*100);
    return ret;
}

graph* make_graph(point** points, int n){
	/*DA IMPLEMENTARE*/
	return NULL;
}

graph* get_best_connections(graph* g){
	/*DA IMPLEMENTARE*/
	return NULL;
}

int get_tree_height(graph* g, int v){
	/*DA IMPLEMENTARE*/
	return 0;
}
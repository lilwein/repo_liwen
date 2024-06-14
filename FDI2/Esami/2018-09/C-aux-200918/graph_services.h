#include "graph.h"
#include "linked_list.h"
#include "min_heap.h"

#ifndef __GRAPH_SERVICES_H__
#define __GRAPH_SERVICES_H__


// "Infinity"
#define INF (100000)


typedef struct centrale{
    char* name;
    double x;
    double y;
} centrale;


/*
 * Stampa a video una rappresentazione del grafo delle Centrali elettriche.
 */
void graph_print_powplant(graph*);


/*
 * Data una lista contenente un elenco di Centrali, ritorna un puntatore al grafo completo avente:
 * - un nodo per ogni Centrale
 * - un arco per ogni coppia di Centrali (x,y) distinte
 */
graph* get_complete_graph(linked_list* l);


/*
 * Dato un grafo delle Centrali completo g, modificare i pesi degli archi di g nel seguente modo:
 * - detto n un nodo ed l la sua lista di archi incidenti, calcolare la distanza tra n e ciascun nodo connesso dagli archi in l. Sia w tale distanza.
 * - settare il peso dell' i-esimo arco incidente ad n a:
 *      - w, se non esistono 3 archi incidenti ad n, con peso inferiore a w; 
 *      - INF altrimenti.
 */
void set_weights_in_graph(graph* g);


/*
 * Dato un grafo, ritorna una lista degli archi che minimizzano la quantita' di cavo per connettere tutte le Centrali di g.
 */
linked_list* get_min_wire(graph* g);


#endif // !__GRAPH_SERVICES_H__

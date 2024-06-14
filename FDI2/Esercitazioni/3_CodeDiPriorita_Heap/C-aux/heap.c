#include <stdlib.h>
#include <stdio.h>
#include "heap.h"

heap * heap_new(HEAP_TYPE is_min_heap, int capacity) {
	heap * new = (heap*) malloc(sizeof(heap));

	heap_entry** array = (heap_entry**) malloc(capacity*sizeof(heap_entry*));
	// for(int i=0; i< capacity; i++){
	// 	heap_entry* entry = (heap_entry*) malloc(sizeof(heap_entry));
	// }
	new->array = array;
	new->size = capacity;
	new->used = 0;
	new->is_min_heap = is_min_heap;
	
	return new;
}

HEAP_TYPE heap_type(heap * hh) {
	return hh->is_min_heap;
}

int heap_peek(heap * hh) {
	return hh->array[0]->key;
}


void upHeap(heap* hh, int position){
	if(position==0) return;
	int parent = (position-1)/2;

	if(hh->array[position]->key < hh->array[parent]->key ) { //min_heap
		
		hh->array[position]->position = parent;
		hh->array[parent]->position = position;
		
		int temp = hh->array[position]->key;
		hh->array[position]->key = hh->array[parent]->key;
		hh->array[parent]->key = temp;

		upHeap(hh, parent);
	}
}

heap_entry * heap_add(heap * hh, int key) {

	heap_entry* entry = (heap_entry*) malloc(sizeof(heap_entry));
	entry->key = key;
	entry->position = hh->used;

	hh->array[hh->used] = entry;
	upHeap(hh,hh->used);

	hh->used++;

	return NULL;
}

int get_key_entry(heap_entry * ee) {
	return ee->key;
}

int heap_size(heap * hh) {
	return hh->used;
}

void downHeap(heap* hh, int position){
	// if(position==0) return;
	int leftChild = (position*2) +1;
	int rightChild = (position*2) +2;

	if(leftChild <= heap_size(hh)-1) {
		int min_pos = leftChild;
		int minore = hh->array[leftChild]->key;
		if(rightChild <= heap_size(hh)-1) {
			if(minore > hh->array[rightChild]->key ) {
				minore = hh->array[rightChild]->key;
				min_pos = rightChild;
			}
		}
		if(minore < hh->array[position]->key ){

			hh->array[position]->position = min_pos;
			hh->array[min_pos]->position = position;
			
			int temp = hh->array[position]->key;
			hh->array[position]->key = hh->array[min_pos]->key;
			hh->array[min_pos]->key = temp;

			downHeap(hh, min_pos);
		}
	}
}

int heap_poll(heap * hh) {
	if(!hh) return 0;
	int minKey = hh->array[0]->key;

	hh->array[0]->key = hh->array[heap_size(hh)-1]->key;
	free(hh->array[heap_size(hh)-1]);
	hh->used--;

	downHeap(hh, 0);
	
	return minKey;
}

void heap_delete(heap * hh) {
	return;
}

heap * array2heap(int * array, int size, HEAP_TYPE is_min_heap) {
	return NULL;
}

void heap_print(heap * hh) {
	int k;
	for (k = 0; k < hh->used; k++)
		printf(" %d", hh->array[k]->key);
	printf("\n\n");
}

void heap_sort(int * array, int size) {
	return;
}

void heap_update_key(heap * hh, heap_entry * ee, int key) {
	return;        
}


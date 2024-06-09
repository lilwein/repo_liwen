#include "mat_sparsa_lista.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct elem {
	int row;
	int col;
	int value;
	struct elem* next;
} elem;

struct matrice_sparsa {
	int rows;
	int columns;
	elem* first;
};

matrice_sparsa* matrice_sparsa_new(int m, int n) {
	matrice_sparsa* new = (matrice_sparsa*) malloc(sizeof(matrice_sparsa));
	new->rows = m;
	new->columns = n;
	
	return new;
}

void matrice_sparsa_delete(matrice_sparsa* mat) {
	elem* aux = mat->first;
	while(aux){
		elem* temp = aux->next;
		free(aux);
		aux = temp;
	} 
	free(mat);
}

int get_num_row(matrice_sparsa* mat) {
	return mat->rows;
}

int get_num_col(matrice_sparsa* mat) {
	return mat->columns;
}

void mat_set(matrice_sparsa* mat, int i, int j, int x) {
	elem* aux = mat->first;
	if(!aux){
		if(x==0) return;

		elem* new_elem = (elem*) malloc(sizeof(elem));
		new_elem->row = i;
		new_elem->col = j;
		new_elem->value = x;

		new_elem->next = 0;
		mat->first = new_elem;
		return;
	}
	elem* prev = 0;

	while(aux){
		// printf("row=%d\tcol=%d\ti=%d\tj=%d\n", aux->row, aux->col, i, j);
		if(aux->row > i || (aux->row == i && aux->col > j ) ){
			// printf("BBBBBB\n");
			if(x==0) return;

			elem* new_elem = (elem*) malloc(sizeof(elem));
			new_elem->row = i;
			new_elem->col = j;
			new_elem->value = x;

			new_elem->next = aux;
			
			// printf("CCCCCC\n");

			if(!prev) mat->first = new_elem;
			else prev->next = new_elem;

			// printf("mat_first: row=%d\tcol=%d\n", mat->first->row, mat->first->col);
			// printf("DDDDDD\n");
			return;
		}
		else if(aux->row==i && aux->col==j) {
			if(x==0) {
				// printf("EEEEEEE\n");
				if(!prev) mat->first = aux->next;
				else prev->next = aux->next;
				free(aux);
				return;
			}

			aux->value = x;
			return;
		}

		prev = aux;
		aux = aux->next;
	}
	if(x==0) return;

	elem* new_elem = (elem*) malloc(sizeof(elem));
	new_elem->row = i;
	new_elem->col = j;
	new_elem->value = x;

	new_elem->next = 0;
	prev->next = new_elem;
	return;
}

int mat_get(matrice_sparsa* mat, int i, int j) {
	
	elem* aux = mat->first;
	if(!aux){
		exit(EXIT_FAILURE);
	}

	while(aux){
		if(aux->row > i || (aux->row == i && aux->col > j ) ){
			return 0;
		}
		else if(aux->row==i && aux->col==j) {
			return aux->value;
		}
		aux = aux->next;
	}
	return 0;
}

void mat_print(matrice_sparsa* mat) {

	elem* aux = mat->first;
	if(!aux){
		printf("Matrice Nulla\n");
	}

	for( int i=0; i<mat->rows; i++){
		for( int j=0; j<mat->columns; j++){
			if( !aux || aux->row > i || (aux->row == i && aux->col > j ) ){
				printf("0\t");
			}
			else if(aux->row==i && aux->col==j) {
				printf("%d\t", aux->value);
				aux = aux->next;
			}
		}
		printf("\n");
	}
}

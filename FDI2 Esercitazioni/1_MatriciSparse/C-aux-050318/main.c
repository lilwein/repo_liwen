#include "mat_sparsa_lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

matrice_sparsa* read_mat_ff(const char* file_name);

int main() {
	matrice_sparsa* mat1 = read_mat_ff("mat.dat");

	printf("Original Matrix:\n");
	mat_print(mat1);
	printf("\n");
	printf("########################################");
	printf("########################################");
	printf("\n");
	printf("\n");
	printf("Added -> 0,0,5\n");
	mat_set(mat1, 0, 0, 5);
	mat_print(mat1);
	printf("\n");
	printf("Added -> 1,1,45\n");
	mat_set(mat1, 1, 1, 45);
	mat_print(mat1);
	printf("\n");
	printf("Added -> 0,0,0\n");
	mat_set(mat1, 0, 0, 0);
	mat_print(mat1);
	printf("\n");
	printf("Added -> 2,3,1\n");
	mat_set(mat1, 2, 3, 1);
	mat_print(mat1);
	printf("\n");
	printf("Added -> 3,0,5\n");
	mat_set(mat1, 3, 0, 5);
	mat_print(mat1);
	printf("\n");
	printf("Added -> 18,17,12\n");
	mat_set(mat1, 18, 17, 12);
	mat_print(mat1);
	printf("\n");
	printf("Added -> 4,4,0\n");
	mat_set(mat1, 4, 4, 0);
	mat_print(mat1);
	printf("\n");
}

matrice_sparsa* read_mat_ff(const char* file_name){
	FILE* file = fopen(file_name, "r");
	int val = 0;
	int m, n;
	fscanf(file, "%d", &val);
	m = val;
	fscanf(file, "%d", &val);
	n = val;
	matrice_sparsa* ret = matrice_sparsa_new(m, n);
	int i, j;
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			//printf("%d ", i);
			fscanf(file, "%d", &val);
			mat_set(ret, i, j, val);
		}
	}
	fclose(file);
	return ret;
}
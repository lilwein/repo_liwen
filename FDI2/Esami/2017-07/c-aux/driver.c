#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bst.h"


int main(int argc, char** argv) {

        BST * b = BST_new();

        BST_insert(b, 1, 4);
        BST_insert(b, 6, 6);
        BST_insert(b, 3, 4);
        BST_insert(b, 5, 1);
        BST_insert(b, 6, 4);
        BST_insert(b, 2, 7);
        BST_insert(b, 2, 2);
        BST_insert(b, 8, 1);
        BST_insert(b, 6, 2);
        BST_insert(b, 8, 7);
        BST_insert(b, 1, 1);
        BST_insert(b, 8, 1);
        

        printf("Albero: \n");
        BST_print(b);

        printf("\nRicerca valore x: \n");
        for (int k=0; k<10; k++){
            printf("Numero nodi con coordinata %d: %d\n", k, aligned(b, k));
        }

        printf("\nRicerca range: \n");
        int coordinatesTest[11][4] = {
            {0, 0, 10, 10},
            {2, 2, 2, 2},
            {2, 6, 2, 6},
            {3, 0, 2, 10},
            {0, 3, 10, 2},
            {0, 4, 10, 4},
            {2, 4, 10, 4},
            {3, 5, 2, 1},
            {2, 2, 3, 4},
            {2, 7, 3, 4},
            {4, 3, 7, 5}        };

        for (int i=0; i<11; i++){
            printf("x1=%d, x2=%d, y1=%d, y2=%d: %d\n", coordinatesTest[i][0], coordinatesTest[i][1], coordinatesTest[i][2], coordinatesTest[i][3], rangeQ(b,coordinatesTest[i][0], coordinatesTest[i][1], coordinatesTest[i][2], coordinatesTest[i][3])); 
        }


        BST_delete(b);
}

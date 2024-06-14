#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bst.h"


int main(int argc, char** argv) {

        BST * b = BST_new();

        BST_insert(b, 3);
        BST_insert(b, 12);
        BST_insert(b, 7);
        BST_insert(b, 5);
        BST_insert(b, 1);
        BST_insert(b, 7);
        BST_insert(b, 15);
        BST_insert(b, 1);
        BST_insert(b, 8);
        BST_insert(b, 7);
        BST_insert(b, 12);

        printf("Albero: \n");
        BST_print(b);

        printf("\nRicerca valore: \n");
        for (int k=0; k<20; k++){
            if (BST_find(b,k)==NULL)
                printf("Nodo con chiave %d NON trovato\n", k);
            else
                printf("Nodo con chiave %d trovato\n", k);
        }

        printf("\nRicerca massimo: \n");
        for (int level=1; level<20; level++){
            int max = maxOnLevel(b,level);

            if (max == -1)
                printf("Livello %d vuoto\n", level);
            else
                printf("Valore massino nel livello %d: %d\n",level, max);
        }

        BST_delete(b);
}

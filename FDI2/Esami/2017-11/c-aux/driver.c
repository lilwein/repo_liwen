#include <stdio.h>
#include <stdlib.h>
#include "bst.h"




int main(void) {
    BST *b1 = newBST();
    BST_insert(b1, 3);
    BST_insert(b1, 12);
    BST_insert(b1, 7);
    BST_insert(b1, 5);
    BST_insert(b1, 1);
    BST_insert(b1, 7);
    BST_insert(b1, 15);
    BST_insert(b1, 1);
    BST_insert(b1, 8);
    BST_insert(b1, 7);
    BST_insert(b1, 12);

    BST *b2 = newBST();
    	
    BinNode *root, *l1, *l2, *l3, *r1, *r2;
    root = BST_insert(b2, 13);
    root->left = l1 = newBinNode(5);
    root->right = r1 = newBinNode(20);
    l1->left = l2 = newBinNode(3);
    l1->right = r2 = newBinNode(17);
    r1->right = l3 = newBinNode(25);
        
    printf("\t Primo Albero: \n");
    BST_print(b1);

    printf("Test BST: ");
    int BSTresult = isBST(b1);
    if (BSTresult == -1) printf("Funzione non implementata\n");     
    else if (BSTresult == 0) printf("Albero non BST\n");     
    else printf("Albero BST\n");     
    
    printf("Test Balanced: ");
    int balresult = isBalanced(b1);
    if (balresult == -1) printf("Funzione non implementata\n");     
    else if (balresult == 0) printf("Albero non bilanciato\n");     
    else printf("Albero bilanciato\n");     

    printf("Test AVL: ");
    int AVLresult = isAVL(b1);
    if (AVLresult == -1) printf("Funzione non implementata\n");     
    else if (AVLresult == 0) printf("Albero non AVL\n");     
    else printf("Albero AVL\n");     
    

    printf("-------------------\n");
    printf("\t Secondo Albero: \n");
    BST_print(b2);

    printf("Test BST: ");
    BSTresult = isBST(b2);
    if (BSTresult == -1) printf("Funzione non implementata\n");     
    else if (BSTresult == 0) printf("Albero non BST\n");     
    else printf("Albero BST\n");     
    
    printf("Test Balanced: ");
    balresult = isBalanced(b2);
    if (balresult == -1) printf("Funzione non implementata\n");     
    else if (balresult == 0) printf("Albero non bilanciato\n");     
    else printf("Albero bilanciato\n");     
    

    printf("Test AVL: ");
    AVLresult = isAVL(b2);
    if (AVLresult == -1) printf("Funzione non implementata\n");     
    else if (AVLresult == 0) printf("Albero non AVL\n");     
    else printf("Albero AVL\n");
    
    return 0;
}

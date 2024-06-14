#ifndef BST_H
#define	BST_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct BinNode {
    int key; // interi positivi
    struct BinNode * left;
    struct BinNode * right;
} BinNode;

typedef struct BST {
        BinNode * root;
} BST;

BST * newBST();
BinNode * newBinNode(int);

// altri prototipi 
BinNode *BST_insert(BST *t, int k);
void BST_print(BST *t);
int isBST(BST *t);
int isBalanced(BST *t);
// fine prototipi


#ifdef	__cplusplus
}
#endif

#endif	/* BST_H */


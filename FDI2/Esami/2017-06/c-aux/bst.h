#ifndef BST_H
#define	BST_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct BinNode {
    int key;
    struct BinNode * left;
    struct BinNode * right;
} BinNode;

typedef struct BST {
        BinNode * root;
        int size;
} BST;

BST * BST_new();
BinNode * BST_insert(BST * t, int k);
BinNode * BST_find(BST * t, int k);

void BST_delete(BST * h);
void BST_print(BST * h);

int maxOnLevel (BST * b, int level);

#ifdef	__cplusplus
}
#endif

#endif	/* BST_H */


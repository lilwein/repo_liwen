#include <stdlib.h>
#include <assert.h>
#include "bstnode.h"

bstnode *newBSTNode(double x, double y) {
    bstnode *tmp = malloc(sizeof(bstnode));
    assert(tmp != NULL);
    tmp->x_coord = x;
    tmp->y_coord = y;
    tmp->left = NULL;
    tmp->right = NULL;
    return tmp;
}

#ifndef _BSTNODEH
#define _BSTNODEH


struct bstnode {
    double x_coord;
    double y_coord;
    struct bstnode *left;
    struct bstnode *right;
};

typedef struct bstnode bstnode;

bstnode *newBSTNode(double, double);


#endif

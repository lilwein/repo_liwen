#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

struct tree {
	int key;
    void * value;
    struct tree * left;
    struct tree * right;
};

tree * build_tree_1() {

	tree * n6 = calloc(sizeof(tree), 1);
	n6->key = 6;

	tree * n3 = calloc(sizeof(tree), 1);
	n3->key = 3;

	tree * n12 = calloc(sizeof(tree), 1);
	n12->key = 12;

	tree * n1 = calloc(sizeof(tree), 1);
	n1->key = 1;

	tree * n5 = calloc(sizeof(tree), 1);
	n5->key = 5;

	tree * n7 = calloc(sizeof(tree), 1);
	n7->key = 7;

	tree * n15 = calloc(sizeof(tree), 1);
	n15->key = 15;

	n6->left = n3;
	n6->right = n12;

	n3->left = n1;
	n3->right = n5;

	n12->left = n7;
	n12->right = n15;

	return n6;
}

tree * build_tree_2() {

	tree * n6 = calloc(sizeof(tree), 1);
	n6->key = 6;

	tree * n3 = calloc(sizeof(tree), 1);
	n3->key = 3;

	tree * n12 = calloc(sizeof(tree), 1);
	n12->key = 12;

	tree * n1 = calloc(sizeof(tree), 1);
	n1->key = 1;

	tree * n5 = calloc(sizeof(tree), 1);
	n5->key = 5;

	tree * n7 = calloc(sizeof(tree), 1);
	n7->key = 7;

	tree * n15 = calloc(sizeof(tree), 1);
	n15->key = 15;

	n6->right = n3;
	n6->left = n12;

	n3->left = n1;
	n3->right = n5;

	n12->left = n7;
	n12->right = n15;

	return n6;
}

tree * build_tree_3() {

	tree * n6 = calloc(sizeof(tree), 1);
	n6->key = 6;

	tree * n3 = calloc(sizeof(tree), 1);
	n3->key = 3;

	tree * n12 = calloc(sizeof(tree), 1);
	n12->key = 12;

	tree * n1 = calloc(sizeof(tree), 1);
	n1->key = 1;

	tree * n5 = calloc(sizeof(tree), 1);
	n5->key = 5;

	n6->left = n3;
	
	n3->left = n1;
	n3->right = n5;

	n5->right = n12;

	return n6;
}

void tree_delete(tree * tt) {

	tree * t = tt;
	if (t == NULL)
		return;

	tree_delete(t->left);
	tree_delete(t->right);
	free(t);
}

// IS TREE?
static int tree_is_bst_aux(tree * t, int last_max){
	if(t==NULL) return last_max;

	int max = tree_is_bst_aux(t->left, last_max);
	if(max > t->key || max == -1 ) return -1;
	
	return tree_is_bst_aux(t->right, t->key);
}

int tree_is_bst(tree * tt) {
	if(tree_is_bst_aux(tt, 0) == -1) return 0;
	return 1;
}


// IS BALANCED? 
static int tree_is_balanced_aux(tree * t) {
	if(t==NULL) return 0;

	int sx = tree_is_balanced_aux(t->left);
	int dx = tree_is_balanced_aux(t->right);

	if( (sx==-1 || dx==-1) || abs(sx-dx)>1) return -1;
	if(sx+dx == 0) return 1;

	int higher = (sx >= dx)? sx:dx;
	return higher + 1 ;
}

int tree_is_balanced(tree * tt) {
	if(tree_is_balanced_aux(tt)==-1) return 0;
	return 1;
}


// IS AVL?
static int tree_is_avl_aux(tree * t, int last_max, int* h){
	if(t==NULL) {
		*h = 0;
		return last_max;
	}
	int left_height, right_height;
	
	int max = tree_is_avl_aux(t->left, last_max, &left_height);
	if(max > t->key || max == -1 ) return -1;
	
	int right = tree_is_avl_aux(t->right, t->key, &right_height);

	int height = (left_height >= right_height)? left_height:right_height;
	*h = height + 1;

	if(abs(left_height-right_height) > 1) return -1;

	return right;
}

int tree_is_avl(tree * tt) {
	int h;
	if(tree_is_avl_aux(tt, 0, &h) == -1) return 0;
	return 1;
}
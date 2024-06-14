#include <stdlib.h>
#include <stdio.h>
#include "bst.h"
#include "queue.h"

static BinNode * BST_node_new(int x, int y) {
    /*NON MODIFICARE*/
    BinNode * b = malloc(sizeof(BinNode));
	b->coordinates[0] = x;
	b->coordinates[1] = y;
	b->left = NULL;
	b->right = NULL;

	return b;
}

BST * BST_new() {
    /*NON MODIFICARE*/
        BST * b = malloc(sizeof(BST));
        b->root = NULL;

	return b;
}

BinNode* BST_insert_aux(BinNode* node, int x, int y){

  if(x < node->coordinates[0] || (x == node->coordinates[0] && y < node->coordinates[1])){
    if(node->left == NULL){
      node->left = BST_node_new(x, y);
      return node->left;
    }else
      return BST_insert_aux(node->left, x, y);
  }else if(x > node->coordinates[0] || (x == node->coordinates[0] && y > node->coordinates[0])){
    if(node->right == NULL){
      node->right = BST_node_new(x, y);
      return node->right;
    }else
      return BST_insert_aux(node->right, x, y);
  }else
    return NULL;
}


BinNode * BST_insert(BST * b, int x, int y) {
  if(b->root == NULL){
    b->root = BST_node_new(x, y);
    return b->root;
  }
  return BST_insert_aux(b->root, x, y);
}


static void BST_delete_aux(BinNode * t) {
/*NON MODIFICARE*/
	if (t == NULL)
		return;

        BST_delete_aux(t->left);
        BST_delete_aux(t->right);
	free(t);
}

void BST_delete(BST * b) {
/*NON MODIFICARE*/
	if (b == NULL)
		return;

        BST_delete_aux(b->root);
        free(b);
}

void BST_print_aux(BinNode * t, int level) {
    /*MODIFICABILE*/
    int i;
    for (i = 0; i < level - 1; i++) {
    	printf("   ");
    }

    if (level > 0) {
    	printf(" |--");
    }

    if (t == NULL){
        printf("%c \n",35);
        return;
    }

    printf("(%d,%d)\n", t->coordinates[0],t->coordinates[1]);

    BST_print_aux(t->left, level + 1);
    BST_print_aux(t->right, level + 1);
}

void BST_print(BST * b){
    /*MODIFICABILE*/
    return BST_print_aux(b->root, 0);
}

int aligned_aux(BinNode* node, int x){
  if(node == NULL)
    return 0;

  int left = 0, right = 0;
  
  if(node->coordinates[0] == x){
    left = 1 + aligned_aux(node->left, x);
    right = aligned_aux(node->right, x);
  }else{
    left = aligned_aux(node->left, x);
    right = aligned_aux(node->right, x);
  }
  return left + right;
}


int aligned(BST * b, int x){
  if(b->root == NULL)
    return 0;
  return aligned_aux(b->root, x);
}

int rangeQ_aux(BinNode* node, int x_min, int y_min, int x_max, int y_max){
  if(node == NULL)
    return 0;

  int left = 0, right = 0;
  
  if(node->coordinates[0] >= x_min && node->coordinates[0] <= x_max &&
     node->coordinates[1] >= y_min && node->coordinates[1] <= y_max){
    //printf("(%d,%d) \n", node->coordinates[0], node->coordinates[1]);
    left = 1 + rangeQ_aux(node->left, x_min, y_min, x_max, y_max);
    right = rangeQ_aux(node->right, x_min, y_min, x_max, y_max);
  }else {
    left = rangeQ_aux(node->left, x_min, y_min, x_max, y_max);
    right = rangeQ_aux(node->right, x_min, y_min, x_max, y_max);
  }
  return left + right;
}

int rangeQ(BST * b, int x1, int y1, int x2, int y2){
  if(b->root == NULL)
    return 0;
  
  int x_min, x_max, y_min, y_max;

  if(x1 < x2){
    x_min = x1;
    x_max = x2;
  }else {
    x_min = x2;
    x_max = x1;
  }

  if(y1 < y2){
    y_min = y1;
    y_max = y2;
  }else {
    y_min = y2;
    y_max = y1;
  }
  //printf("x_min : %d, y_min : %d, x_max : %d, y_max : %d\n", x_min, y_min, x_max, y_max);
  return rangeQ_aux(b->root, x_min, y_min, x_max, y_max);
}






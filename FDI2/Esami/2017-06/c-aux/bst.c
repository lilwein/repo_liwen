#include <stdlib.h>
#include <stdio.h>
#include "bst.h"
#include "queue.h"

static BinNode * BST_node_new(int k) {
        BinNode * b = malloc(sizeof(BinNode));
	b->key = k;
	b->left = NULL;
	b->right = NULL;

	return b;
}

BST * BST_new() {
        BST * b = malloc(sizeof(BST));
        b->root = NULL;

	return b;
}

BinNode* BST_insert_aux(BinNode* node, int k){

  if(k < node->key){
    if(node->left == NULL){
      node->left = BST_node_new(k);
      return node->left;
    }else
      return BST_insert_aux(node->left, k);
  }else if(k > node->key){
    if(node->right == NULL){
      node->right = BST_node_new(k);
      return node->right;
    }else
      return BST_insert_aux(node->right, k);
  }
  return NULL;
}


BinNode * BST_insert(BST * b, int k) {
  if(b->root == NULL){
    b->root = BST_node_new(k);
    return b->root;
  }
  return BST_insert_aux(b->root, k);
}


BinNode* BST_find_aux(BinNode* node, int k){
  if(k < node->key){
    if(node->left == NULL)
      return NULL;
    else
      return BST_find_aux(node->left, k);
  }else if(k > node->key){
    if(node->right == NULL)
      return NULL;
    else
      return BST_find_aux(node->right, k);
  }
  return node;
}


BinNode * BST_find(BST * b, int k) {
  if(b->root == NULL)
    return NULL;
  return BST_find_aux(b->root, k);
}

static void BST_delete_aux(BinNode * t) {
	if (t == NULL)
		return;

        BST_delete_aux(t->left);
        BST_delete_aux(t->right);
	free(t);
}

void BST_delete(BST * b) {
	if (b == NULL)
		return;

        BST_delete_aux(b->root);
        free(b);
}

void BST_print_aux(BinNode * t, int level) {
	if (t == NULL)
		return;

    int i;
    for (i = 0; i < level - 1; i++) {
    	printf("   ");
    }

    if (level > 0) {
    	printf(" |--");
    }

    printf("%d\n", t->key);

    BST_print_aux(t->left, level + 1);
    BST_print_aux(t->right, level + 1);
}

void BST_print(BST * b){
    return BST_print_aux(b->root, 0);
}


int maxOnLevel_aux(BinNode* node, int current, int level){
  if(node == NULL)
    return -1;

  int left = -1, right = -1;
  
  if(current < level){
    left = maxOnLevel_aux(node->left, current + 1, level);
    right = maxOnLevel_aux(node->right, current + 1, level);

    return (left > right) ? left : right;
  }
  
  return node->key;
}



int maxOnLevel (BST * b, int level){
  if(b->root == NULL)
    return -1;

  if(level == 1)
    return b->root->key;

  return maxOnLevel_aux(b->root, 1, level);
}

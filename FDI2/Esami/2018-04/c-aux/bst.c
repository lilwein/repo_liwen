#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

#define LEFT  0
#define RIGHT 1

BinNode * newBinNode(int k) {
    /*OK*/
    BinNode * b = malloc(sizeof(BinNode));
	b->key = k;
	b->left = NULL;
	b->right = NULL;

	return b;
}

BST * newBST() {
    /*OK*/
    BST * b = malloc(sizeof(BST));
    b->root = NULL;

	return b;
}

static void print(BinNode *t, int level, char pos) {
    if(t == NULL) return;
    for (int i = 0; i < level - 1; i++) printf("   ");
    if (level > 0) printf(" %c:--", pos);

    printf("%d\n", t->key);
    print(t->left, level + 1, 'l');
    print(t->right, level + 1, 'r');
}

void BST_print(BST *t){
    if(t != NULL && t->root != NULL) print(t->root, 0, ' ');
}

BinNode* BST_insert_aux(BinNode* node, int k){
  if(node == NULL){
    node = newBinNode(k);
    return node;
  }

  if(node->key > k){
    if(node->left == NULL){
      node->left = newBinNode(k);
      return node->left;
    }else 
      return BST_insert_aux(node->left, k);
  }else if(node->key < k){
    if(node->right == NULL){
      node->right = newBinNode(k);
      return node->right;
    }else
      return BST_insert_aux(node->right, k);
  }
  printf("Key is contained in the tree yet.\n");
  return NULL;
}

BinNode *BST_insert(BST *t, int k) {
  if(t->root == NULL){
    t->root = newBinNode(k);
    return t->root;
  }

  return BST_insert_aux(t->root, k);
}


int isBST_aux(BinNode* curr){
  if(curr == NULL)
    return 0;
  
  //I'm a leaf
  if(curr->left == NULL && curr->right == NULL)
    return curr->key;
  
  int left = isBST_aux(curr->left);
  int right = isBST_aux(curr->right);

  if(left < 0 || right < 0)
    return -1;

  if(curr->key > left  && curr->key < right)
    return right;
  
  return -1;
}


int isBST(BST *t) {
  if(t == NULL)
    return 0;

  int res = isBST_aux(t->root);

  return (res < 0) ? 0 : 1;
}

int isBalanced_aux(BinNode* curr){
  if(curr == NULL)
    return 0;

  int left = isBalanced_aux(curr->left);
  int right = isBalanced_aux(curr->right);

  if(left < 0 || right < 0)
    return -1;

  int res = (right - left < 0 ) ? left - right : right - left;

  if(res <= 1)
    return ((left > right) ? left : right) + 1;
  return -1;
}

int isBalanced(BST *t) {
  if(t == NULL)
    return 0;

  int res = isBalanced_aux(t->root);
  return (res < 0) ? 0 : 1;
}



#ifndef _BSTC
#define _BSTC

#include "bst.h"
#include "bstnode.h"
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define PI 3.14159265


bst *newBST() {
    bst *tmp = malloc(sizeof(bst));
    tmp->root = NULL;
    tmp->size = 0;
    return tmp;
}

static double raggio(double x, double y) {
    return sqrt(x*x+y*y);
}

static double raggiop(bstnode *u) {
    return raggio(u->x_coord, u->y_coord);
}

static double fase(double x, double y) {
    if(x == 0)
        if(y == 0) return 0;
        else if(y > 0) return PI/2;
        else return -PI/2;
    double a = atan(y/x);
    if(x > 0) return a;
    else if(y >= 0) return a + PI;
    else return a - PI;
}

static double fasep(bstnode *p) {
    return fase(p->x_coord, p->y_coord);
}

static void _print(bstnode *t, int ind, char *msg) {
    for(int i = 0; i < ind; i++) printf("--");
    if(t == NULL) { printf("# (%s)\n", msg); return; }
    printf("[NODE (x=%g, y=%g) (raggio=%g, fase=%g)] (%s)\n", t->x_coord, t->y_coord, raggiop(t), fasep(t), msg);
    _print(t->left, ind+1, "figlio SX");
    _print(t->right, ind+1, "figlio DX");
    return;
}

void print(bst *t) {
    printf("Stampa albero in pre-ordine. N.ro nodi: %d\n", t->size);
    _print(t->root, 0, "root");
    printf("Fine stampa albero in pre-ordine\n");
}

bstnode* insert_aux(bstnode* node, double x, double y){

  if((raggio(x, y) < raggiop(node)) || (raggio(x, y) == raggiop(node) && fase(x, y) < fasep(node))){
    if(node->left == NULL){
      node->left = newBSTNode(x, y);
      return node->left;
    }else
      return insert_aux(node->left, x, y);

  }else if((raggio(x, y) > raggiop(node)) || (raggio(x, y) == raggiop(node) && fase(x, y) > fasep(node))){
    if(node->right == NULL){
      node->right = newBSTNode(x, y);
      return node->right;
    }else
      return insert_aux(node->right, x, y);
  }
  return NULL;
}

bstnode *insert(bst *t, double x, double y) {
  if(t->root == NULL){
    t->root = newBSTNode(x, y);
    (t->size)++;
    return t->root;
  }
  bstnode* res = insert_aux(t->root, x, y);

  if(res != NULL)
    (t->size)++;
  return res;
}

void corona_aux(bstnode* node, double r1, double r2, int* counter){
  if(node == NULL)
    return;

  double radius = raggiop(node);
  if(radius >= r1 && radius <= r2)
    (*counter)++;

  corona_aux(node->left, r1, r2, counter);
  corona_aux(node->right, r1, r2, counter);
}


int corona(bst *t, double r1, double r2) {
  if(t->root == NULL)
    return 0;

  int counter = 0;
  corona_aux(t->root, r1, r2, &counter);
  return counter;
}


double getMaxRadius(bstnode* node, bstnode** pred, double* max){
  if(node == NULL)
    return *max;

  double right = getMaxRadius(node->right, pred, max);

  if(right > *max){
    *max = right;
    *pred = node;
  }
  return raggiop(node);
}

double maxCorona(bst *t) {
  if(t->root == NULL)
    return 0;

  double r2 = 0;
  bstnode* node = NULL;
  
  getMaxRadius(t->root, &node, &r2);

  double r1 = raggiop(node);
  
  printf("r1 : %lf, r2 : %lf\n", r1, r2);
  double radius = raggio(r1, r2);
  return 4*PI*radius;
}

#endif
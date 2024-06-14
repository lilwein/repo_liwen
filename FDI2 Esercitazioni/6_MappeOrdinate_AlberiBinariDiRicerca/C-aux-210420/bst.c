#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "bst.h"

// STRUCT
typedef struct bst_node {
	int key;
	void* value;
	struct bst_node*  left;
	struct bst_node* right;
} bst_node;

struct bst {
	bst_node* root;
};


// AUX
// static int _is_leaf(bst_node* b){
// 	if(b==NULL) return 0;
// 	if(b->left == NULL && b->right == NULL) return 1;
// 	return 0;
// }

static int num_child(bst_node* b){
	if(b->left && b->right) return 2;
	if(b->left || b->right) return 1;
	else return 0;
}


// COSTRUTTORE
static bst_node* _node_new(int k, void* v){
	bst_node* node= (bst_node*) malloc(sizeof(bst_node));
	node->key = k;
	node->value = v;
	node->left = NULL;
	node->right = NULL;

	return node;
}

bst * bst_new(int k, void * v) {
	bst* new = (bst*) malloc(sizeof(bst));
	new->root = _node_new(k,v);

	return new;
}


// RICERCA
static bst_node* _node_get(bst_node* b, int k) {
	if(b==NULL) return b;

	assert(b->key);
	if(k == b->key) return b;
	else if(k < b->key) return _node_get(b->left, k);
	else return _node_get(b->right, k);
}

void * bst_find(bst * b, int k) {
	bst_node* found = _node_get(b->root, k);
	if(found) return found->value;
	return NULL;
}


// INSERIMENTO
static void _bst_insert_aux(bst_node* b, int k, void* v) {
	if(k == b->key) b->value = v;

	else if(k < b->key){
		if(b->left) _bst_insert_aux(b->left, k, v);
		else b->left = _node_new(k, v);
	}
	else {
		if(b->right) _bst_insert_aux(b->right, k, v);
		else b->right = _node_new(k, v);
	}
}

void bst_insert(bst * b, int k, void * v) {
	if(b == NULL) b = bst_new(k,v);
	else if (b->root == NULL) b->root = _node_new(k,v);
	else _bst_insert_aux(b->root, k, v);
}


// RICERCA MINIMO
static bst_node* _bst_find_min_aux(bst_node* b){
	if(b->left == NULL) return b;
	return _bst_find_min_aux(b->left);
}

int bst_find_min(bst * b) {
	if(b == NULL || b->root == NULL) return -1;
	return _bst_find_min_aux(b->root)->key;
}


// RIMUOVI MINIMO
static bst_node* _bst_remove_min_aux(bst_node* b){
	if(b->left == NULL) {
		bst_node* right = b->right;
		free(b);
		return right;
	}
	b->left = _bst_remove_min_aux(b->left);
	return b;
}

void bst_remove_min(bst * b) {
	if(b == NULL || b->root == NULL) return;
	b->root = _bst_remove_min_aux(b->root);
}


// RIMOZIONE
static bst_node* _bst_remove_aux(bst_node* b, int k){

	if(b == NULL) return NULL;
	else if(k < b->key){
		b->left = _bst_remove_aux(b->left, k);
	}
	else if(k > b->key){
		b->right = _bst_remove_aux(b->right, k);
	}
	else if(k == b->key){
		int children = num_child(b);
		if(children==2) {
			bst_node* temp = b;

			bst_node* successor = _bst_find_min_aux(b->right);
			// void* value = _node_get(b->right, successor)->value;

			bst_node* new = _node_new(successor->key, successor->value);
			new->left = temp->left;
			new->right = _bst_remove_min_aux(b->right);

			free(temp);
			b = new;
		}
		else if(children==1){
			bst_node * ret;
			if(b->left == NULL) ret = b->right;
			else if(b->right == NULL) ret = b->left;
			free(b);
			return ret;
		}
	}
	return b;

}

void bst_remove(bst * b, int k) {
	if(b == NULL || b->root == NULL) return;
	b->root = _bst_remove_aux(b->root, k);
}


// ELIMINAZIONE BST
static void _bst_delete_aux(bst_node* b){
	if(b==NULL) return;
	_bst_delete_aux(b->left);
	_bst_delete_aux(b->right);
	free(b);
}

void bst_delete(bst * b) {
	_bst_delete_aux(b->root);
}


// STAMPA
static void bst_print_aux(bst_node * t, int level) {
	if (t == NULL) return;

    for (int i = 0; i < level - 1; i++) printf("   ");
    if (level > 0) printf(" |--");

    printf("%d\n", t->key);

    bst_print_aux(t->left, level + 1);
    bst_print_aux(t->right, level + 1);
}

void bst_print(bst * b){
	bst * t = b;
	bst_print_aux(t->root, 0);
}


// PREDECESSORE
static bst_node* _bst_predecessor_aux(bst_node* b, int k){
	if(b==NULL) return NULL;

	if(k <= b->key){
		return _bst_predecessor_aux(b->left, k);
	}
	else{
		bst_node* node = _bst_find_min_aux(b->right);
		if(k > node->key) return node;
		else return b;
	}
}

int bst_predecessor(bst * b, int k) {
	if(b == NULL || b->root == NULL) return -1;
    return _bst_predecessor_aux(b->root, k)->key;
}
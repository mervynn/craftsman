#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define RED 1
#define BLACK 0
struct node{
	int key;
	_Bool color;
	struct node *left, *right, *parent;
} *root, *nil;
struct node *search(struct node*, int);
struct node *grandParent(struct node *p){
	return p->parent->parent;
}

struct node *uncle(struct node *p){
	struct node *g = grandParent(p);
	if(p->parent ==  g->left) return g->right;
	return g->left;
}

_Bool isNil(struct node* p){
	return p == nil;
}

struct node *sbling(struct node* p){
	if(p == p->parent->left) return p->parent->right;
	return p->parent->left;
}

void rotateLeft(struct node *p){
	p->right->parent = p->parent;
	if(isNil(p->parent)) goto pos;
	if(p == p->parent->left) p->parent->left = p->right;
	else p->parent->right = p->right;
	pos:p->parent = p->right;
	p->right = p->right->left;
	p->parent->left = p;
	if(!isNil(p->right)) p->right->parent = p;
	if(root == p) root = p->parent;
}

void rotateRight(struct node *p){
	p->left->parent = p->parent;
	if(isNil(p->parent)) goto pos;
	if(p == p->parent->left) p->parent->left = p->left;
	else p->parent->right = p->left;
	pos:p->parent = p->left;
	p->left = p->left->right;
	p->parent->right = p;
	if(!isNil(p->left)) p->left->parent = p;
	if(root == p) root = p->parent;
}

void insertCase5(struct node* p){
	struct node* g = grandParent(p);
	g->color = RED;
	p->parent->color = BLACK;
	if(p == p->parent->left) rotateRight(g);
	else rotateLeft(g);
}

void insertCase4(struct node* p){
	struct node* g = grandParent(p);
	if(p->parent == g->left && p == p->parent->right){
		rotateLeft(p->parent);
		p = p->left;
	}
	if(p->parent == g->right && p == p->parent->left){
		rotateRight(p->parent);
		p = p->right;
	}
	insertCase5(p);
}

extern void insertCase1(struct node*);

void insertCase3(struct node* p){
	struct node* g = grandParent(p);
	struct node* u = uncle(p);
	if(u->color == RED){
		u->color = BLACK;
		p->parent->color = BLACK;
		g->color = RED;
		insertCase1(g);
	}else insertCase4(p);
}

void insertCase2(struct node* p){
	if(p->parent->color == RED) insertCase3(p);
}

void insertCase1(struct node* p){
	if(isNil(p->parent)) p->color = BLACK;
	else insertCase2(p);
}

void deleteCase6(struct node* p){
	struct node* s = sbling(s);
	s->color = p->parent->color;
	p->parent->color = BLACK;
	if(p == p->parent->left){
		s->right->color = BLACK;
		rotateLeft(p->parent);
	}else{
		s->left->color = BLACK;
		rotateRight(p->parent);
	}
}

void deleteCase5(struct node* p){
	struct node* s = sbling(p);
	if(p == p->parent->left && s->left->color == RED){
		s->color = RED;
		s->left->color = BLACK;
		rotateRight(s);
	}else if(p == p->parent->right && s->right->color ==RED){
		s->color = RED;
		s->right->color = BLACK;
		rotateLeft(s);
	}
	deleteCase6(p);
}

void deleteCase4(struct node* p){
	struct node* s = sbling(p);
	if(p->parent->color == RED &&
	   s->color == BLACK &&
	   s->left->color == BLACK &&
	   s->right->color == BLACK){
		p->parent->color = BLACK;
		s->color = RED;
	}else deleteCase5(p);
}

extern void deleteCase1(struct node*);

void deleteCase3(struct node* p){
	struct node* s = sbling(p);
	if(p->parent->color == BLACK &&
	   s->color == BLACK &&
	   s->left->color == BLACK &&
	   s->right->color ==BLACK){
		s->color = RED;
		deleteCase1(p->parent);
	}else deleteCase4(p);
}

void deleteCase2(struct node* p){
	struct node* s = sbling(p);
	if(s->color == RED){
		s->color = BLACK;
		p->parent->color = RED;
		if(p == p->parent->left) rotateLeft(p->parent);
		else rotateRight(p->parent);
	}
	deleteCase3(p);
}

void deleteCase1(struct node* p){
	if(!isNil(p->parent)) return deleteCase2(p);
}

void replaceNode(struct node* p1, struct node* p2){
	if(isNil(p1->parent)) {
		root = p2;
		goto pos;
	}
	if(p1->parent->left == p1) p1->parent->left = p2;
	else p1->parent->right = p2;
	pos: if(isNil(p2)) return;
	p2->parent = p1->parent;
}

void deleteOneNode(struct node* p){
	struct node* child = isNil(p->left) ? p->right : p->left;
	if(p->color == BLACK){
		if(child->color == RED) child->color = BLACK;
		else deleteCase1(p);
	}
	replaceNode(p, child);
	free(p);
}

struct node* minimumNode(struct node* p){
	return !isNil(p->left) ? minimumNode(p->left) : p;
}

struct node* newNode(int key){
	struct node* p = (struct node*)malloc(sizeof(struct node));
	p->key = key;
	p->color = RED;
	p->left = p->right = p->parent = nil;
	return p;
}

struct node* newNil(){
	struct node* p = (struct node*)malloc(sizeof(struct node));
	p->key = -1;
	p->color = BLACK;
	p->left = p->right = p->parent = NULL;
	return p;
}

void preOrder(struct node* p){
	if(!isNil(p)){
		printf("%d\n", p->key);
		preOrder(p->left);
		preOrder(p->right);
	}
}

void inOrder(struct node* p){
	if(!isNil(p)){
		inOrder(p->left);
		printf("%d\n", p->key);
		inOrder(p->right);
	}
}

void insert(struct node* p, int key){
	struct node* n = newNode(key);
	if(isNil(p)) root = n;
	else{
		struct node *tmp = p;
		struct node *cur = nil;
		while(!isNil(cur = key > tmp->key ? tmp->right : tmp->left)) tmp = cur;
		if(key > tmp->key) tmp->right = n;
		else tmp->left = n;
		n->parent = tmp;
	}
	insertCase1(n);
}

void delete(struct node* p, int key){
	if(!isNil(p)){
		struct node* tmp = p;
		while(!isNil(tmp = key > tmp->key ? tmp->right : tmp->left))
			if(tmp->key == key) break;
		if(!isNil(tmp) && tmp->key == key){
			if(isNil(tmp->left) || isNil(tmp->right)){
				deleteOneNode(tmp);
			}else{
				struct node *min = minimumNode(tmp->right);
				tmp->key = min->key;
				deleteOneNode(min);
			}
		}
	}
}

struct node* search(struct node* p, int key){
	if(isNil(p)) return nil;
	if(p->key == key) return p;
	if(key > p->key) return search(p->right, key);
	else return search(p->left, key);
}

int main(){
	root = nil = newNil();
	clock_t t0 = clock();
	for(int i = 0; i < 10000000; i++) insert(root, i);
	clock_t t1 = clock();
	//preOrder(root);
	delete(root, 1200001);
	clock_t t2 = clock();
	//preOrder(root);
	// CLOCKS_PER_SEC
	printf("Insertion costs:%lu, removal costs:%lu\n", t1 - t0, t2 - t1);
}

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
typedef int elemType;
struct node{
	elemType key;
	int height;
	struct node *left, *right;
};
struct test{};
struct test1{
	int a;
};
struct node* newNode(elemType key){
	struct node* node = (struct node*)malloc(sizeof(struct node));
	node->key = key;
	node->height = 1;
	node->left = NULL;
	node->right = NULL;
	return node;
}

int height(struct node* node){
	return node ? node->height : 0;
}

int max(int a, int b){
	return a > b ? a : b;
}

int getBalanceFactor(struct node* node){
	return node ? height(node->left) - height(node->right) : 0;
}

elemType minimum(struct node* node){
	return node->left ? minimum(node->left) : node->key;
}

struct node* leftRotate(struct node* node){
	struct node* temp = node->right;
	struct node* a = temp->left;
	temp->left = node;
	node->right = a;
	node->height = max(height(node->left), height(node->right)) + 1;
	temp->height = max(height(temp->left), height(temp->right)) + 1;
	return temp;
}

struct node* rightRotate(struct node* node){
	struct node* temp = node->left;
	struct node* a = temp->right;
	temp->right = node;
	node->left = a;
	node->height = max(height(node->left), height(node->right)) + 1;
	temp->height = max(height(temp->left), height(temp->right)) + 1;
	return temp;
}
struct node* insert(struct node* node, elemType key){
	if(node == NULL) return newNode(key);
	if(key < node->key) node->left = insert(node->left, key);
	else node->right = insert(node->right, key);
	node->height = max(height(node->left), height(node->right)) + 1;
	int bf = getBalanceFactor(node);
	if(bf < - 1 && node->right->key < key) return leftRotate(node);
	if(bf < -1 && node->right->key > key){
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}
	if(bf > 1 && node->left->key > key) return rightRotate(node);
	if(bf > 1 && node->left->key < key){
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}
	return node;
}

struct node* deleteNode(struct node* node, elemType key){
	if(!node) return node;
	if(key < node->key) node->left = deleteNode(node->left, key);
	else if(key > node->key) node->right = deleteNode(node->right, key);
	else{
		if(!node->left || !node->right){
			struct node* temp = node->left ? node->left : node->right;
			free(node);
			return temp;
		}else{
			elemType min = minimum(node->right);
			node->key = min;
			node->right = deleteNode(node->right, min);
		}
	}
	node->height = max(height(node->left), height(node->right)) + 1;
	int bf = getBalanceFactor(node);
	if(bf < -1 && getBalanceFactor(node->right) <= 0) return leftRotate(node);
	else if(bf < -1 && getBalanceFactor(node->right) > 0){
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}else if(bf > 1 && getBalanceFactor(node->left) >= 0) return rightRotate(node);
	else if(bf > 1 && getBalanceFactor(node->left) < 0){
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}
	return node;
}
void preOrder(struct node *node){
    if(node){
		printf("key:%d, height:%d\n", node->key, node->height);
		preOrder(node->left);
		preOrder(node->right);
	}
}
void inOrder(struct node* node){
	if(node){
		inOrder(node->left);
		printf("key:%d, height:%d\n", node->key, node->height);
		inOrder(node->right);
	}
}
int main(){
	struct node *root = NULL;
	clock_t t0 = clock();
	for(int i = 0; i < 10000000; i++){
		root = insert(root, i);
	}
	clock_t t1 = clock();
	//preOrder(root);
	//inOrder(root);
	root = deleteNode(root, 1200001);
	//root = deleteNode(root, 9);
	//root = deleteNode(root, 10);
	//inOrder(root);
	clock_t t2 = clock();
	printf("Insertion costs:%lu, removal costs:%lu.\n", t1 - t0, t2 - t1);
}

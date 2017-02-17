#include <iostream>
using namespace std;
class Bst{
	public :
		class node{
			public :
				node(){}
				node(int val) : key(val), height(0), left(NULL), right(NULL){}
				int key;
				node *left, *right;
				int height;		
				~node(){
					key = 0;
					height = 0;
				}
		};
		
	public :
		node *root;
		void insert(int key);
		void deleteKey(int key);
		node *insert(node *root, int key);
		node *deleteNode(node *root, int key);
		void inOrder(node *root);
		void traversal();
		node *minimumNode(node *root);
		int height(node *root);
};

int Bst::height(node* root){
	return !root ? 0 : root->height;
}
Bst::node* Bst::insert(node *root, int key){
	if(!root) return new node(key);
	if(key < root->key)
		root->left = insert(root->left, key);
	else
		root->right = insert(root->right, key);
	root->height = max(height(root->left), height(root->right)) + 1;
	return root;
}

Bst::node* Bst::deleteNode(node *root, int key){
	if(!root) return root;
	if(key < root->key)
		root->left = deleteNode(root->left, key);
	else if(key > root->key)
		root->right = deleteNode(root->right, key);
	else{		
		node* temp;
		if(!root->left || !root->right){
			temp = root->left ? root->left : root->right;
			delete(root);
			return temp;
		}else{
			temp = minimumNode(root->right);
			root->key = temp->key;
			root->right = deleteNode(root->right, key);
		}
	}
	root->height = max(height(root->left), height(root->right)) + 1;
	return root;
}

void Bst::insert(int key){
	root = insert(root, key);
}

void Bst::deleteKey(int key){
	root = deleteNode(root, key);
}

void Bst::inOrder(node *root){
	if(root){
		inOrder(root->left);
		cout<<root->key<<endl;
		inOrder(root->right);
	}
}

void Bst::traversal(){
	inOrder(root);
}

Bst::node* Bst::minimumNode(node* root){
	return !root->left ? root : minimumNode(root->left);
}

int main(){
	Bst *bst = new Bst();
   	cout<<"new"<<endl;
	bst->insert(5);
	cout<<"insert"<<endl;
	bst->insert(4);
	bst->insert(7);
	bst->insert(2);
	bst->insert(1);
	bst->insert(8);
	bst->traversal();
	bst->deleteKey(7);
	bst->traversal();
}


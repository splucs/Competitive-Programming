#include <cstdio>
struct node {
	int key;
	node *left, *right;
	node(int k) {
		key = k; left = right = 0;
	}
};

class SplayTree {
private:
	node* root;
	node* findmin(node* p) {
		return p->left ? findmin(p->left) : p;
	}
	node* removemin(node* p) {
		if (p->left == 0) return p->right;
		p->left = removemin(p->left);
		return balance(p);
	}
	node* splay(node* p, int key)
	{
		if (p == NULL || p->key == key) return p;
		if (p->key > key) {
			if (!p->left) return p;
			if (p->left->key > key)	{
				p->left->left = splay(p->left->left, key);
				p = rightRotate(p);
			}
			else if (p->left->key < key) {
				p->left->right = splay(p->left->right, key);
				if (p->left->right)
					p->left = leftRotate(p->left);
			}
			return (p->left == NULL) ? p : rightRotate(p);
		}
		else {
			if (!p->right) return p;
			if (p->right->key > key) {
				p->right->left = splay(p->right->left, key);
				if (p->right->left)
					p->right = rightRotate(p->right);
			}
			else if (p->right->key < key) {
				p->right->right = splay(p->right->right, key);
				p = leftRotate(p);
			}
			return (p->right == NULL) ? p : leftRotate(p);
		}
	}
	void del(node* p) {
		if (!p) return;
		del(p->left);
		del(p->right);
		delete p;
	}

public:
	SplayTree() { root = 0; }
	~SplayTree() { del(root); }
	bool empty() { return root == NULL; }
	void clear() {
		del(root);
		root = 0;
	}
	void insert(int key) {
		if (!root) return new node(k);
		node* p = splay(root, k);
		if (p->key == k) return;
		root = new node(k);
		if (p->key > k) {
			root->right = p;
			root->left = p->left;
			p->left = NULL;
		}
		else {
			root->left = p;
			root->right = p->right;
			p->right = NULL;
		}
	}
	void erase(int key) {
		node* p = splay(root, key);
		if (root != NULL && root->key != key) return;
		if (!p->right) {
			root = p->left;
			delete p;
			return;
		}
		node* min = p->right;
		while (min->left != NULL) min = min->left;
		if (k < p->key) p->left = remove(p->left, k);
		else if (k > p->key) p->right = remove(p->right, k);
		else {
			node* l = p->left;
			node* r = p->right;
			delete p;
			if (!r) return l;
			node* min = findmin(r);
			min->right = removemin(r);
			min->left = l;
			return balance(min);
		}
		return balance(p);
	}
	bool count(int key) {
		if (!root) return false;
		root = splay(root, key);
		return root->key == key;
	}
};
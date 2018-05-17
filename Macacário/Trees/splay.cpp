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
	node* rotateright(node* p) {
		node* q = p->left;
		p->left = q->right;
		q->right = p;
		return q;
	}
	node* rotateleft(node* q) {
		node* p = q->right;
		q->right = p->left;
		p->left = q;
		return p;
	}
	node* splay(node* p, int key) {
		if (p == NULL || p->key == key) return p;
		if (p->key > key) {
			if (!p->left) return p;
			if (p->left->key > key)	{
				p->left->left = splay(p->left->left, key);
				p = rotateright(p);
			}
			else if (p->left->key < key) {
				p->left->right = splay(p->left->right, key);
				if (p->left->right)
					p->left = rotateleft(p->left);
			}
			return (p->left == NULL) ? p : rotateright(p);
		}
		else {
			if (!p->right) return p;
			if (p->right->key > key) {
				p->right->left = splay(p->right->left, key);
				if (p->right->left)
					p->right = rotateright(p->right);
			}
			else if (p->right->key < key) {
				p->right->right = splay(p->right->right, key);
				p = rotateleft(p);
			}
			return (p->right == NULL) ? p : rotateleft(p);
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
		if (!root) {
			root = new node(key);
			return;
		}
		node* p = splay(root, key);
		if (p->key == key) return;
		root = new node(key);
		if (p->key > key) {
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
		if (p != NULL && p->key != key) return;
		if (!p->right) {
			root = p->left;
			delete p;
			return;
		}
		node* q = splay(p->right, key);
		q->left = p->left;
		root = q;
		delete p;
	}
	bool count(int key) {
		if (!root) return false;
		root = splay(root, key);
		return root->key == key;
	}
};

/*
 * TEST MATRIX
 */

#include <set>
#include <cstdlib>
using namespace std;

bool test()
{
	SplayTree splay;
	set<int> s;
	int N = 1000000;
	for(int t=1; t<=N; t++) {
		int x = rand()%100;
		if (s.count(x) != splay.count(x)) {
			printf("failed on test %d\n", t);
			return false;
		}
		if (s.count(x)) {
			s.erase(x);
			splay.erase(x);
		}
		else{
			s.insert(x);
			splay.insert(x);
		}
	}
	return true;
}

int main()
{
	if (test()) {
		printf("all tests passed\n");
	}
	return 0;
}
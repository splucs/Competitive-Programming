#include <cstdio>

/*
 * Splay Tree
 */

struct node {
	int key;
	node *ls, *rs;
	node(int k) : key(k), ls(NULL), rs(NULL) {}
};

class SplayTree {
private:
	node* root;
	node* rotateright(node* p) {
		node* q = p->ls;
		p->ls = q->rs;
		q->rs = p;
		return q;
	}
	node* rotateleft(node* q) {
		node* p = q->rs;
		q->rs = p->ls;
		p->ls = q;
		return p;
	}
	node* splay(node* p, int key) {
		if (!p || p->key == key) return p;
		if (p->key > key) {
			if (!p->ls) return p;
			if (p->ls->key > key)	{
				p->ls->ls = splay(p->ls->ls, key);
				p = rotateright(p);
			}
			else if (p->ls->key < key) {
				p->ls->rs = splay(p->ls->rs, key);
				if (p->ls->rs)
					p->ls = rotateleft(p->ls);
			}
			return (!p->ls) ? p : rotateright(p);
		}
		else {
			if (!p->rs) return p;
			if (p->rs->key > key) {
				p->rs->ls = splay(p->rs->ls, key);
				if (p->rs->ls)
					p->rs = rotateright(p->rs);
			}
			else if (p->rs->key < key) {
				p->rs->rs = splay(p->rs->rs, key);
				p = rotateleft(p);
			}
			return (!p->rs) ? p : rotateleft(p);
		}
	}
	void del(node* &p) {
		if (!p) return;
		del(p->ls); del(p->rs);
		delete p;
		p = NULL;
	}

public:
	SplayTree() : root(NULL) { }
	~SplayTree() { del(root); }
	bool empty() { return root == NULL; }
	void clear() { del(root); }
	void insert(int key) {
		if (!root) {
			root = new node(key);
			return;
		}
		node* p = splay(root, key);
		if (p->key == key) return;
		root = new node(key);
		if (p->key > key) {
			root->rs = p;
			root->ls = p->ls;
			p->ls = NULL;
		}
		else {
			root->ls = p;
			root->rs = p->rs;
			p->rs = NULL;
		}
	}
	void erase(int key) {
		node* p = splay(root, key);
		if (!p || p->key != key) return;
		if (!p->rs) {
			root = p->ls;
			delete p;
			return;
		}
		node* q = splay(p->rs, key);
		q->ls = p->ls;
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
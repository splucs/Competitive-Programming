#include <cstdio>
#include <vector>
#include <algorithm>
#include <ctime>
#define INF 0x3f3f3f3f
using namespace std;

/*
 * Randomized BST, works as Persistent Implicit Treap
 * split separates in trees of size k and n-k
 */

struct node {
	int v, sum, size;
	node *l, *r;
	node(int _v, vector<node*> &nodes) :
		v(_v), sum(_v), size(1), l(NULL), r(NULL) {
		nodes.push_back(this);
	}	
};

class RBST {
private:
	vector<node*> root, nodes;
	int size(node* t) { return t ? t->size : 0; }
	int sum(node* t) { return t ? t->sum : 0; }
	node* copy(node* t) {
		node* cpy = new node(t->v, nodes);
		cpy->l = t->l; cpy->r = t->r;
		return refresh(cpy);
	}
	node* refresh(node* t) {
		if (t == NULL) return t;
		t->size = 1 + size(t->l) + size(t->r);
		t->sum = t->v + sum(t->l) + sum(t->r);
		return t;
	}
	void split(node* t, int k, node* &a, node* &b) {
		node *aux;
		if (!t) { a = b = NULL; return; }
		t = copy(t);
		if (size(t->l) < k) {
			split(t->r, k-size(t->l)-1, aux, b);
			t->r = aux;
			a = refresh(t);
		}
		else {
			split(t->l, k, a, aux);
			t->l = aux;
			b = refresh(t);
		}
	}
	node* merge(node* a, node* b) {
		node *aux, *cpy;
		if (!a || !b) return a ? a : b;
		int m = size(a), n = size(b);
		if (rand()%(n+m) < m) {
			a = copy(a);
			a->r = merge(a->r, b);
			return refresh(a);
		}
		else {
			b = copy(b);
			b->l = merge(a, b->l);
			return refresh(b);
		}
	}
	node* at(node* t, int i) {
		if (!t) return t;
		if (i < size(t->l)) return at(t->l, i);
		else if (i == size(t->l)) return t;
		else return at(t->r, i-size(t->l)-1);
	}
public:
	RBST() { clear(); }
	~RBST() { clear(); }
	void clear() {
		for(int i = 0; i < (int)nodes.size(); i++)
			delete nodes[i];
		root.push_back(NULL);
	}
	int size(int ver) { return size(root[ver]); }
	int insert(int ver, int i, int v) {
		node *a, *b, *tree;
		split(root[ver], i, a, b);
		tree = merge(merge(a, new node(v, nodes)), b);
		root.push_back(tree);
		return root.size() - 1;
	}
	int erase(int ver, int i) {
		node *a, *b, *c, *d;
		split(root[ver], i, a, b);
		split(b, 1, c, d);
		root.push_back(merge(a, d));
		return root.size() - 1;
	}
	int at(int ver, int i) {
		node* ans = at(root[ver], i);
		return ans ? ans->v : -1;
	}
	int query(int ver, int l, int r) {
		if (l > r) swap(l, r);
		node *a, *b, *c, *d;
		split(root[ver], l, a, d);
		split(d, r-l+1, b, c);
		return sum(b);
	}
	int split(int ver, int k) {
		node *a, *b;
		split(root[ver], k, a, b);
		root.push_back(a);
		root.push_back(b);
		return root.size()-2;
	}
	int merge(int ver1, int ver2) {
		root.push_back(merge(root[ver1], root[ver2]));
		return root.size()-1;
	}
};

/*
 * TEST MATRIX
 */

#include <cassert>
#define MAXSIZE 100000
#define NTESTS 10000
#define NQUERY 10
#define RANGE 10000

void insert(vector<int> & arr, int i, int v) {
	arr.insert(arr.begin()+i, v);
}

int queryt(vector<int> & arr, int i, int j) {
	if (i > j) swap(i, j);
	int sum = 0;
	for(int it=i; it<=j && it<(int)arr.size(); it++) {
		sum += arr[it];
	}
	return sum;
}

void erase(vector<int> & arr, int i) {
	arr.erase(arr.begin()+i);
}

bool test() {
	srand(time(NULL));
	vector<int> control[NTESTS];
	RBST treap;
	for(int test = 1; test < NTESTS; test++) {
		int op = rand()%2;
		int ver = rand()%test;
		control[test] = control[ver];
		if (test%2 == 1) {
			int ver2 = rand()%test;
			if (control[ver].size() + control[ver2].size() > MAXSIZE) {
				test--;
				continue;
			}
			control[test].insert(control[test].end(), control[ver2].begin(), control[ver2].end());
			treap.merge(ver, ver2);
		}
		else if (op == 0 && !control[test].empty()) {
			int i = rand()%int(control[test].size());
			erase(control[test], i);
			treap.erase(ver, i);
		}
		else {
			int data = rand()%RANGE;
			int i = rand()%int(control[test].size()+1);
			insert(control[test], i, data);
			treap.insert(ver, i, data);
		}
	}
	for(int test = 0; test < NTESTS; test++) {
		if (control[test].size() != treap.size(test)) {
			printf("failed on test %d, size: %u-%d\n", test, control[test].size(), treap.size(test));
			return false;
		}
		for(int i = 0; i < (int)control[test].size(); i++) {
			if (control[test][i] != treap.at(test, i)) {
				printf("failed on test %d, id %d: %d-%d\n", test, i, control[test][i], treap.at(test, i));
				return false;
			}
		}
		for(int query = 0; query < NQUERY; query++) {
			if (control[test].empty()) continue;
			int i = rand()%int(control[test].size());
			int j = rand()%int(control[test].size());
			if (i > j) swap(i, j);
			int sum1 = queryt(control[test], i, j);
			int sum2 = treap.query(test, i, j);
			if (sum1 != sum2) {
				printf("failed on test %d, query %d: %d-%d\n", test, query, sum1, sum2);
				return false;
			}
		}
	}
	printf("all tests passed\n");
	return true;
}

int main() {
	test();
	return 0;
}
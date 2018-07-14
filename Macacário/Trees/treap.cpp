#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;

/*
 * Implicit Treap
 * 0-indexed, 10x slower than red-black tree
 * split separates between k-1 and k
 */

struct node {
	int x, y, size;
	node *l, *r;
	node(int _x) : x(_x), y(rand()), size(1), l(NULL), r(NULL) {}	
};

class Treap {
private:
	node* root;
	int size(node* t) { return t ? t->size : 0; }
	node* refresh(node* t) {
		if (!t) return t;
		t->size = 1 + size(t->l) + size(t->r);
		return t;
	}
	void split(node* &t, int k, node* &a, node* &b) {
		node* aux;
		if (!t) a = b = NULL;
		else if (t->x < k) {
			split(t->r, k, aux, b);
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
		if (!a || !b) return a ? a : b;
		if (a->y < b->y) {
			a->r = merge(a->r, b);
			return refresh(a);
		}
		else {
			b->l = merge(a, b->l);
			return refresh(b);
		}
	}
	node* count(node* t, int k) {
		if (!t) return NULL;
		else if (k < t->x) return count(t->l, k);
		else if (k == t->x) return t;
		else return count(t->r, k);
	}
	node* nth(node* t, int n) {
		if (!t) return NULL;
		if (n <= size(t->l)) return nth(t->l, n);
		else if (n == size(t->l) + 1) return t;
		else return nth(t->r, n-size(t->l)-1);
	}
	void del(node* &t) {
		if (!t) return;
		if (t->l) del(t->l);
		if (t->r) del(t->r);
		delete t;
		t = NULL;
	}
public:
	Treap() : root(NULL) { }
	~Treap() { clear(); }
	void clear() { del(root); }
	int size() { return size(root); }
	bool count(int k) { return count(root, k) != NULL; }
	bool insert(int k) {
		if (count(k)) return false;
		node *a, *b;
		split(root, k, a, b);
		root = merge(merge(a, new node(k)), b);
		return true;
	}
	bool erase(int k) {
		node * f = count(root, k);
		if (!f) return false;
		node *a, *b, *c, *d;
		split(root, k, a, b);
		split(b, k+1, c, d);
		root = merge(a, d);
		delete f;
		return true;
	}
	int nth(int n) {
		node* ans = nth(root, n);
		return ans ? ans->x : -1;
	}
};

/*
 * TEST MATRIX
 */

int vet[10000009];

void test() {
	set<int> s;
	Treap t;
	int N = 1000000;
	for(int i=0; i<N; i++) {
		int n = rand()%1000;
		if(!s.count(n)) {
			s.insert(n);
			t.insert(n);
			//if(!t.insert(n)) printf("error inserting %d in treap!\n", n);
			//printf("inserted %d\n", n);
		}
		else{
			s.erase(n);
			t.erase(n);
			//if(!t.erase(n)) printf("error erasing %d in treap!\n", n);
			//printf("erased %d\n", n);
		}
		n = rand()%1000;
		if (s.count(n) != t.count(n)) {
			printf("failed test %d, s.count(%d) = %d, t.count(%d) = %d\n", i, n, s.count(n), n, t.count(n));
		}
	}
	s.clear();
	t.clear();
	for(int i=0; i<N; i++) {
		vet[i] = i+1;
	}
	random_shuffle(vet, vet+N);
	for(int i=0; i<N; i++) {
		t.insert(vet[i]);
	}
	for(int i=1; i<=N; i++) {
		if (t.nth(i) != i) {
			printf("failed test %d\n", i);
		}
	}
	printf("all tests passed\n");
}

int main() {
	test();
	return 0;
}

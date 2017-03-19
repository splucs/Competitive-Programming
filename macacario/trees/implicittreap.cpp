#include <cstdio>
#include <algorithm>
#define INF (1 << 30)
using namespace std;

const int neutral = 0; //comp(x, neutral) = x
int comp(int a, int b) {
	return a + b;
}

struct node {
	int y, v, sum, size;
	bool swap;
	node *l, *r;
	node(int _v) {
		v = sum = _v;
		y = rand();
		size = 1;
		l = r = NULL;
		swap = false;
	}
};

class ImplicitTreap {
private:
	node* root;
	void refresh(node* t) {
		if (t == NULL) return;
		t->size = 1;
		t->sum = t->v;
		if (t->l != NULL) {
			t->size += t->l->size;
			t->sum = comp(t->sum, t->l->sum);
			t->l->swap ^= t->swap;
		}
		if (t->r != NULL) {
			t->size += t->r->size;
			t->sum = comp(t->sum, t->r->sum);
			t->r->swap ^= t->swap;
		}
		if (t->swap) {
			swap(t->l, t->r);
			t->swap = false;
		}
	}
	void split(node* &t, int k, node* &a, node* &b) {
		refresh(t);
		node * aux;
		if (t == NULL) {
			a = b = NULL;
			return;
		}
		else if (size(t->l) < k) {
			split(t->r, k - size(t->l) - 1, aux, b);
			t->r = aux;
			refresh(t);
			a = t;
		}
		else {
			split(t->l, k, a, aux);
			t->l = aux;
			refresh(t);
			b = t;
		}
	}
	node* merge(node* &a, node* &b) {
		refresh(a);
		refresh(b);
		node* aux;
		if (a == NULL) return b;
		else if (b == NULL) return a;
		if (a->y < b->y) {
			aux = merge(a->r, b);
			a->r = aux;
			refresh(a);
			return a;
		}
		else {
			aux = merge(a, b->l);
			b->l = aux;
			refresh(b);
			return b;
		}
	}
	node* at(node* t, int n) {
		if (t == NULL) return NULL;
		refresh(t);
		if (n < size(t->l)) return at(t->l, n);
		else if (n == size(t->l)) return t;
		else return at(t->r, n - size(t->l) - 1);
	}
	int size(node* t) {
		if (t == NULL) return 0;
		else return t->size;
	}
	void del(node* &t) {
		if (t == NULL) return;
		if (t->l != NULL) del(t->l);
		if (t->r != NULL) del(t->r);
		delete t;
		t = NULL;
	}
public:
	ImplicitTreap() { root = NULL; }
	~ImplicitTreap() { clear(); }
	void clear() { del(root); }
	int size() { return size(root); }
	bool insertAt(int n, int v) {
		node *a, *b, *c, *d;
		split(root, n, a, b);
		c = new node(v);
		d = merge(a, c);
		root = merge(d, b);
		return true;
	}
	bool erase(int n) {
		node *a, *b, *c, *d;
		split(root, n, a, b);
		split(b, 1, c, d);
		root = merge(a, d);
		if (c == NULL) return false;
		delete c;
		return true;
	}
	int at(int n) {
		node* ans = at(root, n);
		if (ans == NULL) return -1;
		else return ans->v;
	}
	int query(int l, int r) {
		if (l>r) swap(l, r);
		node *a, *b, *c, *d;
		split(root, l, a, d);
		split(d, r - l + 1, b, c);
		int ans = (b != NULL ? b->sum : neutral);
		d = merge(b, c);
		root = merge(a, d);
		return ans;
	}
	void reverse(int l, int r) {
		if (l>r) swap(l, r);
		node *a, *b, *c, *d;
		split(root, l, a, d);
		split(d, r - l + 1, b, c);
		if (b != NULL) b->swap ^= 1;
		d = merge(b, c);
		root = merge(a, d);
	}
};
#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;

/*
 * Implicit Treap
 * 0-indexed, 10x slower than segment tree
 * split separates in trees of size k and n-k
 */

struct node {
	int y, v, size;
	node *l, *r, *p;
	node(int _v) : v(_v), y(rand()),
		size(1), l(NULL), r(NULL), p(NULL) {}	
};

class ImplicitTreap {
private:
	node* root;
	int size(node* t) { return t ? t->size : 0; }
	node* refresh(node* t) {
		if (t == NULL) return t;
		t->size = 1 + size(t->l) + size(t->r);
        if (t->l) t->l->p = t;
        if (t->r) t->r->p = t;
        if (t->p) {
            if (t->p->l != t && t->p->r != t) t->p = NULL;
        }
		return t;
	}
	void split(node* &t, int k, node* &a, node* &b) {
		refresh(t);
		node * aux;
		if (!t) a = b = NULL;
		else if (size(t->l) < k) {
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
		refresh(a); refresh(b);
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
	node* at(node* t, int n) {
		if (!t) return t;
		refresh(t);
		if (n < size(t->l)) return at(t->l, n);
		else if (n == size(t->l)) return t;
		else return at(t->r, n-size(t->l)-1);
	}
	void del(node* &t) {
		if (!t) return;
		if (t->l) del(t->l);
		if (t->r) del(t->r);
		delete t;
		t = NULL;
	}
    void print(node *a) {
        if (!a) return;
        print(a->l);
        printf("%d, ", a->v);
        print(a->r);
    }
public:
	ImplicitTreap() : root(NULL) { }
	~ImplicitTreap() { clear(); }
	void clear() { del(root); }
	int size() { return size(root); }
	node *insertAt(int n, int v) {
		node *a, *b;
		split(root, n, a, b);
        node *aux = new node(v);
		root = merge(merge(a, aux), b);
        return aux;
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
		return ans ? ans->v : -1;
	}
	node *move(int i, int j) {
        int v = at(i);
        erase(i);
        return insertAt(j, v);
	}
    int posOf(node *a) {
        int n = size(a->l);
        while (a->p) {
            node *p = a->p;
            if (p->r == a) {
                n += 1 + size(p->l);
            }
            a = p;
        }
        return n;
    }
    void print() {
        print(root);
        printf("\n\n");
    }
};

int main() {
    int v;
    vector<node*> in;
    ImplicitTreap t;

    while(scanf(" %d", &v) != EOF) {
        node *a = t.insertAt(t.size(), v);
        in.push_back(a);
    }

    int n = t.size();
    int mod = n-1;
    for (int it = 0; it<n; it++) {
        node *a = in[it];
        int i = t.posOf(a);
        int v = a->v;
        int j = ((i+v+mod)%mod + mod)%mod;
        a = in[it] = t.move(i, j);
    }

    node *zero = NULL;
    for (node *a : in) {
        if (a->v == 0) {
            zero = a;
        }
    }

    int zeroPos = t.posOf(zero);
    int ans = 0;
    for (int d = 1000; d <= 3000; d += 1000) {
        ans += t.at((zeroPos+d)%n);
    }
    printf("%d\n", ans);
    return 0;
}
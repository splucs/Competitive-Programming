#include <cstdio>
#include <vector>
using namespace std;

/*
 * Recursive Purely Functional Deque
 */

struct cont {
	cont *ls, *rs;
	int x;
	cont(int _x, vector<cont*> &gc) :
		x(_x), ls(NULL), rs(NULL) {
		gc.push_back(this);
	}
	cont(cont* l, cont* r, vector<cont*> &gc) :
		x(0), ls(l), rs(r) {
		gc.push_back(this);
	}
};

struct node {
	cont* s[2];
	node* c;
	int sz;
	node(vector<node*> &gc) : c(NULL), sz(0) {
		s[0] = s[1] = NULL;
		gc.push_back(this);
	}
	node* copy(vector<node*> &gc) {
		node* cpy = new node(gc);
		cpy->sz = sz; cpy->c = c;
		cpy->s[0] = s[0]; cpy->s[1] = s[1];
		return cpy;
	}
};

class Deque {
private:
	vector<node*> root, nodes;
	vector<cont*> conts;
	void push(node* &u, int k, cont* x) {
		if (!u) { u = new node(nodes); }
		else u = u->copy(nodes);
		u->sz++;
		if (!u->s[k]) u->s[k] = x;
		else {
			cont* y = u->s[k];
			u->s[k] = NULL;
			if (k) swap(x, y);
			push(u->c, k, new cont(x, y, conts));
		}
	}
	cont* pop(node* &u, int k) {
		u = u->copy(nodes);
		u->sz--;
		cont *x = NULL, *y, *z;
		if (u->s[k]) {
			x = u->s[k];
			u->s[k] = NULL;	
		}
		else if (u->c && u->c->sz) {
			z = pop(u->c, k);
			x = z->ls; y = z->rs;
			if (k) swap(x, y);
			u->s[k] = y;
		}
		else if (u->s[k^1]) {
			x = u->s[k^1];
			u->s[k^1] = NULL;
		}
		else u->sz++;
		return x;
	}
	cont* at(const node* u, int i) {
		if (!u) return NULL;
		if (i == 0 && u->s[0]) return u->s[0];
		if (i == u->sz-1 && u->s[1]) return u->s[1];
		if (u->s[0]) i--;
		cont* x = at(u->c, i>>1);
		return i & 1 ? x->rs : x->ls;
	}
	node* merge(node* u, node* v, cont* c1, cont* c2) {
		node* w = new node(nodes);
		if (!u && !v) {
			w->s[0] = c1; w->s[1] = c2;
			return w;
		}
		if (!u) u = new node(nodes);
		if (!v) v = new node(nodes);
		cont *a[4];
		int k = 0;
		if (u->s[1]) a[k++] = u->s[1];
		if (c1) a[k++] = c1;
		if (c2) a[k++] = c2;
		if (v->s[0]) a[k++] = u->s[0];
		w->s[0] = u->s[0];
		w->s[1] = v->s[1];
		if ((k&1) && v->s[0]) pop(v, 0);
		if ((k&1) && v->sz == 0) w->s[1] = a[--k];
		if (k&1) a[k++] = pop(v, 0);
		c1 = k > 0 ? new cont(a[0], a[1], conts) : NULL;
		c2 = k > 2 ? new cont(a[2], a[3], conts) : NULL;
		w->c = merge(u->c, v->c, c1, c2);
		return w;
	}
public:
	Deque() { root.push_back(new node(nodes)); }
	~Deque() {
		for(int i = 0; i < (int)nodes.size(); i++)
			delete nodes[i];
		for(int i = 0; i < (int)conts.size(); i++)
			delete conts[i];
	}
	int push(int ver, int x, int k) {
		root.push_back(root[ver]);
		push(root.back(), k, new cont(x, conts));
		return root.size()-1;
	}
	int pop(int ver, int k) {
		root.push_back(root[ver]);
		pop(root.back(), k);
		return root.size()-1;
	}
	int merge(int v1, int v2) {
		root.push_back(merge(root[v1], root[v2], NULL, NULL));
		return root.size()-1;
	}
	int push_back(int ver, int x) { return push(ver, x, 1); }
	int push_front(int ver, int x) { return push(ver, x, 0); }
	int pop_back(int ver) { return pop(ver, 1); }
	int pop_front(int ver) { return pop(ver, 0); }
	int size(int ver) { return root[ver]->sz; }
	int at(int ver, int i) { return at(root[ver], i)->x; }
	int front(int ver) { return at(root[ver], 0)->x; }
	int back(int ver) { return at(root[ver], size(ver)-1)->x; }
};

/*
 * TEST MATRIX
 */

#include <ctime>
#include <deque>
#include <cstdlib>
#define RANGE 1000
#define LIMIT 1000

bool test(int ntests) {
	srand(time(NULL));
	vector< deque<int> > control(ntests);
	Deque deq;
	for(int test = 1; test < ntests; test++) {
		int add = rand()%2;
		int front = rand()%2;
		int ver = rand()%test;
		control[test] = control[ver];
		printf("test %d: ", test);
		if (test % 4 == 0 && control[test].size() < LIMIT) {
			int over;
			do {
				over = rand()%test;
			} while(control[test].size() + control[over].size() > LIMIT);
			deq.merge(ver, over);
			control[test].insert(control[test].end(), control[over].begin(), control[over].end());
		}
		else if (add || control[test].empty()) {
			int data = rand()%RANGE;
			//printf("pushing %d to %s of ver %d...", data, front ? "front" : "back", ver);
			if (front) {
				control[test].push_front(data);
				deq.push_front(ver, data);
			}
			else {
				control[test].push_back(data);
				deq.push_back(ver, data);
			}
			//printf("done\n");
		}
		else {
			//printf("popping %s from ver %d...", front ? "front" : "back", ver);
			if (front) {
				control[test].pop_front();
				deq.pop_front(ver);
			}
			else {
				control[test].pop_back();
				deq.pop_back(ver);
			}
			//printf("done\n");
		}
	}
	for(int test = 0; test < ntests; test++) {
		int sz1 = control[test].size();
		int sz2 = deq.size(test);
		if (sz1 != sz2) {
			printf("failed on size test %d (%d,%d)\n", test, sz1, sz2);
			return false;
		}
		if (!control[test].empty()) {
			int data1 = control[test].front();
			int data2 = deq.front(test);
			if (data1 != data2) {
				printf("failed on front test %d: %d-%d\n", test, data1, data2);
				return false;
			}
			data1 = control[test].back();
			data2 = deq.back(test);
			if (data1 != data2) {
				printf("failed on back test %d: %d-%d\n", test, data1, data2);
				return false;
			}
		}
		for(int i = 0; i < (int)control[test].size(); i++) {
			int data1 = control[test][i];
			int data2 = deq.at(test, i);
			if (data1 != data2) {
				printf("failed on at %d test %d: %d-%d\n", i, test, data1, data2);
				return false;
			}
		}
	}
	printf("all tests passed\n");
	return true;
}

int main() {
	test(10000);
	return 0;
}
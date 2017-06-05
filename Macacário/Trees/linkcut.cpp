#include <cstdio>
#include <vector>
using namespace std;
#define INF (1<<30)

struct node
{   int size, id, w;
    node *par, *ppar, *left, *right;
    node() {
		par = ppar = left = right = NULL; 
		w = size = INF;
	}
};

class LinkCutTree
{
	vector<node> lct;

	void update(node* p) {
		p->size = p->w;
		if (p->left) p->size += p->left->size;
		if (p->right) p->size += p->right->size;
	}

	void rotateright(node* p) {
		node *q, *r;
		q = p->par, r = q->par;
		if ((q->left = p->right)) q->left->par = q;
		p->right = q, q->par = p;
		if ((p->par = r)) {
			if (q == r->left) r->left = p;
			else r->right = p;
		}
		p->ppar = q->ppar;
		q->ppar = NULL;
		update(q);
	}

	void rotateleft(node* p) {
		node *q, *r;
		q = p->par, r = q->par;
		if ((q->right = p->left)) q->right->par = q;
		p->left = q, q->par = p;
		if ((p->par = r))
		{
			if (q == r->left) r->left = p;
			else r->right = p;
		}
		p->ppar = q->ppar;
		q->ppar = 0;
		update(q);
	}

	void splay(node* p) {
		node *q, *r;
		while (p->par != NULL) {
			q = p->par;
			if (q->par == NULL) {
				if (p == q->left) rotateright(p);
				else rotateleft(p);
			}
			else {
				r = q->par;
				if (q == r->left) {
					if (p == q->left) rotateright(q), rotateright(p);
					else rotateleft(p), rotateright(p);
				}
				else {
					if (p == q->right) rotateleft(q), rotateleft(p);
					else rotateright(p), rotateleft(p);
				}
			}
		}
		update(p);
	}

	node* access(node* p){
		splay(p);
		if (p->right != NULL) {
			p->right->ppar = p;
			p->right->par = NULL;
			p->right = NULL;
			update(p);
		}
		node* last = p;
		while (p->ppar != NULL) {
			node* q = p->ppar;
			last = q;
			splay(q);
			if (q->right != NULL) {
				q->right->ppar = q;
				q->right->par = NULL;
			}
			q->right = p;
			p->par = q;
			p->ppar = NULL;
			update(q);
			splay(p);
		}
		return last;
	}

public:
    LinkCutTree() { }
    LinkCutTree(int n) {
		lct.resize(n + 1);
        for(int i = 0; i <= n; i++){
			lct[i].id = i;
            update(&lct[i]);
        }
    }

	void link(int u, int v, int w) { //u becomes child of v
		node *p = &lct[u], *q = &lct[v];
		access(p);
		access(q);
		p->left = q;
		q->par = p;
		p->w = w;
		update(p);
	}

	void link(int u, int v) { //unweighted
		link(u, v, 1);
	}

    void cut(int u) {
		node* p = &lct[u];
		access(p);
		p->left->par = NULL;
		p->left = NULL;
		update(p);
    }

    int findroot(int u) {
		node* p = &lct[u];
		access(p);
		while (p->left) p = p->left;
		splay(p);
		return p->id;
    }

	bool IsSameTree(int u, int v) {
		return findroot(u) == findroot(v);
	}

    int depth(int u) {
		access(&lct[u]);
		return lct[u].size - lct[u].w;
    }

    int LCA(int u, int v) {
		access(&lct[u]);
		return access(&lct[v])->id;
    }
};

/*
 * TEST MATRIX
 */

#include <cstring>
#include <cstdlib>
#define MAXN 100009
int par[MAXN];

int findroot(int i) {
	if (par[i] >= 0) return findroot(par[i]);
	else return i;
}

bool IsSameSet(int u, int v) {
	return findroot(u) == findroot(v);
}

void link(int u, int v) {
	if (!IsSameSet(u, v)) par[u] = v;
}

void cut(int u) {
	par[u] = -1;
}

int LCA(int u, int v) {
	if (!IsSameSet(u, v)) return -1;
	int du = 0, ul = u;
	while (ul >= 0) {
		du++;
		ul = par[ul];
	}
	int dv = 0, vl = v;
	while (vl >= 0) {
		dv++;
		vl = par[vl];
	}
	while (du > dv) {
		du--;
		u = par[u];
	}
	while (du < dv) {
		dv--;
		v = par[v];
	}
	while (u != v) {
		u = par[u];
		v = par[v];
	}
	return u;
}

bool test(int N, int T) {
	LinkCutTree lct(N);
	memset(&par, -1, sizeof par);
	for (int i = 0, u, v; i<T; i++) {
		int cmd = rand() % 4;
		if (cmd == 0) {
			u = rand() % N;
			v = rand() % N;
			if (IsSameSet(u, v) != lct.IsSameTree(u, v)) {
				printf("failed on test %d (IsSameSet(%d,%d) LCT:%d BF:%d)\n", i, u, v, lct.IsSameTree(u, v), IsSameSet(u, v));
				return false;
			}
			if (IsSameSet(u, v) || par[u] >= 0) {
				i--;
				continue;
			}
			//printf("%d son of %d\n", u, v);
			link(u, v);
			lct.link(u, v);
		}
		if (cmd == 1) {
			u = rand() % N;
			if (par[u] == -1) {
				i--;
				continue;
			}
			//printf("%d cut from %d\n", u, par[u]);
			cut(u);
			lct.cut(u);
		}
		if (cmd == 2) {
			u = rand() % N;
			v = rand() % N;
			if (IsSameSet(u, v) != lct.IsSameTree(u, v)) {
				printf("failed on test %d (IsSameSet(%d,%d) LCT:%d BF:%d)\n", i, u, v, lct.IsSameTree(u, v), IsSameSet(u, v));
				return false;
			}
			if (!IsSameSet(u, v)) {
				i--;
				continue;
			}
			if (LCA(u, v) != lct.LCA(u, v)) {
				printf("failed on test %d (LCA(%d,%d) LCT:%d BF:%d)\n", i, u, v, lct.LCA(u, v), LCA(u, v));
				return false;
			}
		}
		if (cmd == 3) {
			u = rand() % N;
			if (findroot(u) != lct.findroot(u)) {
				printf("failed on test %d (findroot(%d) LCT:%d BF:%d)\n", i, u, lct.findroot(u), findroot(u));
				return false;
			}
		}
	}
}

/*
 * SPOJ DYNALCA
 */

int main()
{
	int N, M, u, v;
	char str[10];
	scanf("%d %d", &N, &M);
	LinkCutTree lct(N+1);
	for(int i=0; i<M; i++){
		scanf(" %s", str);
		if(str[1] == 'i'){
			scanf("%d %d", &u, &v);
			lct.link(u, v);
		}
		if(str[1] == 'u'){
			scanf("%d", &u);
			lct.cut(u);
		}
		if (str[1] == 'c'){
			scanf("%d %d", &u, &v);
			printf("%d\n", lct.LCA(u, v));
		}
	}
	//if (test(10000, 5000000)) printf("All tests passed\n");
	return 0;
}
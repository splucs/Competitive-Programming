#include <cstdio>
#include <vector>
using namespace std;
#define INF 0x3f3f3f3f

/*
 * Link cut tree
 */

struct node {
	int sw, id, w;
	node *par, *ppar, *ls, *rs;
	node() {
		par = ppar = ls = rs = NULL; 
		w = sw = INF;
	}
};

class LinkCutTree {
	vector<node> lct;
	int sum(node *p) { return p ? p->sw : 0; }
	void refresh(node* p) {
		p->sw = p->w + sum(p->ls) + sum(p->rs);
	}
	void rotateright(node* p) {
		node *q, *r;
		q = p->par, r = q->par;
		if (q->ls = p->rs) q->ls->par = q;
		p->rs = q, q->par = p;
		if (p->par = r) {
			if (q == r->ls) r->ls = p;
			else r->rs = p;
		}
		p->ppar = q->ppar;
		q->ppar = NULL;
		refresh(q);
	}
	void rotateleft(node* p) {
		node *q, *r;
		q = p->par, r = q->par;
		if (q->rs = p->ls) q->rs->par = q;
		p->ls = q, q->par = p;
		if (p->par = r) {
			if (q == r->ls) r->ls = p;
			else r->rs = p;
		}
		p->ppar = q->ppar;
		q->ppar = 0;
		refresh(q);
	}
	void splay(node* p) {
		node *q, *r;
		while (p->par != NULL) {
			q = p->par;
			if (q->par == NULL) {
				if (p == q->ls) rotateright(p);
				else rotateleft(p);
				continue;
			}
			r = q->par;
			if (q == r->ls) {
				if (p == q->ls) rotateright(q), rotateright(p);
				else rotateleft(p), rotateright(p);
			}
			else {
				if (p == q->rs) rotateleft(q), rotateleft(p);
				else rotateright(p), rotateleft(p);
			}
		}
		refresh(p);
	}
	node* access(node* p) {
		splay(p);
		if (p->rs != NULL) {
			p->rs->ppar = p; p->rs->par = NULL;
			p->rs = NULL; refresh(p);
		}
		node* last = p;
		while (p->ppar != NULL) {
			node* q = last = p->ppar;
			splay(q);
			if (q->rs != NULL) {
				q->rs->ppar = q;
				q->rs->par = NULL;
			}
			q->rs = p; p->par = q;
			p->ppar = NULL;
			refresh(q); splay(p);
		}
		return last;
	}
public:
	LinkCutTree(int n = 0) {
		lct.resize(n + 1);
		for(int i = 0; i <= n; i++) {
			lct[i].id = i;
			refresh(&lct[i]);
		}
	}
	void link(int u, int v, int w = 1) {
		//u becomes child of v
		node *p = &lct[u], *q = &lct[v];
		access(p); access(q);
		p->ls = q; q->par = p; p->w = w;
		refresh(p);
	}
	void cut(int u) {
		node* p = &lct[u]; access(p);
		p->ls->par = NULL; p->ls = NULL;
		refresh(p);
	}
	int findroot(int u) {
		node* p = &lct[u]; access(p);
		while (p->ls) p = p->ls;
		splay(p);
		return p->id;
	}
	bool IsSameTree(int u, int v) {
		return findroot(u) == findroot(v);
	}
	int depth(int u) {
		access(&lct[u]);
		return lct[u].sw - lct[u].w;
	}
	int LCA(int u, int v) {
		access(&lct[u]);
		return access(&lct[v])->id;
	}
	int dist(int u, int v) {
		if (!IsSameTree(u, v)) return INF;
		node* lca = &lct[LCA(u, v)];
		int ans = 0;
		access(&lct[u]); splay(lca);
		ans += sum(lca->rs);
		access(&lct[v]); splay(lca);
		ans += sum(lca->rs);
		return ans;
	}
};

/*
 * Undirected link cut tree
 */

class UndirectedLinkCutTree {
	LinkCutTree lct;
	vector<int> par;

	void invert(int u) {
		if (par[u] == -1) return;
		int v = par[u];
		invert(v);
		lct.cut(u); par[u] = -1;
		lct.link(v, u); par[v] = u;
	}
public:
	UndirectedLinkCutTree(int n = 0) {
		lct = LinkCutTree(n);
		par.assign(n+1, -1);
	}
	void link(int u, int v) {
		if (lct.depth(u) < lct.depth(v)) {
			invert(u);
			lct.link(u, v); par[u] = v;
		}
		else {
			invert(v);
			lct.link(v, u); par[v] = u;
		}
	}
	void cut(int u, int v) {
		if (par[v] == u) u = v;
		lct.cut(u); par[u] = -1;
	}
	bool IsSameTree(int u, int v) {
		return lct.IsSameTree(u, v);
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

int dist(int u, int v) {
	if (!IsSameSet(u, v)) return -1;
	int lca = LCA(u, v);
	int ans = 0;
	while(u != lca) {
		u = par[u];
		ans++;
	}
	while(v != lca) {
		v = par[v];
		ans++;
	}
	return ans;
}

bool test(int N, int T) {
	LinkCutTree lct(N);
	memset(&par, -1, sizeof par);
	for (int i = 0, u, v; i<T; i++) {
		int cmd = rand() % 5;
		//if (cmd == 1) cmd = 0; //link only
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
		if (cmd == 4) {
			u = rand() % N;
			v = rand() % N;
			if (!IsSameSet(u, v)) {
				i--;
				continue;
			}
			if (dist(u, v) != lct.dist(u, v)) {
				printf("failed on test %d (dist(%d,%d) LCT:%d BF:%d)\n", i, u, v, lct.dist(u, v), dist(u, v));
				return false;
			}
		}
	}
	printf("all tests passed\n");
	return true;
}

int main() {
	test(10000, 100000);
}

/*
 * SPOJ DYNALCA
 */
/*
int main() {
	int N, M, u, v;
	char str[10];
	scanf("%d %d", &N, &M);
	LinkCutTree lct(N+1);
	for(int i=0; i<M; i++) {
		scanf(" %s", str);
		if(str[1] == 'i') {
			scanf("%d %d", &u, &v);
			lct.link(u, v);
		}
		if(str[1] == 'u') {
			scanf("%d", &u);
			lct.cut(u);
		}
		if (str[1] == 'c') {
			scanf("%d %d", &u, &v);
			printf("%d\n", lct.LCA(u, v));
		}
	}
	//if (test(10000, 5000000)) printf("All tests passed\n");
	return 0;
}*/

/*
 * Codeforces 100960H
 */
/*
UndirectedLinkCutTree ulct;

int main() {
	int N, a, b;
	char op;
	scanf("%d", &N);
	ulct = UndirectedLinkCutTree(N);
	while(true) {
		scanf(" %c", &op);
		switch(op) {
		case 'C':
			scanf("%d %d", &a, &b);
			ulct.link(a, b);
			break;
		case 'D':
			scanf("%d %d", &a, &b);
			ulct.cut(a, b);
			break;
		case 'T':
			scanf("%d %d", &a, &b);
			if (ulct.IsSameTree(a, b)) printf("YES\n");
			else printf("NO\n");
			fflush(stdout);
			break;
		case 'E':
			return 0;
		}
	}
	return 0;
}*/
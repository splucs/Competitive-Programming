#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < int(n); i++)
#define FOR1(i, n) for(int i = 1; i <= int(n); i++)
#define REP(i, n) for(int i = (n)-1; i >= 0; i--)
#define REP1(i, n) for(int i = (n); i > 0; i--)
#define MAXN 1000009
#define MXM 4009
#define MAXLOGN 20
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
typedef vector<int> vi;
typedef long long ll;
typedef pair<int, int> ii;

int colr[MAXN], coll[MAXN], maxr[MAXN], maxl[MAXN], ans[MAXN];
int ls[MAXN], rs[MAXN], col[MAXN], sz[MAXN];
int cnt = 0;

inline int newnode(int s) {
	int u = ++cnt;
	sz[u] = s;
	ls[u] = rs[u] = -1;
	return u;
}

void refresh(int u) {
	if (sz[u] == 1) {
		maxl[u] = maxr[u] = 1;
		colr[u] = coll[u] = col[u];
		ans[u] = 1;
	}
	else {
		colr[u] = colr[rs[u]];
		maxr[u] = maxr[rs[u]];
		if (2*maxr[u] == sz[u] && colr[ls[u]] == colr[u]) {
			maxr[u] += maxr[ls[u]];
		}
		coll[u] = coll[ls[u]];
		maxl[u] = maxl[ls[u]];
		if (2*maxl[u] == sz[u] && coll[rs[u]] == coll[u]) {
			maxl[u] += maxl[rs[u]];
		}
		ans[u] = max(ans[ls[u]], ans[rs[u]]);
		if (colr[ls[u]] == coll[rs[u]]) {
			ans[u] = max(ans[u], maxr[ls[u]]+maxl[rs[u]]);
		}
	}
}

void build(int u, int l, int r, int arr[]) {
	if (l == r) {
		col[u] = arr[r];
	}
	else {
		int m = (l + r)/2;
		ls[u] = newnode(sz[u]/2);
		rs[u] = newnode(sz[u]/2);
		build(ls[u], l, m, arr);
		build(rs[u], m+1, r, arr);
	}
	refresh(u);
}

void change(int u, int l, int r, int i, int c) {
	if (l == r) {
		col[u] = c;
	}
	else {
		int m = (l + r)/2;
		if (i <= m) change(ls[u], l, m, i, c);
		else change(rs[u], m+1, r, i, c);
	}
	refresh(u);
}

int get(int u, int l, int r, int i) {
	if (l == r) {
		return col[u];
	}
	else {
		int m = (l + r)/2;
		if (i <= m) return get(ls[u], l, m, i);
		else return get(rs[u], m+1, r, i);
	}
}

int merge(int u, int v) {
	int w = newnode(sz[u]+sz[v]);
	ls[w] = u;
	rs[w] = v;
	refresh(w);
	return w;
}

ii split(int u) {
	return ii(ls[u], rs[u]);
}

int arr[MAXN], root[MAXN], nroot = 0;

int main() {
	int n, q;
	scanf("%d %d", &n, &q);
	FOR1(i, n) {
		int ver = ++nroot;
		int s;
		scanf("%d", &s);
		FOR1(j, s) scanf("%d", &arr[j]);
		root[ver] = newnode(s);
		build(root[ver], 1, s, arr);
	}
	while(q --> 0) {
		int op;
		scanf("%d", &op);
		if (op == 1) {
			int i, j, ver;
			scanf("%d %d %d", &i, &j, &ver);
			int c1 = get(root[ver], 1, sz[root[ver]], i);
			int c2 = get(root[ver], 1, sz[root[ver]], j);
			change(root[ver], 1, sz[root[ver]], i, c2);
			change(root[ver], 1, sz[root[ver]], j, c1);
		}
		if (op == 2) {
			int ver1, ver2;
			scanf("%d %d", &ver1, &ver2);
			int ver = ++nroot;
			root[ver] = merge(root[ver1], root[ver2]);
		}
		if (op == 3) {
			int ver;
			scanf("%d", &ver);
			ii roots = split(root[ver]);
			root[++nroot] = roots.fi;
			root[++nroot] = roots.se;
		}
		if (op == 4) {
			int ver;
			scanf("%d", &ver);
			printf("%d\n", ans[root[ver]]);
		}
	}
	return 0;
}
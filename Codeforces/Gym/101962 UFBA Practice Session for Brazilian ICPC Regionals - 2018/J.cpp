#include <bits/stdc++.h>
#define MAXN 100009
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define fi first
#define se second
#define sz(x) int(x.size())
#define mset(x, y) memset(&x, y, sizeof x)
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;

struct UnionFind {
	vector<ii> edges;
	map<int, int> par;
	int find(int i) {
		if (!par.count(i)) return i;
		return par[i] = find(par[i]);
	}
	bool unite(int i, int j) {
		ii cur = {i, j};
		i = find(i);
		j = find(j);
		if (i == j) return false;
		edges.pb(cur);
		par[i] = j;
		return true;
	}
	void clear() {
		edges.clear();
		par.clear();
	}
	int size() {
		return edges.size();
	}
	void swap(UnionFind &o) {
		edges.swap(o.edges);
		par.swap(o.par);
	}
};

int n, k, ans[MAXN];
int eu[MAXN], ev[MAXN];
vector<int> g[MAXN];
set<int> sub[MAXN];
UnionFind uf[MAXN];

void merge(int u, int v) {
	if (sz(sub[u]) < sz(sub[v])) {
		swap(sub[u], sub[v]);
	}
	for(int w : sub[v]) {
		sub[u].insert(w);
	}
	sub[v].clear();
	
	if (sz(uf[u]) < sz(uf[v])) {
		uf[u].swap(uf[v]);
	}
	for(ii e : uf[v].edges) {
		uf[u].unite(e.fi, e.se);
	}
	uf[v].clear();
}

void dfs(int u) {
	sub[u].clear();
	sub[u].insert(eu[u]);
	sub[u].insert(ev[u]);
	uf[u].clear();
	uf[u].unite(eu[u], ev[u]);

	for(int v : g[u]) {
		dfs(v);
		merge(u, v);
	}

	ans[u] = k - sz(uf[u].edges);
}

int main() {
	scanf("%d %d", &n, &k);
	FOR1(i, n-1) {
		int p;
		scanf("%d", &p);
		g[p].pb(i+1);
	}
	FOR1(u, n) {
		scanf("%d %d", &eu[u], &ev[u]);
	}
	dfs(1);
	FOR1(u, n) printf("%d\n", ans[u]);
	return 0;
}
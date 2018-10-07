#include <bits/stdc++.h>
#define FOR(x, n) for(int x=0; x<n; x++)
#define FOR1(x, n) for(int x=1; x<=n; x++)
#define sz(x) ((int)x.size())
#define all(x) x.begin(),x.end()
#define pb push_back
#define INF 0x3f3f3f3f
#define MAXN 100009
#define MAXLOGN 18
#define MOD 1000000007
using namespace std;
typedef pair<int, int> ii;
typedef long long ll;

int par[MAXN][MAXLOGN], lvl[MAXN];
vector<int> adj[MAXN];
vector<int> ans;

int predfs(int u, int p, int d) {
	par[u][0] = p;
	lvl[u] = d;

	FOR(i, sz(adj[u])) {
		int v = adj[u][i];
		if (v == p) continue;
		predfs(v, u, d+1);
	}
}

int pre(int n) {
	for (int j = 1; j < MAXLOGN; j++) {
		for (int i = 0; i < n; i++) {
			par[i][j] = par[par[i][j-1]][j-1];
		}
	}
}

vector<int> starts[MAXN];
vector<int> one[MAXN], up[MAXN], two[MAXN], branches[MAXN][2];
vector<ii> paths;

void go_lca(int u, int v) {
	int idx = sz(paths);
	
	if (lvl[u] < lvl[v]) swap(u, v);
	int a = u, b = v;	
	paths.pb(ii(u, v));

	int lca = u;
	if (u == v) {
		starts[a].pb(idx);
		one[lca].pb(idx); up[lca].pb(u);
		return;
	}

	if (lvl[u] != lvl[v]) {
		for (int j = MAXLOGN-1; j >= 0; j--) {
			if (lvl[par[u][j]] > lvl[v]) u = par[u][j];
		}
		lca = par[u][0];
		if (lca == v) {
			starts[a].pb(idx);
			one[lca].pb(idx); up[lca].pb(u);
			return;
		}
		u = lca;
	}
	
	for (int j = MAXLOGN-1; j >= 0; j--) {
		if (par[u][j] != par[v][j]) {
			u = par[u][j];
			v = par[v][j];
		}
	}

	lca = par[u][0];

	starts[a].pb(idx);
	starts[b].pb(idx);

	two[lca].pb(idx);
	branches[lca][0].pb(u);
	branches[lca][1].pb(v);
	return;
}

set<int> sets[MAXN];

void dfs(int u, int p) {
	FOR(i, sz(adj[u])) {
		int v = adj[u][i];
		if (v == p) continue;
		dfs(v, u);
	}
	FOR(i, sz(starts[u])) {
		int idx = starts[u][i];
		sets[u].insert(idx);
	}
	bool deleted = false;
	FOR(i, sz(one[u])) {
		int idx = one[u][i];
		int other = up[u][i];
		if (sets[other].count(idx)) {
			deleted = true;
		}
	}
	FOR(i, sz(two[u])) {
		int idx = two[u][i];
		int o1 = branches[u][0][i], o2 = branches[u][1][i];
		if (sets[o1].count(idx) && sets[o2].count(idx)) {
			deleted = true;
		} else {
			sets[o1].erase(idx);
			sets[o2].erase(idx);
		}
	}

	if (deleted) {
		ans.pb(u);
		sets[u].clear(); return;
	}
	FOR(i, sz(adj[u])) {
		int v = adj[u][i];
		if (v == p) continue;
		if (sz(sets[u]) < sz(sets[v])) swap(sets[u], sets[v]);
		for (auto& it : sets[v]) sets[u].insert(it);
		sets[v].clear();
	}
}

int main() {
	int n, a, b;
	scanf("%d", &n);
	FOR(i, n-1) {
		scanf("%d %d", &a, &b);
		a--; b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}

	predfs(0, 0, 0);
	pre(n);

	int m;
	scanf("%d", &m);
	FOR(T, m) {
		scanf("%d %d", &a, &b);
		a--; b--;
		go_lca(a, b);
	}
	/*FOR(i, n) {
		printf("-- %d\n", sz(starts[i]));
		for (auto& v : starts[i]) printf("%d ", v);
		printf("\n-- %d\n", sz(one[i]));
		for (auto& v : one[i]) printf("%d ", v);
		printf("\n-- %d\n", sz(two[i]));
		for (auto& v : two[i]) printf("%d ", v);
	}*/

	dfs(0, 0);
	printf("%d\n", sz(ans));
	FOR(i, sz(ans)) {
		if (i > 0) printf(" ");
		printf("%d", ans[i] + 1);
	}
	printf("\n");
}
#include <bits/stdc++.h>
using namespace std;
#define MAXN 500009
#define MAXLOGN 20
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define fi first
#define se second
#define pb push_back
#define mset(x, y) memset(&x, y, sizeof x)
typedef long long ll;
typedef pair<int, int> ii;

int n, m;
int par[MAXN];

void init() {
	FOR1(i, n) par[i] = i;
}

int find(int i) {
	if (i == par[i]) return i;
	return par[i] = find(par[i]);
}

bool isSame(int i, int j) {
	return find(i) == find(j);
}

void unite(int i, int j) {
	par[find(i)] = find(j);
}

int eu[MAXN], ev[MAXN], ew[MAXN], id[MAXN];
vector<ii> g[MAXN];
map<ii, int> value, mst;

bool comp(int i, int j) {
	return ew[i] < ew[j];
}

int kruskal() {
	int ans = 0;
	sort(id, id+m, comp);
	FOR(jt, m) {
		int j = id[jt];
		int u = eu[j], v = ev[j], w = ew[j];
		if (isSame(u, v)) continue;
		//printf("edge %d-%d\n", u, v);
		ans += w;
		unite(u, v);
		g[u].pb({w, v});
		g[v].pb({w, u});
		mst[{u, v}] = mst[{v, u}] = w;
	}
	return ans;
}

int P[MAXN][MAXLOGN], D[MAXN][MAXLOGN];
int depth[MAXN];

void dfs(int u, int h) {
	for(ii pp : g[u]) {
		int v = pp.se;
		int w = pp.fi;
		if (v == P[u][0]) continue;
		P[v][0] = u;
		D[v][0] = w;
		dfs(v, h+1);
	}
	depth[u] = h;
}

void computeP(int root) {
	P[root][0] = root;
	D[root][0] = 0;
	dfs(root, 0);
	FOR1(j, MAXLOGN-1) FOR1(u, n) {
		int v = P[u][j-1];
		P[u][j] = P[v][j-1];
		D[u][j] = max(D[u][j-1], D[v][j-1]);
	}
}

int LA(int u, int i, int &ans) {
	if (i <= 0) return u;
	FOR(j, MAXLOGN) {
		if (i & (1<<j)) {
			ans = max(ans, D[u][j]);
			u = P[u][j];
		}
	}
	return u;
}

int LCA(int u, int v) {
	int ans = 0;
	u = LA(u, depth[u] - depth[v], ans);
	v = LA(v, depth[v] - depth[u], ans);
	if (u == v) return ans;
	REP(j, MAXLOGN) {
		if (P[u][j] != P[v][j]) {
			ans = max(ans, D[u][j]);
			ans = max(ans, D[v][j]);
			u = P[u][j];
			v = P[v][j];
		}
	}
	ans = max(ans, D[u][0]);
	ans = max(ans, D[v][0]);
	return ans;
}

int main() {
	scanf("%d %d", &n, &m);
	init();
	FOR(j, m) {
		scanf("%d %d %d", &eu[j], &ev[j], &ew[j]);
		id[j] = j;
		value[{eu[j], ev[j]}] = ew[j];
		value[{ev[j], eu[j]}] = ew[j];
	}
	int cost = kruskal();
	//printf("cost = %d\n", cost);
	computeP(1);
	int q;
	scanf("%d", &q);
	while(q --> 0) {
		int u, v;
		scanf("%d %d", &u, &v);
		if (mst.count({u, v})) printf("%d\n", cost);
		else {
			//printf("cost = %d, rem = %d, new = %d\n", cost, LCA(u, v), value[{u,v}]);
			printf("%d\n", cost - LCA(u, v) + value[{u, v}]);
		}
	}
	return 0;
}
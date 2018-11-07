#include <bits/stdc++.h>
#define MAXN 200009
#define MAXLOGN 20
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define fi first
#define se second
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
using namespace std;
typedef long long int ll;
typedef pair<int, int> ii;
typedef vector<int> vi;

int n, m;
vector<int> g[MAXN];
int P[MAXN][MAXLOGN], level[MAXN];
int euler[MAXN];

void dfs(int u, int h, int &t) {
	level[u] = h;
	euler[++t] = u;
	for(int v : g[u]) {
		if (v == P[u][0]) continue;
		P[v][0] = u;
		dfs(v, h+1, t);
	}
	euler[++t] = u;
}

void computeP(int root, int n) {
	P[root][0] = root;
	int t = 0;
	dfs(root, 0, t);

	FOR1(j, MAXLOGN-1) FOR1(i, n) {
		P[i][j] = P[P[i][j-1]][j-1];
	}
}

int LA(int u, int i) {
	if (i <= 0) return u;
	FOR(j, MAXLOGN) {
		if (i & (1<<j)) u = P[u][j];
	}
	return u;
}

int LCA(int u, int v) {
	u = LA(u, level[u]-level[v]);
	v = LA(v, level[v]-level[u]);
	if (u == v) return u;
	REP(j, MAXLOGN) {
		if (P[u][j] != P[v][j]) {
			u = P[u][j];
			v = P[v][j];
		}
	}
	return P[u][0];
}

int dist(int u, int v) {
	return level[u] + level[v] - 2*level[LCA(u, v)];
}

int getfarthest(int v, vi &arr) {
	int maxdist = -1, ans = -1;
	for(int u : arr) {
		int d = dist(u, v);
		if (maxdist < d) {
			maxdist = d;
			ans = u;
		}
	}
	return ans;
}

int main() {
	scanf("%d %d", &n, &m);
	FOR1(i, n) {
		scanf("%d", &color[i]);
		col[color[i]].pb(i);
	}
	FOR(j, n-1) {
		int u, v;
		scanf("%d %d", &u, &v);
		g[u].pb(v);
		g[v].pb(u);
	}

	computeP(1, n);

	FOR1(c, m) {
		pivot = getfarthest(col[c][0], col[c]);
		pivot = getfarthest(pivot, col[c]);
		sort(all(col[c]), comp);
	}

	FOR1(c, m) {
		FOR(i, sz(col[c])) {
			if (i+1 == sz(col[c])) continue;
			pivot = col[c][i+1];
			int u = col[c][i];
			int v = getclosest(pivot, g[u]);
			if (v == col[c][i+1]) continue;
			dep[color[v]].pb(color[u]);
			//printf("color %d comes before %d\n", color[u], color[v]);
		}
	}

	FOR1(i, m) ts(i);

	for(int c : toposort) {
		printf("%d %d %d\n", c, col[c].front(), col[c].back());
	}
	return 0;
}
#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define MAXLOGN 20
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define sz(x) int(x.size())
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;

vi g[MAXN];
int d[MAXN];
int P[MAXN][MAXLOGN];
int n;

int dfs(int u) {
	for(int v : g[u]) {
		if (P[u][0] == v) continue;
		P[v][0] = u;
		d[v] = 1 + d[u];
		dfs(v);
	}
}

void computeP() {
	P[1][0] = 1;
	d[1] = 1;
	dfs(1);
	FOR1(j, MAXLOGN-1) FOR1(u, n) {
		P[u][j] = P[P[u][j-1]][j-1];
	}
}

int LCA(int u, int v) {
	if (d[u] < d[v]) swap(u, v);
	int jump = d[u] - d[v];
	FOR(i, MAXLOGN) {
		if (jump & (1<<i)) u = P[u][i];
	}
	if (u == v) return u;
	REP(i, MAXLOGN) {
		if (P[u][i] != P[v][i]) {
			u = P[u][i];
			v = P[v][i];
		}
	}
	return P[u][0];
}

int root;

int solve(int u, int v) {
	int ru = LCA(root, u);
	int rv = LCA(root, v);
	if (d[ru] > d[rv]) return ru;
	if (d[ru] < d[rv]) return rv;
	return LCA(u, v);
}

int main() {
	#ifdef ONLINE_JUDGE
	freopen("dynamic.in", "r", stdin);
	freopen("dynamic.out", "w", stdout);
	#endif

	while(scanf("%d", &n), n) {
		FOR1(u, n) g[u].clear();
		FOR(j, n-1) {
			int u, v;
			scanf("%d %d", &u, &v);
			g[u].pb(v);
			g[v].pb(u);
		}
		computeP();
		root = 1;
		int q;
		scanf("%d", &q);
		while(q --> 0) {
			char op;
			scanf(" %c", &op);
			if (op == '?') {
				int u, v;
				scanf("%d %d", &u, &v);
				printf("%d\n", solve(u, v));
			}
			else {
				scanf("%d", &root);
			}
		}
	}
	return 0;
}
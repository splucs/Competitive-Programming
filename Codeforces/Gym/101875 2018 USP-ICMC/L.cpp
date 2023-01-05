#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < int(n); i++)
#define MAXN 100009
#define pb push_back
typedef vector<int> vi;

int ans = 1;
vi g[MAXN];

void dfs(int u, int p, int h) {
	ans = max(ans, h);
	for(int v : g[u]) {
		if (v == p) continue;
		dfs(v, u, h+1);
	}
}

int main() {
	int n, s;
	scanf("%d %d", &n, &s);
	FOR(j, n-1) {
		int u, v;
		scanf("%d %d", &u, &v);
		g[u].pb(v);
		g[v].pb(u);
	}
	dfs(s, -1, 1);
	printf("%d\n", ans);
	return 0;
}
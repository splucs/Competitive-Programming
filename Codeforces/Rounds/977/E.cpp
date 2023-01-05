#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define MAXM ((1e+18) + 100)
#define MOD 1000000007
#define INF 1000000009
#define EPS 1e-9
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;
#define EPS 1e-9

vector<int> g[MAXN];
bool vis[MAXN], ok[MAXN];

bool dfs(int u, int p) {
	if (vis[u]) return ok[u];
	vis[u] = true;
	ok[u] = true;
	if (g[u].size() != 2u) ok[u] = false;
	for(int v : g[u]) {
		ok[u] = ok[u] && dfs(v, u);
	}
	return ok[u];
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	FOR(k, m) {
		int u, v;
		scanf("%d %d", &u, &v);
		g[u].pb(v);
		g[v].pb(u);
	}
	int ans = 0;
	FOR1(u, n) {
		if (!vis[u] && dfs(u, -1)) {
			ans++;
		}
	}
	printf("%d\n", ans);
	return 0;
}
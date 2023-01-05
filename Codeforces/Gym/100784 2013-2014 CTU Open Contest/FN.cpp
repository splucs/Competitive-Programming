#include <bits/stdc++.h>
using namespace std;
#define MAXN 10009
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define fi first
#define se second
#define sz(x) int(x.size())
#define all(x) x.begin(),x.end()
#define mset(x, y) memset(&x, y, sizeof x)
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;

vi g[MAXN];
bool vis[MAXN];
int cnt4, cnt3;
int par[MAXN];

int find(int u) {
	if (u == par[u]) return u;
	return par[u] = find(par[u]);
}

bool isSameSet(int u, int v) {
	return find(u) == find(v);
}

void unite(int u, int v) {
	par[find(u)] = find(v);
}

void dfs(int u) {
	if (vis[u]) return;
	vis[u] = true;
	if (g[u].size() >= 3u) cnt3++;
	if (g[u].size() >= 4u) cnt4++;
	for(int v : g[u]) dfs(v);
}

int main() {
	int n, m;
	while(scanf("%d %d", &n, &m) != EOF) {
		FOR1(u, n) {
			vis[u] = false;
			g[u].clear();
			par[u] = u;
		}
		FOR(j, m) {
			int u, v;
			scanf("%d %d", &u, &v);
			if (isSameSet(u, v)) continue;
			unite(u, v);
			g[u].pb(v);
			g[v].pb(u);
		}
		bool ok = false;
		FOR1(u, n) {
			cnt3 = 0, cnt4 = 0;
			dfs(u);
			if (cnt4 >= 1 || cnt3 >= 2) ok = true;
		}
		printf("%s\n", ok ? "YES" : "NO");
	}
	return 0;
}
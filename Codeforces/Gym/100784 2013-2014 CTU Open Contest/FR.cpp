#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(),x.end()
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;

vector<ii> g[MAXN];

int dfs(int u, int p = -1) {
	int sum = 0;
	if (p != -1 && g[u].size() == 1u) return INF;
	for(auto pp : g[u]) {
		int v = pp.se;
		int w = pp.fi;
		if (v == p) continue;
		sum += min(w, dfs(v, u));
	}
	return sum;
}

int main() {
	int n, s;
	while(scanf("%d %d", &n, &s) != EOF) {
		FOR1(u, n) g[u].clear();
		FOR(j, n-1) {
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);
			g[u].pb({w, v});
			g[v].pb({w, u});
		}
		printf("%d\n", dfs(s));
	}
	return 0;
}
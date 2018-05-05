#include <bits/stdc++.h>
using namespace std;
#define MAXN 10009
#define INF (1<<30)
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define pb push_back
typedef pair<int, int> ii;

bool vis[MAXN][11][11], trust[MAXN];
int N, H, M;
vector<ii> g[MAXN];

void dfs(int u, int d, int t, int dist[]) {
	if (t > 10) return;
	if (vis[u][d][t]) return;
	vis[u][d][t] = true;
	if (trust[u]) dist[u] = min(d, dist[u]);
	for(auto pp : g[u]) {
		int v = pp.first;
		int w = pp.second;
		dfs(v, d+1, t+w, dist);
	}
}

int dist1[MAXN], dist2[MAXN];

int main() {
	while(scanf("%d", &N), N) {
		memset(&trust, false, sizeof trust);
		scanf("%d", &H);
		FOR(i, H) {
			int c;
			scanf("%d", &c);
			trust[c] = true;
		}
		trust[1] = trust[N] = true;
		scanf("%d", &M);
		while(M --> 0) {
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);
			g[u].pb({v, w});
			g[v].pb({u, w});
		}
		
		FOR1(u, N) {
			dist1[u] = 11;
			FOR(i, 11) FOR(j, 11) vis[u][i][j] = false;
		}
		dfs(1, 0, 0, dist1);
		
		FOR1(u, N) {
			dist2[u] = 11;
			FOR(i, 11) FOR(j, 11) vis[u][i][j] = false;
		}
		dfs(1, 0, 0, dist2);
		
		int ans = INF;
		FOR1(u, N) {
			ans = min(ans, dist1[u]+dist2[u]);
		}
		if (ans == INF) ans = -1;
		printf("%d\n", ans);
	}
	return 0;
}

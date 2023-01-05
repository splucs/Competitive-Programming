#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; i++)
#define MAXN 100009
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define pb push_back
#define fi first
#define se second
#define mset(x, y) memset(&x, y, sizeof x);
typedef pair<int, int> ii;

vector<ii> g[MAXN];
int dist[MAXN], cnt[MAXN];
int n, m;

void dijkstra(int s, int t) {
	mset(dist, INF);
	mset(cnt, 0);
	set<ii> pq;
	dist[s] = 0;
	cnt[s] = 1;
	pq.insert({0, s});
	while(!pq.empty()) {
		int u = pq.begin()->se;
		pq.erase(pq.begin());
		for(ii pp : g[u]) {
			int w = pp.fi;
			int v = pp.se;
			if (dist[v] > dist[u] + w) {
				pq.erase({dist[v], v});
				dist[v] = dist[u] + w;
				pq.insert({dist[v], v});
				cnt[v] = 0;
			}
			if (dist[v] == dist[u] + w)
				cnt[v] = (cnt[u] + cnt[v]) % MOD;
		}
	};
}

int main() {
	while(scanf("%d %d", &n, &m) != EOF) {
		FOR(u, n) g[u].clear();
		FOR(j, m) {
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);
			g[u].pb({w, v});
			g[v].pb({w, u});
		}
		dijkstra(0, n-1);
		printf("%d %d\n", dist[n-1], cnt[n-1]);
	}
	return 0;
}
#include <bits/stdc++.h>
using namespace std;
#define MAXN 10009
#define INF (1<<30)
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define pb push_back
typedef pair<int, int> ii;

int N, H, M;
vector<ii> g[MAXN];
vector<int> r[MAXN];
int dist[MAXN];

void dijkstra(int s) {
	set<ii> pq;
	FOR1(u, N) dist[u] = INF;
	dist[s] = 0;
	pq.insert(ii(dist[s], s));
	r[s].clear();
	while(!pq.empty()) {
		int u = pq.begin()->second;
		pq.erase(pq.begin());
		if (dist[u] <= 600 && u != s) {
			r[s].pb(u);
		}
		for(ii pp : g[u]) {
			int v = pp.second;
			int w = pp.first;
			if (dist[v] > dist[u] + w) {
				if (pq.count(ii(dist[v], v)))
					pq.erase(ii(dist[v], v));
				dist[v] = dist[u] + w;
				pq.insert(ii(dist[v], v));
			}
		}
	}
}

vector<int> trust;

int bfs(int s, int t) {
	FOR1(u, N) dist[u] = -1;
	dist[s] = -1;
	queue<int> q;
	q.push(s);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int v : r[u]) {
			if (dist[v] == -1) {
				dist[v] = 1 + dist[u];
				q.push(v);
			}
		}
	}
	return dist[t];
}

int main() {
	while(scanf("%d", &N), N) {
		scanf("%d", &H);
		trust.clear();
		trust.pb(1); trust.pb(N);
		FOR(i, H) {
			int c;
			scanf("%d", &c);
			trust.pb(c);
		}
		scanf("%d", &M);
		FOR1(u, N) {
			g[u].clear();
			r[u].clear();
		}
		while(M --> 0) {
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);
			g[u].pb({w, v});
			g[v].pb({w, u});
		}
		for(int u : trust) {
			dijkstra(u);
		}
		
		printf("%d\n", bfs(1, N));
	}
	return 0;
}

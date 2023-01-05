
#include <set>
#include <vector>
using namespace std;
#define MAXN 100009
#define INF 0x3f3f3f3f
typedef pair<int, int> ii;

/*
 * Dijkstra's Algorithm O(nlogn + m)
 */
 
vector<ii> adjList[MAXN];
 
int dijkstra(int s, int t, int n, int dist[]) {
	for(int i = 1; i <= n; i++) dist[i] = INF;
	set<ii> pq;
	dist[s] = 0;
	pq.insert(ii(0, s));
	while(!pq.empty()) {
		int u = pq.begin()->second;
		pq.erase(pq.begin());
		for(int i=0; i<(int)adjList[u].size(); i++) {
			int v = adjList[u][i].second;
			int w = adjList[u][i].first;
			if (dist[v] > dist[u] + w) {
				pq.erase(ii(dist[v], v));
				dist[v] = dist[u] + w;
				pq.insert(ii(dist[v], v));
			}
		}
	}
	return dist[t];
}

/*
 * SPOJ EZDIJKST
 */

#include <cstdio>

int dist[MAXN], n, m;
 
int main() {
	int T;
	int u, v, w, s, t;
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d", &n, &m);
		for(int i=1; i<=n; i++) adjList[i].clear();
		for(int i=0; i<m; i++) {
			scanf("%d %d %d", &u, &v, &w);
			adjList[u].push_back(ii(w, v));
		}
		scanf("%d %d", &s, &t);
		int ans = dijkstra(s, t, n, dist);
		if (ans == INF) printf("NO\n");
		else printf("%d\n", ans);
	}
	return 0;
}
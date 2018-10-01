/*
 * Solução do problema http://www.spoj.com/submit/EZDIJKST/
 */
#include <cstdio>
#include <set>
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;
const int MAXN = 100009;
const int INF = 1e9;
 
using ii = pair<int, int>;
vector<ii> adjList[MAXN];
int dist[MAXN], n, m;
 
int dijkstra(int s, int t)
{
	for(int i=1; i<=n; i++) dist[i] = INF;
	dist[s]=0;
	set<pair<int, int> > nodes;
	nodes.insert(ii(0, s));
	while(!nodes.empty()) {
		int u = nodes.begin()->second;
		nodes.erase(nodes.begin());
		for(unsigned i=0; i<adjList[u].size(); i++) {
			int v = adjList[u][i].second;
			int w = adjList[u][i].first;
			if (dist[v] > dist[u] + w) {
				if (dist[v] < INF) {
					nodes.erase(ii(dist[v], v));
				}
				dist[v] = dist[u] + w;
				nodes.insert(ii(dist[v], v));
			}
		}
	}
	return dist[t];
}
 
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
		int ans = dijkstra(s, t);
		if (ans == INF) printf("NO\n");
		else printf("%d\n", ans);
	}
	return 0;
}

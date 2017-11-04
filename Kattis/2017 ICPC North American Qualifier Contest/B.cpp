#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define INF (1LL<<60)

typedef long long ll;
typedef pair<ll, int> ii;
vector<ii> adjList[MAXN];
ll dist[MAXN];
int n, m;
 
void dijkstra(int s) {
	for(int i=0; i<2*n; i++) dist[i] = INF;
	dist[s]=0;
	set<pair<int, int> > nodes;
	nodes.insert(ii(0, s));
	while(!nodes.empty()){
		int u = nodes.begin()->second;
		nodes.erase(nodes.begin());
		for(int i=0; i<(int)adjList[u].size(); i++){
			int v = adjList[u][i].second;
			ll w = adjList[u][i].first;
			if (dist[v] > dist[u] + w){
				if (dist[v] < INF){
					nodes.erase(ii(dist[v], v));
				}
				dist[v] = dist[u] + w;
				nodes.insert(ii(dist[v], v));
			}
		}
	}
}

int main() {
	int f, s, t, u, v;
	ll w;
	scanf("%d %d %d %d %d", &n, &m, &f, &s, &t);
	for(int j=0; j<m; j++) {
		scanf("%d %d %lld", &u, &v, &w);
		adjList[u].push_back(ii(w, v));
		adjList[v].push_back(ii(w, u));
		adjList[u+n].push_back(ii(w, v+n));
		adjList[v+n].push_back(ii(w, u+n));
	}
	for(int j=0; j<f; j++) {
		scanf("%d %d", &u, &v);
		adjList[u].push_back(ii(0, v+n));
	}
	dijkstra(s);
	printf("%I64d\n", min(dist[t], dist[t+n]));
	return 0;
}
#include <cstdio>
#include <set>
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;
#define MAXN 10009
#define INF (1<<30)
 
typedef pair<int, int> ii;
vector<ii> adjList[MAXN], prv[MAXN];
int dist[MAXN], n, m, ans;
 
int dijkstra(int s, int t)
{
	for(int i=1; i<=n; i++) dist[i] = INF;
	dist[s]=0;
	set<pair<int, int> > nodes;
	nodes.insert(ii(0, s));
	while(!nodes.empty()){
		int u = nodes.begin()->second;
		nodes.erase(nodes.begin());
		for(int i=0; i<(int)adjList[u].size(); i++){
			int v = adjList[u][i].second;
			int w = adjList[u][i].first;
			if (dist[v] > dist[u] + w){
				prv[v].clear();
				if (dist[v] < INF){
					nodes.erase(ii(dist[v], v));
				}
				dist[v] = dist[u] + w;
				nodes.insert(ii(dist[v], v));
			}
			if (dist[v] == dist[u] + w){
				prv[v].push_back(ii(w, u));
			}
		}
	}
	return dist[t];
}

int dfs(int u){
	if (dist[u] == 1) return 0;
	dist[u] = 1;
	int ans = 0;
	for(int i=0; i<(int)prv[u].size(); i++){
		int v = prv[u][i].second;
		int w = prv[u][i].first;
		prv[u][i].first = 0;
		ans += dfs(v);
		ans += w;
	}
	return ans;
}

int main()
{
	int u, v, w;
	scanf("%d %d", &n, &m);
	while(m--){
		scanf("%d %d %d", &u, &v, &w);
		adjList[u].push_back(ii(w, v));
		adjList[v].push_back(ii(w, u));
	}
	dijkstra(0, n-1);
	memset(&dist, 0, sizeof dist);
	printf("%d\n", 2*dfs(n-1));
	return 0;
}
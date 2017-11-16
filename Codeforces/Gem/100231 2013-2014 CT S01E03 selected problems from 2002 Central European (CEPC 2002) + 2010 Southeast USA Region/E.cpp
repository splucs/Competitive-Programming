#include <bits/stdc++.h>
using namespace std;
#define MAXN 30009
#define INF (1<<30)
 
typedef pair<int, int> ii;
vector<ii> adjList[MAXN];
int dist[MAXN], mint[MAXN][12], rank[MAXN], id[MAXN], N, M, ans;
 
void dijkstra(int s) {
	for(int i=1; i<=N; i++) dist[i] = INF;
	
	dist[s]=0;
	set<pair<int, int> > heap;
	heap.insert(ii(0, s));
	
	while(!heap.empty()){
		int u = heap.begin()->second;
		heap.erase(heap.begin());
		
		mint[u][rank[s]] = min(mint[u][rank[s]], dist[u]);
		
		bool ok = true;
		for(int r = rank[s]+1; r<=10 && ok; r++) {
			if (dist[u] >= mint[u][r]) ok = false;
		}
		if (!ok) continue;
		ans++;
		
		for(int i=0; i<(int)adjList[u].size(); i++){
			int v = adjList[u][i].second;
			int w = adjList[u][i].first;
			if (dist[v] > dist[u] + w){
				if (dist[v] < INF) heap.erase(ii(dist[v], v));
				dist[v] = dist[u] + w;
				heap.insert(ii(dist[v], v));
			}
		}
	}
}

bool comp(int i, int j) {
	return rank[i] > rank[j];
}

int main() {
	scanf("%d %d", &N, &M);
	
	int u, v, w;
	for(u=1; u<=N; u++) {
		scanf("%d", &rank[u]);
		for(int r=1; r<=10; r++) mint[u][r] = INF;
		id[u] = u;
	}
	for(int j=0; j<M; j++) {
		scanf("%d %d %d", &u, &v, &w);
		adjList[u].push_back(ii(w, v));
		adjList[v].push_back(ii(w, u));
	}
	
	sort(id+1, id+1+N, comp);
	ans = 0;
	for(int i=1; i<=N; i++) {
		u = id[i];
		dijkstra(u);
	}
	
	printf("%d\n", ans);
	return 0;
	
}
#include <bits/stdc++.h>
using namespace std;
#define MAXN 30009
#define INF (1<<30)
 
typedef pair<int, int> ii;
vector<ii> adjList[MAXN];
int dist[MAXN], mint[MAXN], minr[MAXN], curt[MAXN], curr[MAXN], rnk[MAXN], id[MAXN], N, M, ans;
 
void dijkstra(int s) {
	for(int i=1; i<=N; i++) dist[i] = INF;
	
	dist[s]=0;
	set<pair<int, int> > heap;
	heap.insert(ii(0, s));
	
	while(!heap.empty()){
		int u = heap.begin()->second;
		heap.erase(heap.begin());
		
		if (curr[u] > rnk[s]) {
			minr[u] = curr[u];
			mint[u] = min(mint[u], curt[u]);
			curr[u] = rnk[s];
			curt[u] = INF;
		}
		curt[u] = min(curt[u], dist[u]);
		
		if (mint[u] <= dist[u]) continue;
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
	return rnk[i] > rnk[j];
}

int main() {
	int T;
	scanf("%d", &T);
	while(T --> 0) {
		scanf("%d %d", &N, &M);
		
		int u, v, w;
		for(u=1; u<=N; u++) {
			scanf("%d", &rnk[u]);
			curr[u] = curt[u] = mint[u] = minr[u] = INF;
			adjList[u].clear();
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
	}
	return 0;
	
}
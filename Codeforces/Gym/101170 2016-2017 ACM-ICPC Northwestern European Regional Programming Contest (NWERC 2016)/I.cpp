#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define INF (1<<25)

int N, M, K;
queue<int> q[3];
int dist[3][MAXN];
vector<int> adjList[MAXN], revAdj[MAXN];

int main() {
	scanf("%d %d %d", &N, &M, &K);
	for(int k=0; k<3; k++) {
		for(int u=1; u<=N; u++) dist[k][u] = INF;
	}
	for(int i=0, u; i<M; i++) {
		scanf("%d", &u);
		dist[1][u] = 0;
		q[1].push(u);
	}
	for(int i=0, u; i<K; i++) {
		scanf("%d", &u);
		dist[2][u] = 0;
		q[2].push(u);
	}
	for(int u=1, a, v; u<=N; u++) {
		scanf("%d", &a);
		while (a --> 0) {
			scanf("%d", &v);
			adjList[u].push_back(v);
			revAdj[v].push_back(u);
		}
	}
	
	q[0].push(1);
	dist[0][1] = 0;
	for(int k=0; k<3; k++) {
		while(!q[k].empty()) {
			int u = q[k].front(); q[k].pop();
			vector<int> & adj = k == 0 ? adjList[u] : revAdj[u];
			for(int i=0; i<(int)adj.size(); i++) {
				int v = adj[i];
				if (dist[k][v] > dist[k][u] + 1) {
					dist[k][v] = dist[k][u] + 1;
					q[k].push(v);
				}
			}
		}
	}
	
	int ans = INF;
	for(int u=1; u<=N; u++) {
		//printf("%d %d %d\n", dist[0][u], dist[1][u], dist[2][u]);
		ans = min(ans, dist[0][u]+dist[1][u]+dist[2][u]);
	}
	if (ans >= INF) printf("impossible\n");
	else printf("%d\n", ans);
	return 0;
}
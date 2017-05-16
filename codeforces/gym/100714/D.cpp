#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define INF (1LL << 60)

typedef long long ll;
typedef pair<ll, int> ii;
vector<ii> adjList[MAXN];
ll dist[MAXN];
int N, C, M, own[MAXN], L[MAXN];
 
ll dijkstra()
{
	for(int i=1; i<=2*N; i++) dist[i] = INF, own[i] = -1;
	set<pair<int, int> > nodes;
	for(int i=1, j; i<=C; i++) {
		j = L[i];
		if (dist[j] < INF) return 0;
		dist[j] = 0;
		own[j] = i;
		//printf("dist[%d]=%I64d, own[%d]=%d\n", j, dist[j], j, own[j]);
		nodes.insert(ii(0, j));
	}
	while(!nodes.empty()){
		int u = nodes.begin()->second, v;
		nodes.erase(nodes.begin());
		int un = u > N ? u-N : u;
		for(int i=0; i<(int)adjList[un].size(); i++){
			int vn = adjList[un][i].second;
			ll w = adjList[un][i].first;
			
			ll dv = dist[u] + w;
			int v1 = vn, v2 = vn+N;
			
			if (dist[v2] < dist[v1]) swap(v1, v2);
			if (dv < dist[v1]) {
				if (own[v1] == own[u]) v = v1;
				else v = v2;
			}
			else if (dv < dist[v2]){
				if (own[v1] == own[u]) v = -1;
				else v = v2;
			}
			else v = -1;
			
			if (v >= 0){
				if (dist[v] < INF){
					nodes.erase(ii(dist[v], v));
				}
				dist[v] = dv;
				own[v] = own[u];
				//printf("dist[%d]=%I64d, own[%d]=%d\n", v, dist[v], v, own[v]);
				nodes.insert(ii(dist[v], v));
			}
		}
	}
	ll ans = INF;
	for(int i=1; i<=N; i++) {
		if (dist[i] < INF && dist[i+N] < INF)
			ans = min(max(dist[i], dist[i+N]), ans);
	}
	for(int u=1, v; u<=N; u++) {
		for(int i=0; i<(int)adjList[u].size(); i++) {
			int u1 = u, u2 = u+N;
			v = adjList[u][i].second;
			ll w = adjList[u][i].first;
			int v1 = v, v2 = v+N;
			if ((own[u1] == own[v1] || own[u1] == own[v2])
				&& (own[u2] == own[v1] || own[u2] == own[v2])) {
				if (own[u1] == own[v2]) swap(v1, v2);
				if (dist[u1] > dist[v1]) swap(u1, v1);
				if (dist[u2] > dist[v2]) swap(u2, v2);
				ll s = abs(dist[u1] - dist[u2]);
				ll l = w - s;
				ans = min(ans, max(dist[u1], dist[u2]) + l/2);
			}
		}
	}
	return ans;
}

int main() {
	ll w;
	int u, v;
	scanf("%d %d %d", &C, &N, &M);
	for(int i=1; i<=C; i++) scanf("%d", &L[i]);
	for(int i=1; i<=M; i++) {
		scanf("%d %d %I64d", &u, &v, &w);
		adjList[u].push_back(ii(6*w, v));
		adjList[v].push_back(ii(6*w, u));
	}
	printf("%I64d\n", dijkstra());
	return 0;
}
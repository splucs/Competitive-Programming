#include <vector>
#include <queue>
#include <cstdio>
#include <cstring>
#define INF (1<<30)
#define MAXN 5009
using namespace std;

vector<int> adjList[MAXN];
typedef long long ll;
ll cap[MAXN][MAXN];
int dist[MAXN], work[MAXN], N, M;

ll dfs(int u, ll f, int s, int t) {
	if (u == t) return f;
	int v; ll df;
	for (int &i = work[u]; i<(int)adjList[u].size(); i++) {
		v = adjList[u][i];
		if (cap[u][v] <= 0) continue;
		if (dist[v] == dist[u] + 1) {
			df = dfs(v, min(f, cap[u][v]), s, t);
			if (df > 0) {
				cap[u][v] -= df;
				cap[v][u] += df;
				return df;
			}
		}
	}
	return 0;
}

//O(EV^2)
ll dinic(int s, int t) {
	ll result = 0, f;
	int u, v;
	while (true) {
		memset(&dist, -1, sizeof dist);
		dist[s] = 0;
		queue<int> q; q.push(s);
		while(!q.empty()) {
			u = q.front(); q.pop();
			for (int i = 0; i<(int)adjList[u].size(); i++) {
				v = adjList[u][i];
				if (dist[v] < 0 && cap[u][v] > 0) {
					dist[v] = dist[u] + 1;
					q.push(v);
				}
			}
		}
		if(dist[t] < 0) break;
		memset(&work, 0, sizeof work);
		while (f = dfs(s, INF, s, t), f>0) result += f;
	}
	return result;
}

int main(){
	scanf("%d %d", &N, &M);
	int u, v, f;
	memset(&cap, 0ll, sizeof cap);
	for(int i=0; i<M; i++){
		scanf("%d %d %d", &u, &v, &f);
		if (u == v) continue;
		if (cap[u][v]==0 && cap[v][u]==0){
			adjList[u].push_back(v);
			adjList[v].push_back(u);
		}
		cap[u][v] += f;
		cap[v][u] += f;
	}
	printf("%lld\n", dinic(1, N));
	return 0;
}
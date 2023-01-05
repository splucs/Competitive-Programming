#include <bits/stdc++.h>
#define INF (1<<30)
#define MAXN 103000
#define MAXM 900000
using namespace std;

int N, M, ned, first[MAXN];
int cap[MAXM], to[MAXM], nxt[MAXM], dist[MAXN];

void init(){
   memset(first, -1, sizeof first);
   ned = 0;
}

void add(int u, int v, int f){
    to[ned] = v, cap[ned] = f;
    nxt[ned] = first[u];
    first[u] = ned++;
    
    to[ned] = u, cap[ned] = 0;
    nxt[ned] = first[v];
    first[v] = ned++;
}

int dfs(int u, int f, int s, int t) {
	if (u == t) return f;
	if (f <= 0) return 0;
	printf("visit %d, dist[%d] = %d\n", u, u, dist[u]);
	int v, df;
	for(int e = first[u]; e!=-1; e = nxt[e]){
        v = to[e];
		if (dist[v] == dist[u] + 1 && cap[e] > 0) {
			df = dfs(v, min(f, cap[e]), s, t);
			if (df > 0) {
				cap[e] -= df;
				cap[e^1] += df;
				return df;
			}
		}
	}
	return 0;
}

bool bfs(int s, int t){
	int u, v;
	memset(&dist, -1, sizeof dist);
	dist[s] = 0;
	queue<int> q; q.push(s);
	while (!q.empty()) {
		u = q.front(); q.pop();
		for(int e = first[u]; e!=-1; e = nxt[e]){
			v = to[e];
			if (dist[v] < 0 && cap[e] > 0) {
				dist[v] = dist[u] + 1;
				q.push(v);
			}
		}
	}
	return dist[t] >= 0;
}

//O(EV^2)
int dinic(int s, int t) {
	int result = 0, f;
	while (bfs(s, t)) {
		while (f = dfs(s, INF, s, t)) result += f;
	}
	return result;
}

#include <cstdio>

int main()
{
	int u, v;
	while(scanf("%d %d", &N, &M) != EOF) {
		init();
		for(int j=0; j<M; j++) {
			scanf("%d %d", &u, &v);
			add(u, v, 1);
			add(v, u, 1);
		}
		int s = 5, t = 3;
		printf("computing flow from %d to %d\n", s, t);
		int flow = dinic(s, t);
		printf("flow = %d\n", flow);
	}
	return 0;
}
#include <bits/stdc++.h>
#define INF (1<<30)
#define MAXN 5009
#define MAXM 900000
using namespace std;

int ned, first[MAXN], work[MAXN];
int cap[MAXM], to[MAXM], nxt[MAXM], dist[MAXN];

void init() {
   memset(first, -1, sizeof first);
   ned = 0;
}

void add(int u, int v, int f) {
    to[ned] = v, cap[ned] = f;
    nxt[ned] = first[u];
    first[u] = ned++;
    
    to[ned] = u, cap[ned] = 0;
    nxt[ned] = first[v];
    first[v] = ned++;
}

int dfs(int u, int f, int s, int t) {
	if (u == t) return f;
	int v, df;
	for(int & e = work[u]; e!=-1; e = nxt[e]) {
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

bool bfs(int s, int t) {
	int u, v;
	memset(&dist, -1, sizeof dist);
	dist[s] = 0;
	queue<int> q; q.push(s);
	while (!q.empty()) {
		u = q.front(); q.pop();
		for(int e = first[u]; e!=-1; e = nxt[e]) {
			v = to[e];
			if (dist[v] < 0 && cap[e] > 0) {
				dist[v] = dist[u] + 1;
				q.push(v);
			}
		}
	}
	return dist[t] >= 0;
}

int dinic(int s, int t) {
	int result = 0, f;
	while (bfs(s, t)) {
		memcpy(work, first, sizeof work);
		while (f = dfs(s, INF, s, t)) result += f;
	}
	return result;
}

int main() {
	
	int N, M;
	while(scanf("%d %d", &N, &M), N || M) {
		
		init();
		int s = 0;
		int t = N+1;
		
		for(int i=1, b; i<=N; i++) {
			scanf("%d", &b);
			if (b == 1) add(i, t, 1);
			else add(s, i, 1);
		}
		for(int j=1, u, v; j<=M; j++) {
			scanf("%d %d", &u, &v);
			add(u, v, 1);
			add(v, u, 1);
		}
		
		printf("%d\n", dinic(s, t));
	}

	return 0;
}
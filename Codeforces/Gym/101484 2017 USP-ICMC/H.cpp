#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009
#define MAXM 10009
#define INF (1<<30)

int ned, first[MAXN], work[MAXN];
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
	int v, df;
	for(int & e = work[u]; e!=-1; e = nxt[e]){
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

int dinic(int s, int t) {
	int result = 0, f;
	while (bfs(s, t)) {
		memcpy(work, first, sizeof work);
		while (f = dfs(s, INF, s, t)) result += f;
	}
	return result;
}

int K, N, A, B, arr[MAXN], reach[MAXN][2];

int main() {
	scanf("%d %d %d %d", &K, &N, &A, &B);
	for(int i=0, x; i<A; i++) {
		scanf("%d", &x);
		reach[x][0] = 1;
	}
	for(int i=0, x; i<B; i++) {
		scanf("%d", &x);
		reach[x][1] = 1;
	}
	init();
	for(int i=1; i<=N; i++) {
		scanf("%d", &arr[i]);
	}
	for(int j=1; j<=K; j++) {
		if (reach[j][1] == reach[j][0]) continue;
		if (reach[j][0]) add(0, j, INF);
		if (reach[j][1]) add(j, N+1, INF);
	}
	int ans = 0;
	for(int i=1, g; i<=N-1; i++) {
		scanf("%d", &g);
		ans += g;
		add(arr[i], arr[i+1], g);
		add(arr[i+1], arr[i], g);
	}
	ans -= dinic(0, N+1);
	printf("%d\n", ans);
	return 0;
}
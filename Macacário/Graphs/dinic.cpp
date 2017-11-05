#include <queue>
#include <cstring>
#define INF (1<<30)
#define MAXN 103000
#define MAXM 900000
using namespace std;

/*
 * Dinic's Algorithm - O(EV^2)
 */

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

/*
 * Codeforces 100783D
 */

#include <cstdio>

int main() {
	int u, v, N, M;
	init();
	memset(&cap, 0, sizeof cap);
	scanf("%d %d", &N, &M);
	for(int i=1; i<=N; i++){
		add(0, i, 1);
		add(i+N, 2*N+1, 1);
	}
	for(int i=0; i<M; i++){
		scanf("%d %d", &u, &v);
		u++; v++;
		add(u, v+N, 1);
	}
	int MF = dinic(0, 2*N+1);
	//printf("MF = %d\n", MF);
	if (MF == N) printf("YES\n");
	else printf("NO\n");
	return 0;
}
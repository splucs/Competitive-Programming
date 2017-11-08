#include <bits/stdc++.h>
#define INF (1<<30)
#define MAXN 103000
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

#define MAXQ 109
int N, Q, S, q[MAXQ], in[MAXQ][MAXQ], out[MAXQ][MAXQ], data[MAXQ];

int main() {
	init();
	int k = 0;
	int st = k++;
	int en = k++;
	
	scanf("%d %d %d", &N, &Q, &S);
	for(int s=1; s<=S; s++) {
		scanf("%d", &q[s]);
	}
	for(int i=1, c; i<=Q; i++) {
		scanf("%d", &c);
		for(int n=1; n<=N; n++) {
			in[i][n] = k++;
			out[i][n] = k++;
			add(in[i][n], out[i][n], c);
			if (n > 1) add(out[i][n-1], in[i][n], c);
		}
	}
	int sum = 0;
	for(int n=1, c; n<=N; n++) {
		scanf("%d", &c);
		data[n] = k++;
		add(data[n], en, c);
		for(int i=1; i<=Q; i++) {
			add(out[i][n], data[n], INF);
		}
		
		for(int s=1, a; s<=S; s++) {
			scanf("%d", &a);
			sum += a;
			add(st, in[q[s]][n], a);
		}
	}
	
	int mf = dinic(st, en);
	//printf("mf = %d\n", mf);
	
	if (sum == mf) printf("possible\n");
	else printf("impossible\n");
	return 0;
}
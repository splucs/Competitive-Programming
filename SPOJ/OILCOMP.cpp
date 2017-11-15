#include <bits/stdc++.h>
#define INF (1<<30)
#define MAXN 103009
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

int pos[20][20], N, M;
int di[4] = {0, 1, 0, -1};
int dj[4] = {1, 0, -1, 0};

bool valid(int i, int j) {
	return i >= 0 && j >= 0 && i < N && j < M;
}

int main() {
	int T;
	scanf("%d", &T);
	for(int caseNo = 1; caseNo <= T; caseNo++) {
		scanf("%d %d", &M, &N);
		
		init();
		int k = 0, sum = 0;
		int s = k++;
		int t = k++;
		for(int i=0, x; i<N; i++) {
			for(int j=0; j<M; j++) {
				pos[i][j] = k++;
				scanf("%d", &x);
				sum += x;
				if ((i+j)%2 == 0) add(s, pos[i][j], x);
				else add(pos[i][j], t, x);
			}
		}
		
		for(int i=0; i<N; i++) {
			for(int j=0; j<M; j++) {
				for(int k=0; k<4; k++) {
					int ni = i + di[k];
					int nj = j + dj[k];
					if (!valid(ni, nj)) continue;
					if ((i+j)%2 == 0) add(pos[i][j], pos[ni][nj], INF);
					else add(pos[ni][nj], pos[i][j], INF);
				}
			}
		}
		
		printf("Case %d: %d\n", caseNo, sum - dinic(s, t));
	}
	
	return 0;
}
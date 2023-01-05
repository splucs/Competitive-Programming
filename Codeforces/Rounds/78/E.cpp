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

#define MAXB 19
#define MAXT 69

char board[MAXB][MAXB];
int mint[MAXB][MAXB], N, T;
int di[4] = {0, 1, 0, -1};
int dj[4] = {1, 0, -1, 0};
int pos[MAXB][MAXB][MAXT], capsule[MAXB][MAXB];

bool isNumber(char c) {
	return c >= '0' && c <= '9';
}

bool valid(int i, int j) {
	if (i < 0 || j < 0 || i >= N || j >= N) return false;
	return isNumber(board[i][j]);
}

int main() {
	scanf("%d %d", &N, &T);
	
	queue<int> qi, qj;
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			scanf(" %c", &board[i][j]);
			mint[i][j] = INF;
			if (board[i][j] == 'Z') {
				qi.push(i); qj.push(j);
				mint[i][j] = 0;
			}
		}
	}
	
	while(!qi.empty()) {
		int i = qi.front(); qi.pop();
		int j = qj.front(); qj.pop();
		for(int k=0; k<4; k++) {
			int ni = i + di[k];
			int nj = j + dj[k];
			if (!valid(ni, nj)) continue;
			if (mint[ni][nj] == INF) {
				mint[ni][nj] = mint[i][j] + 1;
				qi.push(ni); qj.push(nj);
			}
		}
	}
	
	init();
	int k = 0;
	int st = k++;
	int en = k++;
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			for(int t=0; t<MAXT; t++) {
				pos[i][j][t] = k++;
			}
		}
	}
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			for(int t=0; t+1<MAXT && t<mint[i][j]; t++) {
				for(int k=0; k<4; k++) {
					int ni = i + di[k];
					int nj = j + dj[k];
					if (!valid(ni, nj)) continue;
					add(pos[i][j][t], pos[ni][nj][t+1], INF);
				}
				add(pos[i][j][t], pos[i][j][t+1], INF);
			}
			if (isNumber(board[i][j])) {
				int n = board[i][j] - '0';
				add(st, pos[i][j][0], n);
			}
		}
	}
	
	/*for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			printf("%d ", mint[i][j]);
		}
		printf("\n");
	}*/
	
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			scanf(" %c", &board[i][j]);
			if (isNumber(board[i][j])) {
				capsule[i][j] = k++;
				int n = board[i][j] - '0';
				add(capsule[i][j], en, n);
				for(int t=0; t<MAXT && t<=T && t<=mint[i][j]; t++) {
					add(pos[i][j][t], capsule[i][j], INF);
				}
			}
		}
	}
	
	printf("%d\n", dinic(st, en));
	
	return 0;
}
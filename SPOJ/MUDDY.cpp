#include <bits/stdc++.h>
#define INF (1<<30)
#define MAXN 103000
#define MAXM 900000
using namespace std;

/*
 * Edmonds-Karp's Algorithm - O(VE^2)
 */

int ned, prv[MAXN], first[MAXN];
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

int augment(int v, int minEdge, int s) {
	int e = prv[v];
	if (e == -1) return minEdge;
	int f = augment(to[e^1], min(minEdge, cap[e]), s);
	cap[e] -= f;
	cap[e^1] += f;
	return f;
}

bool bfs(int s, int t){
	int u, v;
	memset(&dist, -1, sizeof dist);
	dist[s] = 0;
	queue<int> q; q.push(s);
	memset(&prv, -1, sizeof prv);
	while (!q.empty()) {
		u = q.front(); q.pop();
		if (u == t) break;
		for(int e = first[u]; e!=-1; e = nxt[e]){
			v = to[e];
			if (dist[v] < 0 && cap[e] > 0) {
				dist[v] = dist[u] + 1;
				q.push(v);
				prv[v] = e;
			}
		}
	}
	return dist[t] >= 0;
}

int edmondskarp(int s, int t){
	int result = 0;
	while (bfs(s, t)) {
		result += augment(t, INF, s);
	}
	return result;
}

#define MAXB 59
int ver[MAXB][MAXB], hor[MAXB][MAXB];
char board[MAXB][MAXB];

int main(){
	int T, N, M;
	scanf("%d", &T);
	while(T --> 0) {
		scanf("%d %d", &N, &M);
		int cnt = 0;
		init();
		int s = cnt++;
		int t = cnt++;
		for(int i=0; i<N; i++) {
			for(int j=0; j<M; j++) {
				scanf(" %c", &board[i][j]);
				if (board[i][j] == '.') {
					ver[i][j] = hor[i][j] = -1;
				}
				else {
					if (i > 0 && ver[i-1][j] != -1) ver[i][j] = ver[i-1][j];
					else {
						ver[i][j] = cnt++;
						add(s, ver[i][j], 1);
					}
					if (j > 0 && hor[i][j-1] != -1) hor[i][j] = hor[i][j-1];
					else {
						hor[i][j] = cnt++;
						add(hor[i][j], t, 1);
					}
					add(ver[i][j], hor[i][j], 1);
				}
			}
		}
		printf("%d\n", edmondskarp(s, t));
	}
	return 0;
}
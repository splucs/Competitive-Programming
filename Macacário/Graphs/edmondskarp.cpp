#include <queue>
#include <cstring>
#define INF 0x3f3f3f3f
#define MAXN 103000
#define MAXM 900000
using namespace std;

/*
 * Edmonds-Karp's Algorithm - O(VE^2)
 */

int ned, prv[MAXN], first[MAXN];
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

int augment(int v, int minEdge, int s) {
	int e = prv[v];
	if (e == -1) return minEdge;
	int f = augment(to[e^1], min(minEdge, cap[e]), s);
	cap[e] -= f;
	cap[e^1] += f;
	return f;
}

bool bfs(int s, int t) {
	int u, v;
	memset(&dist, -1, sizeof dist);
	dist[s] = 0;
	queue<int> q; q.push(s);
	memset(&prv, -1, sizeof prv);
	while (!q.empty()) {
		u = q.front(); q.pop();
		if (u == t) break;
		for(int e = first[u]; e!=-1; e = nxt[e]) {
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

int edmondskarp(int s, int t) {
	int result = 0;
	while (bfs(s, t)) {
		result += augment(t, INF, s);
	}
	return result;
}

/*
 *	Codeforces 101128F
 */
#include <cstdio>

int main() {
	int N, M, R, C, A, B, pos[60][60];
	char c;
	scanf("%d %d %d %d", &R, &C, &A, &B);
	init();
	memset(&cap, 0, sizeof cap);
	N = R*C+2;
	for(int i=0, k=1; i<R; i++) {
		for(int j=0; j<C; j++) pos[i][j] = k++;
	}
	for(int i=0; i<R; i++) {
		for(int j=0; j<C; j++) {
			scanf(" %c", &c);
			if (c == '.') add(0, pos[i][j], B);
			else add(pos[i][j], N-1, B);
			if (i < R-1) {
				add(pos[i][j], pos[i+1][j], A);
				add(pos[i+1][j], pos[i][j], A);
			}
			if (j < C-1) {
				add(pos[i][j], pos[i][j+1], A);
				add(pos[i][j+1], pos[i][j], A);
			}
		}
	}
	printf("%d\n", edmondskarp(0, N-1));
	return 0;
}
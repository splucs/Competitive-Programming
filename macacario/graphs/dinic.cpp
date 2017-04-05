#include <vector>
#include <queue>
#include <cstdio>
#include <cstring>
#define INF (1<<30)
#define MAXN 2509
using namespace std;

vector<int> adjList[MAXN];
int cap[MAXN][MAXN], dist[MAXN], work[MAXN], N, M;

void add(int u, int v, int c){
	if (cap[u][v] == 0 && cap[v][u] == 0){
		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}
	cap[u][v] += c;
}

int dfs(int u, int f, int s, int t) {
	if (u == t) return f;
	int v, df;
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

bool bfs(int s, int t){
	int u, v;
	memset(&dist, -1, sizeof dist);
	dist[s] = 0;
	queue<int> q; q.push(s);
	while (!q.empty()) {
		u = q.front(); q.pop();
		for(int i = 0; i<(int)adjList[u].size(); i++){
			v = adjList[u][i];
			if (dist[v] < 0 && cap[u][v] > 0) {
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
		memset(&work, 0, sizeof work);
		while (f = dfs(s, INF, s, t)) result += f;
	}
	return result;
}

/*
 *	Codeforces 101128F
 */

int main(){
	int R, C, A, B, pos[60][60];
	char c;
	scanf("%d %d %d %d", &R, &C, &A, &B);
	memset(&cap, 0, sizeof cap);
	N = R*C+2;
	for(int i=0, k=1; i<R; i++){
		for(int j=0; j<C; j++) pos[i][j] = k++;
	}
	for(int i=0; i<R; i++){
		for(int j=0; j<C; j++){
			scanf(" %c", &c);
			if (c == '.') add(0, pos[i][j], B);
			else add(pos[i][j], N-1, B);
			if (i < R-1){
				add(pos[i][j], pos[i+1][j], A);
				add(pos[i+1][j], pos[i][j], A);
			}
			if (j < C-1){
				add(pos[i][j], pos[i][j+1], A);
				add(pos[i][j+1], pos[i][j], A);
			}
		}
	}
	printf("%d\n", dinic(0, N-1));
	return 0;
}
#include <bits/stdc++.h>
using namespace std;
#define MAXN 509

bool vis[MAXN], inqueue[MAXN], possible, pres[MAXN];
vector<int> adjList[MAXN];
int col[MAXN];

void bfs(int w) {
	//printf("bfs %d\n", w);
	if (adjList[w].empty()) return;
	int u = adjList[w][0], v;
	queue<int> q;
	memset(&pres, false, sizeof pres);
	memset(&inqueue, false, sizeof inqueue);
	for(int i=0; i<(int)adjList[w].size(); i++) {
		v = adjList[w][i];
		pres[v] = true;
		if(col[v] != 0) {
			u = v;
			q.push(u);
			inqueue[u] = true;
		}
	}
	if (col[u] == 0) col[u] = 4-col[w];
	while(!q.empty()) {
		u = q.front();
		//printf("bfs %d %d\n", w, u);
		q.pop();
		for(int i=0; i<(int)adjList[u].size(); i++) {
			v = adjList[u][i];
			if (!pres[v] || inqueue[v]) continue;
			inqueue[v] = true;
			q.push(v);
			if (col[v] != 0 && col[v] != 6 - col[u] - col[w]) possible = false;
			col[v] = 6 - col[u] - col[w];
		}
	}
}

void dfs(int u) {
	if (vis[u]) return;
	vis[u] = true;
	//printf("dfs %d\n", u);
	bfs(u);
	for(int i=0; i<(int)adjList[u].size(); i++) {
		int v = adjList[u][i];
		if (col[v] == col[u]) possible = false;
		dfs(v);
	}
}

int main() {
	freopen("mayors.in", "r", stdin);
	freopen("mayors.out", "w", stdout);
	
	int N, M, u, v;
	scanf("%d %d", &N, &M);
	for(int i=0; i<M; i++) {
		scanf("%d %d", &u, &v);
		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}
	memset(&col, 0, sizeof col);
	col[1] = 1;
	possible = true;
	dfs(1);
	if (possible) {
		printf("Plan OK\n");
		for(int i=1; i<=N; i++) {
			if (col[i] == 1) printf("R");
			if (col[i] == 2) printf("G");
			if (col[i] == 3) printf("B");
		}
	}
	else printf("Plan failed\n");
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}
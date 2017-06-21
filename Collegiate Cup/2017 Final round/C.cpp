#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define UNVISITED -1

int num[MAXN], vis[MAXN], component[MAXN], N, M, low[MAXN], counter, root, numSCC;
int size[MAXN];
stack<int> S;
vector<int> adjList[MAXN], adjC[MAXN];
set<int> adjCompS[MAXN];

void dfs(int u) {
	low[u] = num[u] = counter++;
	S.push(u);
	vis[u] = 1;
	int v;
	for (int j = 0; j < (int)adjList[u].size(); j++) {
		v = adjList[u][j];
		if (num[v] == UNVISITED) dfs(v);
		if (vis[v]) low[u] = min(low[u], low[v]);
	}
	if (low[u] == num[u]) {
		while (true) {
			v = S.top(); S.pop(); vis[v] = 0;
			component[v] = numSCC;
			if (u == v) break;
		}
		numSCC++;
	}
}

void tarjan(){
	counter = numSCC = 0;
	memset(&num, UNVISITED, sizeof num);
	memset(&vis, 0, sizeof vis);
	memset(&low, 0, sizeof low);
	for (int i = 0; i < N; i++){
		if (num[i] == UNVISITED)
			dfs(i);
	}
}

vector<int> toposort;	//Ordem reversa!

void ts(int u) {
	vis[u] = true;
	for (int j = 0, v; j < (int)adjC[u].size(); j++) {
		v = adjC[u][j];
		if (!vis[v]) ts(v);
	}
	toposort.push_back(u);
}

int dp[MAXN];

int main(){
	scanf("%d %d", &N, &M);
	for(int i=0, u, v; i<M; i++){
		scanf("%d %d", &u, &v);
		u--; v--;
		adjList[u].push_back(v);
	}
	tarjan();
	memset(&size, 0, sizeof size);
	for(int u=0, v; u<N; u++){
		size[component[u]]++;
		for(int i=0; i<(int)adjList[u].size(); i++) {
			v = adjList[u][i];
			adjCompS[component[u]].insert(component[v]);
		}
	}
	for(int u=0, v; u<numSCC; u++){
		for(set<int>::iterator it = adjCompS[u].begin(); it != adjCompS[u].end(); it++){
			adjC[u].push_back(*it);
		}
	}
	memset(&vis, 0, sizeof vis);
	for(int u=0; u<numSCC; u++) {
		if (!vis[u]) ts(u);
	}
	int ans = 0;
	for(int i=0, u, v; i<numSCC; i++){
		u = toposort[i];
		dp[u] = 0;
		for(int j=0; j<(int)adjC[u].size(); j++) {
			v = adjC[u][j];
			dp[u] = max(dp[u], dp[v]);
		}
		dp[u] += size[u];
		ans = max(ans, dp[u]);
	}
	int cnt = 0;
	for(int i=0; i<N; i++){
		if (dp[component[i]] == ans) cnt++;
	}
	printf("%d %d\n", ans, cnt);
	return 0;
}
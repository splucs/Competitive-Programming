#include <bits/stdc++.h>
using namespace std;
#define MAXN 10009

typedef pair<int, bool> ii;
vector<ii> adjList[MAXN];
bool vis[MAXN];
int N, M, K;

bool checkCycle(int s, int t) {
	memset(&vis, false , sizeof vis);
	stack<int> dfs;
	dfs.push(s);
	vis[s] = true;
	while(!dfs.empty()) {
		int u = dfs.top();
		dfs.pop();
		if (u == t) return true;
		for(int i=0; i<(int)adjList[u].size(); i++) {
			int v = adjList[u][i].first;
			if (adjList[u][i].second && !vis[v]) {
				vis[v] = true;
				dfs.push(v);
			}
		}
	}
	return false;
}

void deactivateEdge(int u, int v) {
	for(int i=0; i<(int)adjList[u].size(); i++) {
		if (adjList[u][i].first == v)
			adjList[u][i].second = false;
	}
}

void activateEdge(int u, int v) {
	for(int i=0; i<(int)adjList[u].size(); i++) {
		if (adjList[u][i].first == v)
			adjList[u][i].second = true;
	}
}

int main() {
	int T;
	scanf("%d", &T);
	for(int cases = 1; cases<=T; cases++) {
		scanf("%d %d %d", &N, &M, &K);
		for(int i=0; i<N; i++) adjList[i].clear();
		for(int j=0, u, v; j<M; j++) {
			scanf("%d %d", &u, &v);
			adjList[u].push_back(ii(v, true));
			adjList[v].push_back(ii(u, true));
		}
		int ans = 0;
		for(int u=0; u<K; u++) {
			for(int i=0; i<(int)adjList[u].size(); i++) {
				int v = adjList[u][i].first;
				if (!adjList[u][i].second) continue;
				deactivateEdge(v, u);
				adjList[u][i].second = false;
				if (checkCycle(u, v)) {
					ans++;
				}
				else {
					activateEdge(v, u);
					adjList[u][i].second = true;
				}
			}
		}
		printf("Case #%d: %d\n", cases, ans);
	}
	return 0;
}
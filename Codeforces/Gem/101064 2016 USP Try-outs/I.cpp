#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define UNVISITED 0
#define EXPLORING 1
#define DONE 2

int par[MAXN], num[MAXN], cnt;
bool usedpar[MAXN];
vector<int> adjList[MAXN];
vector<int> ans1, ans2, ans3;

void dfs(int u) {
	num[u] = EXPLORING;
	for(int i=0; i<(int)adjList[u].size(); i++) {
		int v = adjList[u][i];
		if (num[v] == UNVISITED) {
			par[v] = u;
			dfs(v);
		}
	}
	int last = -1;
	for(int i=0; i<(int)adjList[u].size(); i++) {
		int v = adjList[u][i];
		if (num[v] == DONE) {
			if (par[v] == u && usedpar[v]) continue;
			if (par[v] != u) continue;
		}
		if (v == par[u]) continue;
		
		if (last == -1) last = v;
		else {
			ans1.push_back(last);
			ans2.push_back(u);
			ans3.push_back(v);
			last = -1;
		}
	}
	
	if (last != -1 && par[u] != -1) {
		usedpar[u] = true;
		ans1.push_back(last);
		ans2.push_back(u);
		ans3.push_back(par[u]);
	}
	else usedpar[u] = false;
	
	num[u] = DONE;
	
}

int main() {
	int N, M, u, v;
	scanf("%d %d", &N, &M);
	memset(&num, 0, sizeof num);
	while(M --> 0) {
		scanf("%d %d", &u, &v);
		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}
	for(int i=1; i<=N; i++) {
		if (num[i] == UNVISITED) {
			par[i] = -1;
			dfs(i);
		}
	}
	printf("%u\n", ans1.size());
	for(int i=0; i<(int)ans1.size(); i++) {
		printf("%d %d %d\n", ans1[i], ans2[i], ans3[i]);
	}
	return 0;
}
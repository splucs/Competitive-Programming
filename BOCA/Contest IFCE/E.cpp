#include <bits/stdc++.h>
using namespace std;
#define MAXN 10009
#define INF (1<<30)

int N, X, V[MAXN], s[MAXN];
vector<int> adjList[MAXN];
vector<int> ans[MAXN];
/*
void merge(vector<int> & v1, vector<int> & v2) {
	int lim = min((int)(v1.size()+v2.size()), X+1);
	for(int i=0; i<lim; i++) {
		s[i] = -INF;
		for(int j=max(0, i+1-((int)v2.size())); j<min(i+1, (int)v1.size()); j++) {
			s[i] = max(s[i], v1[j] + v2[i-j]);
		}
		//printf(" s[%d]=%d", i, s[i]);
	}
	//printf("\n");
	v1.resize(lim);
	for(int i=0; i<lim; i++) {
		v1[i] = s[i];
	}
}
*/
void merge(vector<int> & v1, vector<int> & v2) {
	int lim = min((int)(v1.size()+v2.size()), X+1);
	for(int i=0; i<=X; i++) {
		s[i] = -INF;
		for(int j=0; j<=i; j++) {
			s[i] = max(s[i], v1[j] + v2[i-j]);
		}
		//printf(" s[%d]=%d", i, s[i]);
	}
	//printf("\n");
	for(int i=0; i<=X; i++) {
		v1[i] = s[i];
	}
}
void dfs(int u, int p) {
	ans[u].assign(X+1, -INF);
	ans[u][0] = 0;
	for(int i=0; i<(int)adjList[u].size(); i++) {
		int v = adjList[u][i];
		if (v == p) continue;
		dfs(v, u);
		//printf("merging %d into %d", v, u);
		merge(ans[u], ans[v]);
	}
	ans[u][1] = max(V[u], ans[u][1]);
	/*printf("node %d:", u);
	for(int i=0; i<(int)ans[u].size(); i++) {
		printf("  %d: %d", i, ans[u][i]);
	}
	printf("\n");*/
}

int main() {
	int u, v;
	/*N = 10000;
	X = 100;
	for(u=2; u<=N; u++) {
		v = u/2;
		adjList[u].push_back(v);
		adjList[v].push_back(u);
		V[u] = u;
	}
	V[1] = 1;*/
	scanf("%d %d", &N, &X);
	for(int i=1; i<=N; i++) scanf("%d", &V[i]);
	for(int i=1; i<N; i++) {
		scanf("%d %d", &u, &v);
		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}
	dfs(1, -1);
	if ((int)ans[1].size() <= X || ans[1][X] < -1000000) printf("impossivel\n");
	else printf("%d\n", ans[1][X]);
	return 0;
}
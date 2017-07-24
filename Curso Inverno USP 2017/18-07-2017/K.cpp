#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

vector<int> adj[MAXN];
double rollopt;
bool isdead[MAXN];
int N, M;

void dfs(int u, int dead, int p) {
	rollopt += 1.0/(dead+1);
	for(int i=0; i<(int)adj[u].size(); i++) {
		int v = adj[u][i];
		if (v == p) continue;
		dfs(v, dead + isdead[u], u);
	}
}

int main() {
	int T, u, v;
	scanf("%d", &T);
	while(T-->0) {
		scanf("%d", &N);
		for(int i=1; i<=N; i++) {
			adj[i].clear();
			isdead[i] = false;
		}
		for(int i=1; i<N; i++) {
			scanf("%d %d", &u, &v);
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		scanf("%d", &M);
		for(int i=0; i<M; i++) {
			scanf("%d", &u);
			isdead[u] = true;
		}
		rollopt = 0.0;
		dfs(1, 0, -1);
		printf("%.6f\n", N - rollopt);
	}
	return 0;
}
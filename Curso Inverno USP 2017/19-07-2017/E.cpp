#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009

typedef pair<int, int> ii;
ii prepos[MAXN];
vector<int> adjList[MAXN];
int N, Q, cnt, coins[MAXN], ev[MAXN], od[MAXN];
bool iseven[MAXN];

void dfs(int u, int p, bool even) {
	prepos[u].first = cnt++;
	ev[u] = coins[u];
	od[u] = 0;
	iseven[u] = even;
	for(int i=0; i<(int)adjList[u].size(); i++) {
		int v = adjList[u][i];
		if (v == p) continue;
		dfs(v, u, !even);
		ev[u] ^= od[v];
		od[u] ^= ev[v];
	}
	prepos[u].second = cnt++;
}

int main() {
	int u, v;
	scanf("%d", &N);
	for(int i=1; i<=N; i++) {
		scanf("%d", &coins[i]);
	}
	for(int i=1; i<N; i++) {
		scanf("%d %d", &u, &v);
		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}
	cnt = 0;
	dfs(1, -1, true);
	scanf("%d", &Q);
	int totxor = od[1], newxor;
	while(Q-->0) {
		scanf("%d %d", &u, &v);
		if (prepos[u].first < prepos[v].first && prepos[u].second > prepos[v].second) printf("INVALID\n");
		else if (iseven[u] == iseven[v]) {
			newxor = totxor^ev[u]^od[u];
			if (newxor != 0) printf("YES\n");
			else printf("NO\n");
		}
		else {
			newxor = totxor;
			if (newxor != 0) printf("YES\n");
			else printf("NO\n");
		}
	}
	return 0;
}
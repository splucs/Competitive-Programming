#include <bits/stdc++.h>
using namespace std;
#define MAXN 209

int N, M;
int adj[MAXN][MAXN], reach[MAXN][MAXN];

void refresh() {
	for(int u = N; u>0; u--) {
		for(int v = 1; v<=N; v++) reach[u][v] = 0;
		reach[u][u] = 1;
		for(int v = 1; v<=N; v++) {
			
		}
	}
}

int main() {
	scanf("%d %d", &N, &M);
	int u, v;
	for(int j=0; j<M; j++) {
		scanf("%d %d", &u, &v);
		adj[u][v] = 1;
	}
}
#include <bits/stdc++.h>
using namespace std;
#define MAXN 60009
#define MAXLOGN 4009
#define INF (1<<30)

int D, par[MAXN], N, cnt;
int mind[MAXN][MAXLOGN];

int find(int i) {
	if (i == par[i]) return i;
	else return par[i] = find(par[i]);
}

void merge(int u, int v) {
	int z = ++cnt;
	u = find(u);
	v = find(v);
	par[u] = z;
	par[v] = z;
	par[z] = z;
	//u leader
	for(int h=0; h<MAXLOGN; h++) mind[z][h] = INF;
	for(int h=1; h<MAXLOGN; h++) {
		if (mind[v][h-1] <= D) {
			mind[z][h] = min(mind[z][h], 1+mind[u][h]);
		}
	}
	//v leader
	for(int h=1; h<MAXLOGN; h++) {
		if (mind[u][h-1] <= D) {
			mind[z][h] = min(mind[z][h], 1+mind[v][h]);
		}
	}
}


int main() {
	int T;
	scanf("%d", &T);
	for(int cases = 1; cases<=T; cases++) {
		scanf("%d %d", &N, &D);
		for(int i=1; i<=N; i++) {
			par[i] = i;
			for(int h=1; h<MAXLOGN; h++) {
				mind[i][h] = 0;
			}
			mind[i][0] = INF;
		}
		cnt = N;
		for(int i=1; i<N; i++) {
			int u, v;
			scanf("%d %d", &u, &v);
			if (D > 1) merge(u, v);
		}
		int ans = N;
		for(int h=1; h<MAXLOGN && D > 1; h++) {
			if (mind[cnt][h] <= D) ans = min(ans, h);
		}
		printf("Case #%d: %d\n", cases, ans);
	}
	return 0;
}
#include <bits/stdc++.h>
using namespace std;
#define MAXN 22
#define MAXS 1009

int N, R, M, dice;
int dp[MAXN][MAXS];
int goal[MAXS], ans[7];
vector<int> adj;

bool backtrack(int i, int prev, int minp) {
	if (i == R) {
		for(int j=0; j<(int)adj.size(); j++) {
			int v = adj[j];
			if (goal[v] != 0) return false;
		}
		return true;
	}
	for(int k=prev, s; k<=50; k++) {
		ans[i] = k;
		bool ok = true;
		for(int j=0, v; j<M; j++) {
			v = adj[j];
			if (v - k >= 0) {
				goal[v] -= dp[N][v-k];
				if (goal[v] < 0) ok = false;
			}
		}
		if (ok && backtrack(i+1, k, minp)) return true;
		for(int j=0, v; j<M; j++) {
			v = adj[j];
			if (v - k >= 0) {
				goal[v] += dp[N][v-k];
			}
		}
		for(int j=0, v; j<M; j++) {
			v = adj[j];
			if (minp+k > v && goal[v] > 0) return false;
		}			
	}
	return false;
}

int main() {
	int f, v, c;
	while(scanf("%d", &N), N) {
		for(int j=0; j<MAXS; j++) dp[0][j] = 0;
		dp[0][0] = 1;
		for(int i=1; i<=N; i++) {
			scanf("%d", &f);
			for(int s=0; s<MAXS; s++) dp[i][s] = 0;
			for(int j=1; j<=f; j++) {
				scanf("%d", &dice);
				for(int s=dice; s<MAXS; s++) dp[i][s] += dp[i-1][s-dice];
			}
		}
		for(int s=0; s<MAXS; s++) {
			goal[s] = -1;
		}
		scanf("%d %d", &R, &M);
		adj.clear();
		for(int i=0; i<M; i++) {
			scanf("%d %d", &v, &c);
			goal[v] = c;
			adj.push_back(v);
		}
		int minp = 0;
		while(dp[N][minp] == 0) minp++;
		if (!backtrack(0, 1, minp)) printf("Impossible\n");
		else {
			printf("Final die face values are");
			for(int i=0; i<R; i++) {
				printf(" %d", ans[i]);
			}
			printf("\n");
		}
	}
	return 0;
}
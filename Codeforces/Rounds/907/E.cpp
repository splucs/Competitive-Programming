#include <bits/stdc++.h>
using namespace std;
#define MAXN 22

int dp[1<<MAXN], A[1<<MAXN], adjMat[MAXN][MAXN], N, M;

int main() {
	scanf("%d %d", &N, &M);
	for(int j = 0; j < M; j++) {
		int u, v;
		scanf("%d %d", &u, &v);
		u--; v--;
		adjMat[u][v] = adjMat[v][u] = 1;
	}
	for(int mask = (1<<N)-1; mask >= 0; mask--) {
		if (mask == (1<<N)-1) {
			dp[mask] = 0;
			A[mask] = -1;
		}
		else if (mask == 0) {
			dp[0] = N+1;
			for(int i = 0; i < N; i++) {
				if (dp[0] > dp[1<<i]) {
					A[0] = i;
					dp[0] = dp[1<<i];
				}
			}
		}
		else {
			dp[mask] = N+1;
			A[mask] = -1;
			for(int i = 0; i < N; i++) {
				if (!(mask & (1<<i))) continue;
				inclick = true;
				for(int j = 0; j < N; j++) {
					if ((mask & (1<<j)) && !adjMat[i][j]) inclick = false;
				}
				if (inclick) {
					dp[mask] = dp[mask | (1<<i)];
					A[mask] = i;
					break;
				}
			}
			if (inclick) continue;

			dp[mask] = N+1;
		}
	}
}
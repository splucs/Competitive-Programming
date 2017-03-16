#include <cstdio>
#define MAXN 1009
#define INF (1LL << 60)

typedef long long ll;

ll dp[MAXN][MAXN], C[MAXN][MAXN];
int A[MAXN][MAXN], N, S;

void knuth() {
	ll cur;
	for (int s = 0; s < N; s++) {
		for (int i = 0, j; i + s<N; i++) {
			j = i + s;
			if (s < S) {	//Caso base
				dp[i][j] = 0;
				A[i][j] = i;
				continue;
			}
			dp[i][j] = INF;
			for (int k = A[i][j - 1]; k <= A[i + 1][j]; k++) {
				cur = C[i][j] + dp[i][k] + dp[k][j];
				if (dp[i][j] > cur) {
					dp[i][j] = cur;
					A[i][j] = k;
				}
			}
		}
	}
}
#include <cstdio>
#include <algorithm>
using namespace std;
#define MAXN 1009
#define MAXK 19
#define INF (1<<30)

int dp[MAXN][MAXK], A[MAXN][MAXK], N, K;

void twopointer() {
	for(int i=0; i<=N; i++) dp[i][0] = INF;
	for(int j=0; j<=K; j++) dp[0][j] = 0, A[0][j] = 1;
	dp[0][0] = 0;
	for(int i=1; i<=N; i++) {
		for(int j=1; j<=K; j++) {
			dp[i][j] = INF;
			for(int k=A[i-1][j]; k<=i; k++) {
				int cur = 1 + max(dp[k-1][j-1], dp[i-k][j]);
				if (dp[i][j] > cur) {
					dp[i][j] = cur;
					A[i][j] = k;
				}
				if (dp[k-1][j-1] > dp[i-k][j]) break;
			}
		}
	}
}

/*
 *	Hacker Earth Eggs and Building
 */

int main() {
	int T, n, k;
	scanf("%d", &T);
	N = 1000;
	K = 10;
	twopointer();
	while(T-->0) {
		scanf("%d %d", &n, &k);
		printf("%d\n", dp[n][k]);
	}
	return 0;
}
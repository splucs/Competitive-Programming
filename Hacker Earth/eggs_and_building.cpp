#include <cstdio>
#include <algorithm>
using namespace std;
#define MAXN 1009
#define MAXK 19
#define INF (1<<30)

int dp[MAXN][MAXK], A[MAXN][MAXK], N, K;

void twopointer() {
	for(int n=0; n<=N; n++) dp[n][0] = INF;
	for(int k=0; k<=K; k++) dp[0][k] = 0, A[0][k] = 1;
	dp[0][0] = 0;
	for(int n=1; n<=N; n++) {
		for(int k=1; k<=K; k++) {
			dp[n][k] = INF;
			for(int j=A[n-1][k]; j<=n; j++) {
				int cur = 1 + max(dp[j-1][k-1], dp[n-j][k]);
				if (dp[n][k] > cur){
					dp[n][k] = cur;
					A[n][k] = j;
				}
				if (dp[j-1][k-1] > dp[n-j][k]) break;
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
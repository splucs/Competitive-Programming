#include <bits/stdc++.h>
using namespace std;
#define MAXN 109
#define MAXM 2009
#define MOD 1000000007

int dp[MAXN][MAXM], sum[MAXN][MAXM], N, C, m, M;

int main() {
	int T;
	scanf("%d", &T);
	while(T --> 0) {
		scanf("%d %d %d %d", &N, &C, &m, &M);
		
		for(int i = N+1; i>0; i--) {
			for(int c=0; c<=C; c++) {
				if (i == N+1) {
					if (c == 0) dp[i][c] = 1;
					else dp[i][c] = 0;
				}
				else {
					/*dp[i][c] = 0;
					for(int l=m; l<=M && c-l>=0; l++) {
						dp[i][c] += dp[i+1][c-l];
					}*/
					if (c < m) dp[i][c] = 0;
					else dp[i][c] = sum[i+1][c-m] - (c-M-1 >= 0 ? sum[i+1][c-M-1] : 0);
				}
				dp[i][c] = (dp[i][c] + MOD) % MOD;
				sum[i][c] = dp[i][c] + (c > 0 ? sum[i][c-1] : 0);
				sum[i][c] %= MOD;
				
				//printf("dp[%d][%d] = %d, ", i, c, dp[i][c]);
				//printf("sum[%d][%d] = %d\n", i, c, sum[i][c]);
			}
		}
		
		printf("%d\n", dp[1][C]);
	}
	
	return 0;
}
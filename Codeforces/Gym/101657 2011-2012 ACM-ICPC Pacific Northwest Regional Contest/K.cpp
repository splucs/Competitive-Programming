#include <bits/stdc++.h>
using namespace std;
#define MAXN 1509
#define MAXLOGN 19
#define MOD 1000000000

int dp[MAXN][MAXLOGN];

int main() {
	int N;
	for(int h = 0; h < MAXLOGN; h++) {
		for(int i = 0; i < MAXN; i++) {
			if (i == 0 && h == 0) {
				dp[i][h] = 1;
				continue;
			}
			if (i == 0 || h == 0) {
				dp[i][h] = 0;
				continue;
			}
			dp[i][h] = 0;
			for(int j = 0; j <= i-1; j++) {
				if (h >= 1) {
					dp[i][h] += (dp[j][h-1]*1ll*dp[i-1-j][h-1])%MOD;
					dp[i][h] %= MOD;
				}
				if (h >= 2) {
					dp[i][h] += (dp[j][h-2]*1ll*dp[i-1-j][h-1])%MOD;
					dp[i][h] %= MOD;
					dp[i][h] += (dp[j][h-1]*1ll*dp[i-1-j][h-2])%MOD;
					dp[i][h] %= MOD;
				}
			}
		}	
	}
	while(scanf("%d", &N) != EOF) {
		int ans = 0;
		for(int h = 1; h < MAXLOGN; h++) {
			ans = (ans + dp[N][h])%MOD;
		}
		printf("%09d\n", ans);
	}
	return 0;
}
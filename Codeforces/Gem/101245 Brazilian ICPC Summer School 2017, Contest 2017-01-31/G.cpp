#include <bits/stdc++.h>
using namespace std;
#define MAXN 32
#define MAXL 1002

int v[MAXN], dp[MAXN][MAXN][MAXN][MAXL];

int main() {
	int n, l;
	while(scanf("%d %d", &l, &n) != EOF) {
		for(int i=0; i<n; i++) {
			scanf("%d", &v[i]);
		}
		sort(v, v+n);
		
		for(int i = n; i>=0; i--) {
			for(int d=0; d<i; d++) {
				for(int u=0; u<MAXN; u++) {
					for(int h = 0; h<=l; h++) {
						if (l-h < v[d]*(u+1)) dp[i][d][u][h] = 0;
						else if (i == n) {
							dp[i][d][u][h] = n;
						}
						else {
							dp[i][d][u][h] = dp[i+1][d][u][h];
							if (h+v[i] <= l) dp[i][d][u][h] = min(dp[i][d][u][h], 1+dp[i+1][d][u+1][h+v[i]]);
						}
					}
				}
			}
		}
		
		int ans = n, cur;
		int sum;
		for(int i = 0; i<n; i++) {
			cur = 0; sum = 0;
			for(int j=0; j<i; j++) {
				cur++;
				sum += v[j];
			}
			if (sum > l) continue;
			cur += dp[i+1][i][cur][sum];
			ans = min(ans, cur);
		}
		
		printf("%d\n", ans);
	}
	return 0;
}
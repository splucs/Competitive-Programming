#include <bits/stdc++.h>
using namespace std;
#define MAXN 900000

int K, N, dp[7][MAXN], len[7], a[7][7];

int code(int c[7], int l) {
	int ans = 0;
	for(int i=0; i<l; i++) {
		ans = (c[i]-1) + ans*7;
	}
	return ans;
}

int bt(const int i, const int j) {
	if (i == K) return 1;
	if (j == len[i]) {
		int mask = code(a[i], len[i]);
		if (dp[i][mask] < 0) {
			dp[i][mask] = bt(i+1, 0);
		}
		return dp[i][mask];
	}
	
	int ans = 0;
	for(int n=1; n<=N; n++) {
		if (i > 0 && n <= a[i-1][j]) continue;
		if (j > 0 && n < a[i][j-1]) continue;
		a[i][j] = n;
		ans += bt(i, j+1);
	}
	return ans;
}

int main() {
	while(scanf(" %d", &K) != EOF) {
		
		for(int i=0; i<K; i++) scanf("%d", &len[i]);
		scanf("%d", &N);
		
		memset(&dp, -1, sizeof dp);
		int ans = bt(0, 0);
		
		printf("%d\n", ans);
	}
	
	return 0;
}
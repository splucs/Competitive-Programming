#include <bits/stdc++.h>
using namespace std;
#define state dp[i][l][n]

int v[39], N, L;
int dp[39][1009][39];

int DP(const int i, const int l, const int n) {
	if (state >= 0) return state;
	if ()
}

int main() {
	scanf("%d %d", &L, &N);
	for(int i=1; i<=N; i++) {
		scanf("%d", &v[i]);
	}
	
	int ans = N;
	for(int d=0; d<=100; d++) {
		ans = min(ans, dp[N][L][d]);
	}
	printf("%d\n", ans);
	return 0;
}
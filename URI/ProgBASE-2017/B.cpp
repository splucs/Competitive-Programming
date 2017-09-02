#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

int dp[MAXN][MAXN], N, arr[MAXN];

int main() {
	while(scanf("%d", &N), N) {
		N *= 2;
		for(int i=0; i<N; i++) scanf("%d", &arr[i]);
		for(int s=0; s<N; s++) {
			for(int i=0, j; i+s<N; i++) {
				j = i+s;
				if (s == 0) dp[i][j] = 0;
				//player 2
				if (s % 2 == 0) {
					dp[i][j] = min(dp[i+1][j], dp[i][j-1]);
				}
				//player 1
				else {
					dp[i][j] = max(dp[i+1][j] + (arr[i] % 2 == 0 ? 1 : 0), dp[i][j-1] + (arr[j] % 2 == 0 ? 1 : 0));
				}
			}
		}
		printf("%d\n", dp[0][N-1]);
	}
	return 0;
}
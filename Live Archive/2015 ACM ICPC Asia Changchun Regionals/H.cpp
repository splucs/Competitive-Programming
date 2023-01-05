#include <bits/stdc++.h>
using namespace std;
#define MAXN 2019
#define INF (1<<30)

int dp[MAXN], f[MAXN];

int main() {
	int T, N;
	scanf("%d", &T);
	while(T-->0) {
		scanf("%d", &N);
		for(int i=1; i<N; i++) {
			scanf("%d", &f[i]);
		}
		int ans = N*f[1];
		for(int i=N-1; i>=1; i--) {
			f[i] -= f[1];
		}
		for(int j=0; j<=N-2; j++) {
			if (j == 0) dp[j] = 0;
			else {
				dp[j] = -INF;
				for(int k=1; k<=j; k++) {
					if (dp[j] < dp[j-k] + f[k+1])
						dp[j] = dp[j-k] + f[k+1];
				}
			}
		}
		printf("%d\n", dp[N-2]+ans);
	}
	return 0;
}
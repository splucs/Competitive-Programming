#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define MAXM 509

int dp[2][2][MAXM];
int p[MAXN], c[MAXN];

int main() {
	int N, K;
	scanf("%d %d", &N, &K);
	for(int i=1; i<=N; i++) scanf("%d", &p[i]);
	for(int i=2; i<=N; i++) scanf("%d", &c[i]);
	for(int k=0; k<=K; k++) {
		dp[N%2][0][k] = 0;
		dp[N%2][1][k] = p[N] + c[N];
	}
	for(int i=N-1; i>=1; i--) {
		for(int k=0; k<=K; k++) {
			if (k > 0) dp[i%2][0][k] = max(dp[(i+1)%2][0][k], dp[(i+1)%2][1][k-1] - p[i]);
			else dp[i%2][0][k] = dp[(i+1)%2][0][k];
			dp[i%2][1][k] = max(dp[(i+1)%2][1][k], dp[i%2][0][k] + p[i] + c[i]);
		}
	}
	printf("%d\n", dp[1][0][K]);
	return 0;
}
#include <bits/stdc++.h>
using namespace std;
#define MAXN 2009
#define MAXD 29

typedef long long ll;
int N, D;
ll dp[MAXN][MAXD], arr[MAXN], sum[MAXN];

ll rnd(ll x) {
	if ((x%10) < 5) x -= (x%10);
	else x += 10 - (x%10);
	return x;
}

int main() {
	scanf("%d %d", &N, &D);
	sum[0] = 0;
	for(int i=1; i<=N; i++) {
		scanf("%I64d", &arr[i]);
		sum[i] = sum[i-1] + arr[i];
	}
	for(int i=0; i<=N; i++) {
		for(int d=0; d<=D; d++) {
			if (i == 0) dp[i][d] = 0;
			else if (d == 0) dp[i][d] = rnd(sum[i]);
			else {
				dp[i][d] = rnd(sum[i]);
				for(int j = i-1; j>=0; j--) {
					if (dp[i][d] > dp[j][d-1] + rnd(sum[i] - sum[j]))
						dp[i][d] = dp[j][d-1] + rnd(sum[i] - sum[j]);
				}
			}
		}
	}
	printf("%I64d\n", dp[N][D]);
	return 0;
}
#include <bits/stdc++.h>
using namespace std;
#define MAXN 59
#define MAXK 109
#define INF (1LL<<60)

int N;
typedef long long ll
ll dp[MAXN][MAXK], w[MAXN], p[MAXN];

int main() {
	int T;
	scanf("%d", &T);
	for(int t=1; t<=T; t++) {
		scanf("%d", &N);
		for(int i=1; i<=N; i++) {
			scanf("%lld %lld", &p[i], &w[i]);
		}
		for(int i=0; i<=N; i++) {
			for(int k=0; k<=K; k++) {
				if (k == 0) dp[i][k] = 0;
				else if (i == 0) dp[i][k] = INF;
				else {
					dp[i][k] = INF;
					if (k>=w[i]) dp[i][k] = min(dp[i][k], dp[i-1][)
				}
			}
		}
	}
}
#include <bits/stdc++.h>
using namespace std;
#define MAXN 109

int dp[MAXN][MAXN], v[MAXN];

int main() {
	int T, N, M, K;
	char c;
	scanf("%d", &T);
	while(T-->0) {
		scanf("%d %d %d", &N, &M, &K);
		for(int i=0; i<N; i++) {
			v[i] = 0;
			for(int j=0; j<M; j++) {
				scanf(" %c", &c);
				if (c == '*') v[i]++;
			}
			
			for(int k=0; k<=K; k++) {
				if (i == 0) {
					if (k % 2 == 0) dp[i][k] = v[i];
					else dp[i][k] = M - v[i];
				}
				else if (k == 0) dp[i][k] = v[i] + dp[i-1][k];
				else dp[i][k] = max(v[i] + dp[i-1][k], M - v[i] + dp[i-1][k-1]);
			}
		}
		printf("%d\n", dp[N-1][K]);
	}
	return 0;
}
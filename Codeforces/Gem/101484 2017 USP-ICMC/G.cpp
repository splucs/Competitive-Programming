#include <bits/stdc++.h>
using namespace std;
#define MAXN 10009
#define ALFA 30
#define INF (1<<30)

int p[ALFA][ALFA], K;
int dp[ALFA][MAXN];

int main() {
	scanf("%d", &K);
	for(int i=0; i<26; i++) {
		for(int j=0; j<26; j++) {
			scanf("%d", &p[i][j]);
		}
	}
	for(int k=0; k<K; k++) {
		for(int i=0; i<26; i++) {
			if (k == 0) dp[i][k] = 0;
			else {
				dp[i][k] = INF;
				for(int j=0; j<26; j++) {
					dp[i][k] = min(dp[i][k], dp[j][k-1] + p[i][j]);
				}
			}
		}
	}
	int ans = INF;
	for(int i=0; i<26; i++) {
		ans = min(ans, dp[i][K-1]);
	}
	printf("%d\n", ans);
	return 0;
}
#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define MAXN 100009
typedef long long ll;

char s[MAXN];
ll dp[MAXN][3];

int main() {
	int T;
	scanf("%d", &T);
	FOR1(t, T) {
		scanf(" %s", s);
		int n = strlen(s);
		REP(i, n+1) FOR(k, 3) {
			if (i == n) {
				dp[i][k] = 0;
				continue;
			}
			if (k == 0) {
				if (s[i] != 'L') dp[i][k] = dp[i+1][k];
				else dp[i][k] = 1+dp[i+1][k];
			}
			if (k == 1) {
				if (s[i] != 'O') dp[i][k] = dp[i+1][k];
				else dp[i][k] = dp[i][0]+dp[i+1][k];
			}
			if (k == 2) {
				if (s[i] != 'L') dp[i][k] = dp[i+1][k];
				else dp[i][k] = dp[i][1]+dp[i+1][k];
			}
		}
		printf("%lld\n", dp[0][2]);
	}
	return 0;
}
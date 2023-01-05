#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define MAXN 100009
#define mset(x, y) memset(&x, y, sizeof x)
typedef long long ll;

int a[MAXN][3], n[3];
ll dp[MAXN][3];

int main() {
	int T;
	scanf("%d", &T);
	FOR1(t, T) {
		FOR(k, 3) {
			scanf("%d", &n[k]);
			FOR(i, n[k]) scanf("%d", &a[i][k]);
		}
		mset(dp, 0);
		REP(i, n[2]) dp[i][2] = 1 + dp[i+1][2];
		int j = n[2];
		REP(i, n[1]) {
			while(j-1 >= i && a[j-1][2] >= a[i][1]) j--;
			dp[i][1] = dp[i+1][1];
			if (j >= i) dp[i][1] += dp[j][2];
		}
		j = n[1];
		REP(i, n[0]) {
			while(j-1 >= i && a[j-1][1] >= a[i][0]) j--;
			dp[i][0] = dp[i+1][0];
			if (j >= i) dp[i][0] += dp[j][1];
		}
		printf("%lld\n", dp[0][0]);
	}
	return 0;
}
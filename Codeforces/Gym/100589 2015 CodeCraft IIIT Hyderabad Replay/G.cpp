#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define MAXN 15
typedef long long ll;

ll dp[1<<MAXN][MAXN];

int main() {
	int T, n, k;
	scanf("%d", &T);
	FOR1(t, T) {
		scanf("%d %d", &n, &k);
		ll ans = 0;
		REP(mask, (1<<n)) FOR(i, n) {
			if (mask+1 == (1<<n)) dp[mask][i] = 1;
			else {
				dp[mask][i] = 0;
				if (!(mask & (1<<i))) continue;
				FOR(j, n) {
					if (mask & (1<<j)) continue;
					if (abs(i-j) > k) continue;
					dp[mask][i] += dp[mask|(1<<j)][j];
				}
			}
			if ((mask&-mask) == mask) {
				ans += dp[mask][i];
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
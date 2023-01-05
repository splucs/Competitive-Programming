#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(),x.end()
#define sz(x) int(x.size())
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define MAXN 109
typedef long long ll;

int a[MAXN], n;
bool dp[MAXN][MAXN][2][MAXN];

bool solve(int K) {
	printf("solve %d\n", K);
	REP(i, n+1) FOR(c, a[i]+1) REP(d, 2) FOR1(k, K+1) {
		bool &ans = dp[i][c][d][k];
		if (i == n) {
			ans = (d == 0 && k == K+1);
		}
		else if (c == 0) {
			ans = dp[i+1][a[i+1]][d][k];
		}
		else {
			ans = false;
			if (k > 1 && c >= k-1) {
				ans = ans || dp[i][c-(k-1)][1][k-1];
			}
			if ((d == 0 || k == 1) && c >= k && k <= K) {
				ans = ans || dp[i][c-k][0][k+1];
			}
		}
		printf("dp[%d][%d][%d][%d] = %d\n", i, c, d, k, ans);
	}
	return dp[0][a[0]][1][K+1];
}

int main() {
	scanf("%d", &n);
	FOR(i, n) {
		scanf("%d", &a[i]);
	}
	int ans = 1;
	FOR1(i, 2) if (solve(i)) ans = i;
	printf("%d\n", ans);
	return 0;
}
#include <bits/stdc++.h>
using namespace std;
#define MAXN 309
#define MAXLOGN 20
#define MOD 1000000007
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define sz(x) int(x.size())
#define all(x) x.begin(),x.end()
#define mset(x, y) memset(&x, y, sizeof x)
typedef long long ll;
typedef vector<int> vi;

int n, k;
int a[MAXN];
int dp[MAXN][MAXN];
int pascal[MAXN][MAXN];

int main() {
	#ifdef ONLINE_JUDGE
	freopen("monotonic.in", "r", stdin);
	freopen("monotonic.out", "w", stdout);
	#endif

	FOR(i, MAXN) FOR(j, MAXN) {
		if (j > i) pascal[i][j] = 0;
		else if (j == 0 || i == j) pascal[i][j] = 1;
		else pascal[i][j] = (pascal[i-1][j] + pascal[i-1][j-1]) % MOD;
	}

	while(scanf("%d %d", &n, &k) != EOF) {
		FOR1(i, n) a[i] = 1;
		int s = 0, ds;
		FOR(i, k) {
			scanf("%d", &ds);
			s += ds;
			a[s] = 0;
		}
		FOR(s, n) FOR1(i, n) {
			int j = i+s;
			if (j > n) break;

			dp[i][j] = 0;
			for(int k = i; k <= j; k++) {
				if (k < j && a[k] == 0) continue;
				if (k > i && a[k-1] == 1) continue;

				int curl, curr, szl, szr;

				if (k == i) curl = 1;
				else curl = dp[i][k-1];
				szl = k-i;

				if (k == j) curr = 1;
				else curr = dp[k+1][j];
				szr = j-k;

				int cur = (curr*1ll*curl) % MOD;
				cur = (cur*1ll*pascal[szr+szl][szr]) % MOD;
				dp[i][j] = (dp[i][j] + cur) % MOD;
			}

			//printf("dp[%d][%d] = %d\n", i, j, dp[i][j]);
		}
		printf("%d\n", dp[1][n]);
	}
	return 0;
}
#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define MAXM 1000009
#define INF 0x3f3f3f3f
#define MOD 1000000009
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;

ii a[MAXN];
ll dp[MAXN][11];

int main() {
	int T;
	scanf("%d", &T);
	FOR1(caseNo, T) {
		int n, k;
		scanf("%d %d", &n, &k);
		FOR(i, n) scanf("%d %d", &a[i].fi, &a[i].se);
		sort(a, a+n);
		REP(i, n+1) FOR(j, k+1) {
			if (i == n) {
				dp[i][j] = 0;
			}
			else {
				ll v1 = -a[i].se + (j == 0 ? a[i].fi : min((ll)a[i].fi, dp[i+1][j-1]));
				ll v2 = dp[i+1][j];
				dp[i][j] = max(v1, v2);
			}
		}
		printf("%lld\n", dp[0][k]);
	}
	return 0;
}
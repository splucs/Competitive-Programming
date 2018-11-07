#include <bits/stdc++.h>
#define MAXN 100009
#define MAXM 309
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define fi first
#define se second
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
using namespace std;
typedef long long int ll;
typedef pair<int, int> ii;
typedef vector<int> vi;

int dp[MAXN][MAXM], h[26];
char order[MAXM], shows[MAXN];

int main() {
	int k, n;
	scanf("%d %d", &k, &n);
	FOR(i, 26) scanf("%d", &h[i]);
	scanf(" %s %s", order, shows);
	REP(i, n+1) FOR(j, k) {
		if (i == n) dp[i][j] = 0;
		else if (j == k-1) {
			dp[i][j] = dp[i+1][j];
			if (shows[i] == order[j])
				dp[i][j] = (1+dp[i][j])%MOD;
		}
		else {
			dp[i][j] = dp[i+1][j];
			char c = order[j] - 'A';
			if (shows[i] == order[j] && i+h[c]+1 < n)
				dp[i][j] = (dp[i+h[c]+1][j+1] + dp[i][j])%MOD;
		}
	}
	printf("%d\n", dp[0][0]);
	return 0;
}
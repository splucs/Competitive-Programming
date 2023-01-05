#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < int(n); i++)
#define FOR1(i, n) for(int i = 1; i <= int(n); i++)
#define REP(i, n) for(int i = (n)-1; i >= 0; i--)
#define REP1(i, n) for(int i = (n); i > 0; i--)
#define MAXN 459
#define MXM 4009
#define MAXLOGN 20
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
typedef vector<int> vi;
typedef long long ll;
typedef pair<int, int> ii;

char s[MAXN];
int dp[MAXN][MAXN];
int n, k, S[MAXN];

int main() {
	S[0] = 0;
	FOR1(i, MAXN-1) S[i] = i + S[i-1];
	while(scanf("%d %d %s", &n, &k, s) != EOF) {
		FOR(r, n+1) REP(i, n+1) {
			if (i == n) dp[i][r] = 0;
			else if (s[i] == '0') dp[i][r] = dp[i+1][r];
			else {
				int j;
				for(j = i; j < n && s[j] == '1'; j++);
				dp[i][r] = S[j-i] + dp[j][r];
				if (r == 0) continue;
				for(j = i; j < n && s[j] == '1'; j++) {
					if (dp[i][r] > S[j-i] + dp[j+1][r-1]) {
						dp[i][r] = S[j-i] + dp[j+1][r-1];
					}
				}
			}
			//printf("dp[%d][%d] = %d\n", i, r, dp[i][r]);
		}
		int ans;
		FOR(r, n+1) {
			if (dp[0][r] <= k) {
				ans = r;
				break;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
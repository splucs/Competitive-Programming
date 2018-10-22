#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009
#define MOD 1000000
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(),x.end()
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;

char s[MAXN];
int dp[MAXN][MAXN];

int main() {
	while(scanf(" %s", s) != EOF) {
		int n = strlen(s);
		REP(i, n+1) FOR(j, n+1) {
			if (i == n) {
				dp[i][j] = (j == 0);
			}
			else if (s[i] == '.') {
				if (j > 0) dp[i][j] = (dp[i+1][j+1] + dp[i+1][j-1]) % MOD;
				else dp[i][j] = dp[i+1][j+1];
			}
			else if (s[i] == '(') {
				dp[i][j] = dp[i+1][j+1];
			}
			else if (s[i] == ')') {
				if (j > 0) dp[i][j] = dp[i+1][j-1];
				else dp[i][j] = 0;
			}
		}
		printf("%d\n", dp[0][0]);
	}
	return 0;
}
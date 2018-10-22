#include <bits/stdc++.h>
using namespace std;
#define MAXN 5009
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define fi first
#define se second
typedef long long ll;
typedef pair<int, int> ii;

int a[MAXN], n;
int dp[MAXN][MAXN];

int main() {
	while(scanf("%d", &n) != EOF) {
		FOR(i, n) scanf("%d", &a[i]);
		FOR(s, n) FOR(i, n) {
			int j = i+s;
			if (j >= n) continue;
			if (i == j) dp[i][j] = 0;
			else if (i+1 == j) {
				dp[i][j] = (a[i] == a[j]);
			}
			else {
				int &ans = dp[i][j];
				ans = 0;
				if (a[i] == a[j] && ans < 1+dp[i+1][j-1]) {
					ans = 1+dp[i+1][j-1];
				}
				if (ans < dp[i+1][j]) ans = dp[i+1][j];
				if (ans < dp[i][j-1]) ans = dp[i][j-1];
			}
		}
		printf("%d\n", dp[0][n-1]);
	}
	return 0;
}
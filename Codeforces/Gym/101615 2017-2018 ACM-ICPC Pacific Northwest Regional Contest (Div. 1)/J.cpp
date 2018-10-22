#include <bits/stdc++.h>
#define MAXN 39
#define INF 0x3f3f3f3f
#define FOR(x,n) for(int x=0; x<n; x++)
#define FOR1(x,n) for(int x=1; x<=n; x++)
#define REP(x,n) for(int x=n-1; x>=0; x--)
#define REP1(x,n) for(int x=n; x>0; x--)
#define pb push_back
#define sz(x) ((int)x.size())
#define all(x) x.begin(),x.end()
#define mset(x, y) memset(&x, y, sizeof x)
using namespace std;
typedef pair<int,int> ii;
typedef long long ll;

ll dp[MAXN][MAXN];
int minr[MAXN], maxb[MAXN];
char field[MAXN][MAXN];

int main() {
	int n, m;
	while(scanf("%d %d", &n, &m) != EOF) {
		mset(minr, INF);
		mset(maxb, 0);
		FOR1(i, n) {
			scanf(" %s", field[i]+1);
			FOR1(j, m) {
				if (field[i][j] == 'R') minr[j] = min(i, minr[j]);
				if (field[i][j] == 'B') maxb[j] = max(i, maxb[j]);
			}
		}
		REP1(j, m+1) FOR(i, n+1) {
			if (j == m+1) {
				dp[j][i] = 1;
				continue;
			}
			int top = min(minr[j]-1, i);
			int bot = maxb[j];
			dp[j][i] = 0;
			for(int k = bot; k <= top; k++) {
				dp[j][i] += dp[j+1][k];
			}
		}
		printf("%lld\n", dp[1][n]);
	}
	return 0;
}
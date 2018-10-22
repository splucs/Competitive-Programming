#include <bits/stdc++.h>
#define MAXN 709
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define EPS 1e-9
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
typedef vector<int> vi;

int dp[1<<12][MAXN][12];
int p[12];

int main() {
	int n, x;
	while(scanf("%d %d", &n, &x) != EOF) {
		int maxp = 0;
		FOR(i, n) {
			scanf("%d", &p[i]);
			maxp = max(maxp, p[i]);
		}
		REP(mask, (1<<n)) FOR(s, x+1) FOR(i, n) {
			int &ans = dp[mask][s][i];
			if (mask == 0) {
				ans = 0;
				FOR(j, n) {
					if (p[j] == maxp) continue;
					int cur = (maxp-p[j]+1)*n;
					if (s < cur) continue;
					ans += dp[(1<<j)][s-cur][j];
				}
			}
			else if (mask+1 == (1<<n)) {
				ans = 1;
			}
			else {
				ans = 0;
				if (!(mask & (1<<i))) continue;
				int cnt = __builtin_popcount(mask);
				FOR(j, n) {
					if (mask & (1<<j)) continue;
					int cur = (n-cnt)*max(0, p[i]-p[j]+1);
					if (s < cur) continue;
					ans += dp[mask^(1<<j)][s-cur][j];
				}
			}
		}
		printf("%d\n", dp[0][x][0]);
	}
	return 0;
}
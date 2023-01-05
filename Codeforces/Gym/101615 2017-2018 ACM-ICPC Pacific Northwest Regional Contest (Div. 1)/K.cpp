#include <bits/stdc++.h>
#define MAXN 49
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

char str[MAXN];
int dp[MAXN][2][2], n;

int fix(int s, int t, int p, int q) {
	if (q) s++;
	if (t < s) {
		if (!p) return INF;
		return t-s+10;
	}
	else {
		if (p) return t-s+10;
		else return t-s;
	}
}

int main() {
	while(scanf(" %s", str) != EOF) {
		n = strlen(str);
		REP(i, n/2 + 1) FOR(p, 2) FOR(q, 2) {
			int j = n-i-1;
			int &ans = dp[i][p][q];
			ans = 0;
			if (i > j) {
				if (p == q) ans = 0;
				else ans = INF;
			}
			else if (i == j) {
				ans = INF;
				FOR(c, 10) {
					int b = str[i] - '0';
					ans = min(ans, fix(b, c, p, q));
				}
			}
			else {
				ans = INF;
				FOR(c, 10) FOR(fp, 2) FOR(fq, 2) {
					int cur = dp[i+1][fp][fq];
					int bi = str[i] - '0';
					int bj = str[j] - '0';
					
					cur = min(INF, cur + fix(bi, c, p, fp));
					cur = min(INF, cur + fix(bj, c, fq, q));

					ans = min(ans, cur);
				}
			}
		}
		printf("%d\n", min(dp[0][0][0], dp[0][1][0]));
	}
	return 0;
}
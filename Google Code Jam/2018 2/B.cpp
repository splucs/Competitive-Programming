/*
             /\\
              .\\\..
              \\   \\
              \ (o) /
              (/    \
               /\    \
              ///     \
             ///|     |
            ////|     |
           //////    /
           |////    /
          /|////--V/  Stephen Morgana
         //\//|   |
     ___////__\___\__________
    ()_________'___'_________)
        \\\\
          \\\
            \\
*/

#include <bits/stdc++.h>
#define DEBUG false
#define debugf if (DEBUG) printf
#define MAXN 501
#define MAXM 35
#define MOD 1000000007
#define INF 0x3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define EPS 1e-9
#define PI 3.141592653589793238462643383279502884
#define FOR(x,n) for(int x=0; (x)<int(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=int(n); (x)++)
#define REP(x,n) for(int x=int(n)-1; (x)>=0; (x)--)
#define REP1(x,n) for(int x=(n); (x)>0; (x)--)
#define pb push_back
#define pf push_front
#define fi first
#define se second
#define mp make_pair
#define all(x) x.begin(), x.end()
#define mset(x,y) memset(&x, (y), sizeof(x));
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef unsigned int uint;

short dp[MAXN][MAXN][MAXM][MAXM];

int main() {
	int lf, rt;
	FOR(r, MAXN) FOR(b, MAXN) {
		REP(nr, MAXM) REP(nb, MAXM) {
			if (nb+1 < MAXM) {
				if (r >= nr && b >= nb+1 && nb+1 < MAXM)
					lf = 1+dp[r-nr][b-nb-1][nr][nb+1];
				else lf = 0;
				rt = dp[r][b][nr][nb+1];
			}
			else {
				if (nr+1 >= MAXM) {
					rt = lf = 0;
				}
				else {
					if (r >= nr+1)
						rt = 1+dp[r-nr-1][b][nr+1][0];
					else rt = 0;
					lf = dp[r][b][nr+1][0];
				}
			}
			if (rt > lf) dp[r][b][nr][nb] = rt;
			else dp[r][b][nr][nb] = lf;
			if (dp[r][b][nr][nb] == 0 && r+b > 0) dp[r][b][nr][nb] = -INF;
		}
	}
	int T;
	scanf("%d", &T);
	FOR1(caseNo, T) {
		int r, b;
		scanf("%d %d", &r, &b);
		int ans = dp[r][b][0][0];
		if (ans < 0) ans = 1;
		printf("Case #%d: %d\n", caseNo, ans);
	}
	return 0;
}
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
#define MAXN 503009
#define MAXM 900009
#define MOD 1000000007
#define INF 0x3f3f3f3f
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

int a[MAXN], dp[MAXN], sum[MAXN];
int n, k, d;

int main() {
	scanf("%d %d %d", &n, &k, &d);
	FOR(i, n) scanf("%d", &a[i]);
	sort(a, a+n);
	int r = n-1;
	sum[n] = 1;
	dp[n] = 1;
	sum[n+1] = 0;
	dp[n+1] = 0;
	REP(i, n) {
		int l = i+k-1;
		while(a[r]-a[i] > d) r--;
		if (l >= n) dp[i] = 0;
		else if (l == n-1) {
			if (r == n-1) dp[i] = 1;
			else dp[i] = 0;
		}
		else {
			if (r < l) dp[i] = 0;
			else dp[i] = sum[l+1] - sum[r+2] > 0 ? 1 : 0;
		}
		sum[i] = dp[i] + sum[i+1];
	}
	if (dp[0]) printf("YES\n");
	else printf("NO\n");
	return 0;
}
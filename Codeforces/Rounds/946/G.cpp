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
#define MAXN 200009
#define MAXM 1000200019
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

class SegmentTree {
	vector<int> a;
	int n, sz;
public:
	SegmentTree() {}
	SegmentTree(int _sz) {
		sz = _sz;
		for (n = 1; n < sz; n <<= 1);
		a.assign(n << 1, INF);
	}
	void update(int i, int x) {
		a[i+n] = min(x, a[i+n]);
		for (i += n, i >>= 1; i; i >>= 1)
			a[i] = min(a[i<<1], a[1+(i<<1)]);
	}
	int query(int l) {
		int r = sz-1;
		int ans = INF;
		for (l += n, r += n+1; l < r; l >>= 1, r >>= 1) {
			if (l & 1) ans = min(ans, a[l++]);
			if (r & 1) ans = min(ans, a[--r]);
		}
		return ans;
	}
};

SegmentTree st[2];

int a[MAXN], n;
int dp[MAXN][2];

int main() {
	scanf("%d", &n);
	map<int, int> reduce;
	FOR(i, n) {
		scanf("%d", &a[i]);
		a[i] -= i;
		reduce[a[i]] = 0;
		reduce[a[i]-1] = 0;
	}
	int cnt = 0;
	for(auto & pp : reduce) {
		pp.second = cnt++;
	}
	st[0] = st[1] = SegmentTree(cnt);
	int ans = INF;
	REP(i, n) {
		if (i == n-1) {
			dp[i][0] = dp[i][1] = 0;
			continue;
		}
		
		dp[i][1] = max(n-i-2, 0);
		dp[i][0] = n-i-1;

		dp[i][1] = min(dp[i][1], st[0].query(reduce[a[i]-1]) - i - 2);
		FOR(b, 2) st[b].update(reduce[a[i+1]], i+1 + dp[i+1][b]);
		dp[i][0] = min(dp[i][0], st[0].query(reduce[a[i]]) - i - 1);
		dp[i][1] = min(dp[i][1], st[1].query(reduce[a[i]]) - i - 1);

		ans = min(ans, dp[i][1] + i);
		ans = min(ans, dp[i][0] + max(i-1, 0));
	}
	printf("%d\n", ans);
	return 0;
}

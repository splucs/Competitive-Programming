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
#define MAXN 103009
#define MAXM 900009
#define MOD 1000000007
#define INF 1500000000
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

ll n, H;

ll ceil(ll a, ll b) {
	if (a % b == 0) return a/b;
	else return a/b + 1;
}

ll check(ll x) {
	ll m = n - (x*(x+1)/2);
	if (x <= H && m <= 0) {
		ll lo = 1;
		ll hi = x+1;
		while(hi > lo + 1) {
			ll y = (hi+lo)/2;
			if (y*(y+1)/2 <= n) lo = y;
			else hi = y;
		}
		m = n - lo*(lo+1)/2;
		return lo + ceil(m, lo);
	}
	if (x <= H) {
		return x + ceil(m, x);
	}
	ll l = (H+x-1)*(x-H)/2;
	if (l > m) return -1;
	m -= l;
	return x + (x-H) + ceil(m, x);
}

int main() {
	scanf("%lld %lld", &n, &H);
	ll lo = 1;
	ll hi = INF;
	while(hi > lo + 1) {
		ll mid = (hi + lo) / 2;
		if (check(mid) == -1) hi = mid;
		else lo = mid;
	}
	printf("%lld\n", check(lo));
	return 0;
}
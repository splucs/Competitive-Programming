#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000009
#define MAXM ((1e+18) + 100)
#define MOD 1000000007
#define INF (1LL<<60)
#define EPS 1e-9
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;

ll n, k, M, D;

ll ceil(ll a, ll b) {
	if (a % b == 0) return a/b;
	return a/b + 1;
}

ll getd(ll x) {
	return ceil(n/x, k);
}

int main() {
	scanf("%I64d %I64d %I64d %I64d", &n, &k, &M, &D);
	ll ans = 0;
	FOR1(d, D) {
		ll lo = 0;
		ll hi = INF;
		while(hi > lo + 1) {
			ll x = (hi + lo) / 2;
			ll cd = getd(x);
			if (cd >= d) lo = x;
			else hi = x;
		}
		ll x = lo;
		if (x == 0) continue;
		if (x > M) x = M;
		ll cd = getd(x);
		if (d != cd) continue;
		ans = max(ans, d*x);
	}
	printf("%I64d\n", ans);
	return 0;
}
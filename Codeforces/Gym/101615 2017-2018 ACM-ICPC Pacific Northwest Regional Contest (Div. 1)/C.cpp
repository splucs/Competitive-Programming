#include <bits/stdc++.h>
#define MAXN 5009
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
typedef vector<int> vi;

ll msqrt(ll x) {
	ll val = sqrt(x);
	val = max(0LL, val-1);
	while (val*val <= x) val++;
	return val-1;
}

int main() {
	unsigned long long A, B;
	unsigned long long ans = 0;

	cin >> A >> B;
	ll raiz = msqrt(B);

	for (ll i = 1; i <= raiz; i++) {
		ll lo = (A/i), hi = (B/i);
		if (lo*i < A) lo++;
		ans += i*(hi-lo + 1);

		lo = max(lo, raiz+1);
		if (lo > hi) continue;
		
		if ((hi + lo)%2 == 0) {
			ans += (hi + lo) / 2 * (hi - lo + 1);
		} else {
			assert((hi-lo+1)%2 == 0);
			ans += (hi-lo + 1)/2 * (hi + lo);
		}
	}
	cout << ans << endl;
}
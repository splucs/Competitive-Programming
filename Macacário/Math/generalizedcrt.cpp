#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll extGcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    else {
        ll g = extGcd(b, a % b, y, x);
        y -= a / b * x;
        return g;
    }
}

/*
 * Generalized CRT
 */

ll crt(ll rem[], ll mod[], int n) {
	if (n == 0) return 0;
    ll ans = rem[0], m = mod[0];
    for (int i = 1; i < n; i++) {
	    ll x, y;
	    ll g = extGcd(mod[i], m, x, y);
	    if ((ans - rem[i])%g != 0) return -1;
	    ans = ans + 1ll*(rem[i]-ans)*(m/g)*y;
	    m = (mod[i]/g)*(m/g)*g;
	    ans = (ans%m + m)%m;
    }
    return ans;
}

/*
 * COMPILATION TEST
 */

int main() {
	long long a[2] = {2, 7};
	long long p[2] = {10, 15};
	printf("%lld\n", crt(a, p, 2));
}

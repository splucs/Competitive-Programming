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

ll crt(ll* rem, ll* mod, int n) {
	if (n == 0) return 0;
    ll ans = rem[0], m = mod[0];
    for (int i = 1; i < n; i++) {
	    ll x, y;
	    ll g = extGcd(mod[i], m, x, y); // x*mod[i] + m*y = gcd(mod[i], m);
	    assert(x*mod[i] + m*y == g);

	    if ((ans - rem[i])%g != 0) return -1; // No solution

	    ans = ans + 1ll*(rem[i]-ans)*(m/g)*y; // new ans
	    m = (mod[i]/g)*(m/g)*g; // new m = lcm(mod[i], m)
	    
	    ans = (ans%m + m)%m;
    }
    return ans;
}


int main() {
	long long a[2] = {2, 7};
	long long p[2] = {10, 15};
	printf("%lld\n", crt(a, p, 2));
}

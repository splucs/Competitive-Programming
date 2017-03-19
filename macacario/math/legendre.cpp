#include <cstdio>
#include <cstring>

typedef long long ll;

ll legendre(ll n, ll p) {
	int ans = 0;
	ll prod = p;
	while (prod <= n) {
		ans += n / prod;
		prod *= p;
	}
	return ans;
}
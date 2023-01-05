#include <bits/stdc++.h>
using namespace std;
#define MOD 1000000009LL
#define FOR(i, n) for(long long i = 0; i < n; i++)

typedef long long ll;

template <typename T>
T extGcd(T a, T b, T& x, T& y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    else {
        T g = extGcd(b, a % b, y, x);
        y -= a / b * x;
        return g;
    }
}
 
template <typename T>
T modInv(T a, T m) {
    T x, y;
    extGcd(a, m, x, y);
    return (x % m + m) % m;
}
 
template <typename T>
T modDiv(T a, T b, T m) {
    return ((a % m) * modInv(b, m)) % m;
}

template<typename T>
T modExp(T a, T b, T m) {
    if (b == 0) return (T)1;
    T c = modExp(a, b / 2, m);
    c = (c * c) % m;
    if (b % 2 != 0) c = (c*a) % m;
    return c;
}

int main() {
	ll a, b, n, k;
	scanf("%I64d %I64d %I64d %I64d", &n, &a, &b, &k);
	const ll r = modDiv(b, a, MOD);
	ll ans = modExp(a, (ll)n, MOD);
	ans %= MOD;
	ll rk = modExp(r, k, MOD);
	if (rk == 1) {
		ans *= (n+1)/k;
	}
	else {
		ans *= modDiv(
			(modExp(r, n+1, MOD) - 1 + MOD)%MOD,
			(rk - 1 + MOD)%MOD,
			MOD
		);
	}
	ans %= MOD;
	ll cur = 0, p = 1;
	FOR(i, k) {
		char op;
		scanf(" %c", &op);
		if (op == '+') cur = (cur + p) % MOD;
		else cur = (cur - p + MOD) % MOD;
		p = (p*r)%MOD;
	}
	ans = (ans*cur)%MOD;
	printf("%I64d\n", ans);
	return 0;
}




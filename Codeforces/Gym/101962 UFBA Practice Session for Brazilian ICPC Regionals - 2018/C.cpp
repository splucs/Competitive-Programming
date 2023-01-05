#include <bits/stdc++.h>
#define MAXN 100009
#define MOD 1000000007
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
using namespace std;
typedef long long ll;

ll modExp(ll a, ll b) {
	if (b == 0) return 1;
	ll c = modExp(a, b/2);
	c = (c*c) % MOD;
	if (b % 2 != 0) c = (c*a) % MOD;
	return c;
}

ll mul(ll a, ll b) {
	return ((a%MOD + MOD) % MOD)*((b%MOD + MOD) % MOD) % MOD;
}

int main() {
	int T;
	scanf("%d", &T);
	FOR1(caseNo, T) {
		ll n;
		scanf("%lld", &n);
		ll pw2 = modExp(2, n-1);
		ll S1 = (mul(n-2, pw2) + 1) % MOD;
		ll S2 = (mul(mul(n-1, n-1), pw2) + pw2 - 1 - 2*S1) % MOD;
		ll ans = mul(n, S1) - S2;
		ans = (ans%MOD + MOD) % MOD;
		printf("%lld\n", ans);
	}
	return 0;
}
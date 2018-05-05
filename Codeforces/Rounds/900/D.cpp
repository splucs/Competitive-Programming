#include <bits/stdc++.h>
using namespace std;
#define MOD 1000000007

typedef long long ll;
map<ll, ll> dp;

ll modExp(ll a, ll e) {
	if (e == 0) return 1;
	ll k = modExp(a, e/2);
	k = (k*k)%MOD;
	if (e%2 != 0) k = (k*a)%MOD;
	return k;
}

ll DP(ll y) {
	if (dp.count(y)) return dp[y];
	if (y == 1) return dp[y] = 1;
	ll ans = 0;
	for(ll i = 1; i*i <= y; i++) {
		if (y % i == 0) {
			if (i != y) ans += DP(i);
			ans %= MOD;
			if (i*i != y && y/i != y) ans += DP(y/i);
			ans %= MOD;
		}
	}
	ans = (modExp(2, y-1) - ans + MOD) % MOD;
	//printf("DP[%I64d] = %I64d\n", y, ans);
	return dp[y] = ans;
}

int main() {
	ll x, y;
	scanf("%I64d %I64d", &x, &y);
	if (y%x != 0) {
		printf("0\n");
		return 0;
	}
	printf("%I64d\n", DP(y/x));
	return 0;
}
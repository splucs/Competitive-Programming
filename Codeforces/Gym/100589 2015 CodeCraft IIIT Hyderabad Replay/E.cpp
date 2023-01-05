#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define MAXN 100009
#define fi first
#define se second
#define mset(x, y) memset(&x, y, sizeof x)
typedef long long ll;
typedef pair<int, int> ii;

set<ll> vis;

void compute(ll s) {
	if (s == 0) return;
	if (vis.count(s)) return;
	vis.insert(s);
	if (s == 1) return;
	ll hs, left = s, n;
	for(n = 1; n <= left; n <<= 1) {
		left -= n;
	}
	assert((s-left-1)%2 == 0);
	hs = (s-left-1)/2;
	if (left <= n/2) {
		compute(hs+left);
		compute(hs);
	}
	else {
		compute(hs+n/2);
		compute(hs+left-n/2);
	}
}

int main() {
	int T;
	scanf("%d", &T);
	while(T --> 0) {
		ll n;
		scanf("%lld", &n);
		if (n == 1) { printf("1\n"); continue; }

		vis.clear();
		compute(n);
		int k = vis.size() - 1;
		ll a = 1;
		while (a <= n) { a *= 2; k++; }
		k--; 
		printf("%d\n", k);
	}
	return 0;
}
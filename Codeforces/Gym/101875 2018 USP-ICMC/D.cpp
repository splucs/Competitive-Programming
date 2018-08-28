#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < int(n); i++)
#define MAXN 100009
#define pb push_back
typedef vector<int> vi;
typedef long long ll;

int main() {
	ll n, a, b, c, d;
	while(scanf("%lld %lld %lld %lld %lld", &n, &a, &b, &c, &d) != EOF) {
		a = abs(c-a);
		b = abs(d-b);
		
		a = a + b;
		if (a == 0) a = 2;
		ll ans = (n-a)/2 + 1;
		if (n < a) ans = 0;
		printf("%lld\n", ans);
	}
	return 0;
}
#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
typedef long long ll;

int main() {
	int n;
	ll k;
	while(scanf("%d %lld", &n, &k) != EOF) {
		ll carry = 0;
		ll ans = 0, x;
		FOR(i, n) {
			scanf("%lld", &x);
			carry += x;
			ans += carry/k;
			carry %= k;
			if (i+1 == n) x = 0;
			if (carry > x) {
				ans++;
				carry = 0;
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
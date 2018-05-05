#include <bits/stdc++.h>
using namespace std;
#define MAXN 5000009
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define pb push_back
#define INF (1LL<<60)
typedef long long ll;
typedef pair<int, int> ii;

int main() {
	ll N;
	while(scanf("%I64d", &N) != EOF) {
		ll ans = 0;
		for(ll lb = 1; lb < N; lb <<= 1) {
			ll am = ((N - 1 - lb)/(lb<<1) + 1);
			ans += lb*am;
		}
		printf("%I64d\n", ans);
	}
	return 0;
}
#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)

typedef long long ll;

ll n, m;
int T;

int main() {
	scanf("%d", &T);
	FOR1(t, T) {
		scanf("%lld %lld", &n, &m);
		ll ans = (n+m)*(m-n+1)/2;
		printf("Caso #%d: %lld\n", t, ans);
	}
	return 0;
}

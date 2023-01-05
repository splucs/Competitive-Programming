#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int solve(ll n) {
	int cnt = 0, ans = 0;
	for(int i = 0; i < 50; i++) {
		cnt++;
		if ((n & 1LL) == 0) cnt = 0;
		n >>= 1;
		if (ans < cnt) ans = cnt;
	}
	return ans;
}

int main() {
	int N;
	ll x;
	scanf("%d", &N);
	while(N --> 0) {
		scanf("%lld", &x);
		printf("%d\n", solve(x));
	}
	return 0;
}
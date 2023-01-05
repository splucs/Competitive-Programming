#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
	ll a, b;
	scanf("%I64d %I64d", &a, &b);
	if (b-a > 10) {
		printf("0\n");
	}
	else {
		ll p = 1;
		for(ll i=a+1; i<=b; i++) {
			p = (p*i)%10;
		}
		printf("%I64d\n", p);
	}
	return 0;
}
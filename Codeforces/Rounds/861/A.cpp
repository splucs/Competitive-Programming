#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, k;
	scanf("%d %d", &n, &k);
	long long ans = n, p = 1;
	while(k > 0) {
		k--;
		p *= 10;
	}
	while(ans % p != 0) ans += n;
	printf("%I64d\n", ans);
	return 0;
}
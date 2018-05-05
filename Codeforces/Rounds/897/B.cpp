#include <bits/stdc++.h>
using namespace std;
#define MAXN 109

int num[MAXN];
typedef long long ll;

ll duplicate(int n, int p) {
	int cb = 0;
	while(n > 0) {
		num[cb++] = n%10;
		n /= 10;
	}
	reverse(num, num+cb);
	for(int i = cb-1; i >= 0; i--) {
		num[cb++] = num[i];
	}
	ll ans = 0, p10 = 1;
	for(int i = 0; i < cb; i++) {
		ans = (ans + num[i]*p10)%p;
		p10 = (p10*10LL)%p;
	}
	return ans;
}

int main() {
	int k, p;
	ll ans;
	scanf("%d %d", &k, &p);
	for(int i=1; i<=k; i++) {
		ans = (ans + duplicate(i, p))%p;
	}
	printf("%I64d\n", ans);
	return 0;
}
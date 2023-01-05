#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

typedef long long ll;
int n;
ll k;

int main()
{
	scanf("%d", &n);
	ll tot = 0, hi = 0;
	for (int i = 0; i < n; i++) {
		scanf("%I64d", &k);
		tot += k;
		hi = max(hi, k);
	}
	ll ans;
	if (tot >= 2 * hi) ans = tot / 2;
	else ans = tot - hi;
	printf("%I64d\n", ans);
	return 0;
}
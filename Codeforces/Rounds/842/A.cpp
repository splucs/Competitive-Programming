#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
	ll l, r, x, y, k;
	scanf("%I64d %I64d %I64d %I64d %I64d", &l, &r, &x, &y, &k);
	bool ok = false;
	for(ll z=x, m; z<=y && !ok; z++) {
		m = z*k;
		if (m >= l && m <= r) ok = true;
	}
	if (ok) printf("YES\n");
	else printf("NO\n");
	return 0;
}
#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

typedef long long ll;
typedef pair<ll, ll> ii;
int n;
ll k;
ii p[MAXN];

int main()
{
	scanf("%d %I64d", &n, &k);
	for (int i = 0; i < n; i++) {
		scanf("%I64d %I64d", &p[i].first, &p[i].second);
	}
	sort(p, p + n);
	int l = 0, r = n - 1;
	ll ans = 0, carry = 0, cur;
	while (l < n && p[l].first < 0) {
		ans -= 2 * p[l].first*(p[l].second / k);
		p[l].second %= k;
		if (p[l].second == 0) {
			l++;
			continue;
		}
		ans -= 2 * p[l].first;
		carry = k;
		while (l < n && p[l].first < 0 && carry > 0) {
			cur = min(carry, p[l].second);
			p[l].second -= cur;
			carry -= cur;
			while (l < n && p[l].first < 0 && p[l].second == 0) l++;
		}
	}
	while (r >= 0 && p[r].first > 0) {
		ans += 2 * p[r].first*(p[r].second / k);
		p[r].second %= k;
		if (p[r].second == 0) {
			r--;
			continue;
		}
		ans += 2 * p[r].first;
		carry = k;
		while (r >= 0 && p[r].first > 0 && carry > 0) {
			cur = min(carry, p[r].second);
			p[r].second -= cur;
			carry -= cur;
			while (r >= 0 && p[r].first > 0 && p[r].second == 0) r--;
		}
	}
	printf("%I64d\n", ans);
	return 0;
}
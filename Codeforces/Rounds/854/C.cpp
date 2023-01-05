#include <bits/stdc++.h>
using namespace std;
#define MAXN 300009

typedef long long ll;
typedef pair<ll, int> ii;
ll c[MAXN], t[MAXN];

int main() {
	int n, k;
	scanf("%d %d", &n, &k);
	for(int i=1; i<=n; i++) {
		scanf("%I64d", &c[i]);
	}
	priority_queue<ii> s;
	vector<int> v;
	ll ans = 0;
	for(int i=1; i<=n+k; i++) {
		if (i <= n) s.push(ii(c[i], i));
		if (i > k) {
			ii cur = s.top();
			s.pop();
			ans += cur.first*(i - cur.second);
			t[cur.second] = i;
		}
	}
	printf("%I64d\n", ans);
	for(int i=1; i<=n; i++) printf("%I64d ", t[i]);
	printf("\n");
	return 0;
}
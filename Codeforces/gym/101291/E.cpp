#include <bits/stdc++.h>
using namespace std;
#define MAXN 309

typedef long long ll;

int main()
{
	int n, k;
	ll t[MAXN];
	priority_queue<ll> pq;
	scanf("%d %d", &n, &k);
	for (int i = 0; i < n; i++) {
		scanf("%I64d", &t[i]);
	}
	int next = 0;
	while (pq.size() < k && next < n) {
		pq.push(-t[next++]);
	}
	ll cur = 0, ans = 0;
	while (!pq.empty()) {
		cur -= pq.top();
		pq.pop();
		ans += cur;
		if (next < n)
			pq.push(-t[next++]);
	}
	printf("%I64d\n", ans);
	return 0;
}
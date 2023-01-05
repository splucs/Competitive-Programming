#include <cstdio>
#include <stack>
using namespace std;
typedef long long ll;

#define MAXN 100009

/*
 * Solution to the histogram problem in O(n)
 */

ll histogram(ll vet[], int n) {
	stack<ll> s;
	ll ans = 0, tp, cur;
	int i = 0;
	while(i < n || !s.empty()) {
		if (i < n && (s.empty() || vet[s.top()] <= vet[i])) s.push(i++);
		else {
			tp = s.top();
			s.pop();
			cur = vet[tp] * (s.empty() ? i : i - s.top() - 1);
			if (ans < cur) ans = cur;
		}
	}
	return ans;
}

/*
 * URI 1683
 */

ll vet[MAXN];

int main() {
	int n;
	while (scanf("%d", &n), n) {
		for (int i = 0; i<n; i++) {
			scanf("%lld", vet + i);
		}
		printf("%lld\n", histogram(vet, n));
	}
	return 0;
}
#include <cstdio>
#include <stack>
#define MAXN 100009
#define INF  (1LL<<60)
using namespace std;

typedef long long ll;

ll histogram(ll * vet, int n) {
	stack<ll> s;
	ll ans = 0, tp, cur;
	int i = 0;
	while(i < n) {
		if (s.empty() || vet[s.top()] <= vet[i]) s.push(i++);
		else {
			tp = s.top();
			s.pop();
			cur = vet[tp] * (s.empty() ? i : i - s.top() - 1);
			if (ans < cur) ans = cur;
		}
	}
	while (!s.empty()) {
		tp = s.top();
		s.pop();
		cur = vet[tp] * (s.empty() ? i : i - s.top() - 1);
		if (ans < cur) ans = cur;
	}
	return ans;
}

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
#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define INF (1LL<<60)

typedef long long ll;
ll p[MAXN];

int main() {
	int N;
	scanf("%d", &N);
	for(int i=0; i<N; i++) {
		scanf("%lld", &p[i]);
	}
	set<ll> s;
	set<ll>::iterator it;
	ll ans = INF;
	for(int i=0; i<N; i++) {
		it = s.upper_bound(p[i]);
		if (it != s.end()) {
			ans = min(ans, (*it) - p[i]);
		}
		s.insert(p[i]);
	}
	printf("%lld\n", ans);
	return 0;
}
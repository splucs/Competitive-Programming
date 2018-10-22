#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define fi first
#define se second
typedef long long ll;
typedef pair<int, int> ii;

int main() {
	int n;
	while(scanf("%d", &n) != EOF) {
		map<int, int> p, q;
		FOR1(i, n) {
			int x, y;
			scanf("%d %d", &x, &y);
			p[x+y]++;
			p[x-y]++;
		}
		ll ans = 0;
		for(ii pp : p) {
			ans += pp.se*(pp.se-1LL);
		}
		for(ii pp : q) {
			ans += pp.se*(pp.se-1LL);
		}
		ll tot = (n*1LL*n);
		printf("%.20f\n", ans*1.0/tot);
	}
	return 0;
}
#include <bits/stdc++.h>
using namespace std;
#define MAXN 19
#define INF (1LL<<60)
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define pb push_back
typedef pair<int, int> ii;
typedef long long ll;

int N;
ll t[MAXN];
vector<int> g[MAXN];

int main() {
	while(scanf("%d", &N) != EOF) {
		FOR(i, N) {
			scanf("%lld", &t[i]);
			g[i].clear();
		}
		FOR(e, N-1) {
			int i = e+1, j;
			scanf("%d", &j);
			j--;
			g[i].pb(e);
			g[j].pb(e);
		}
		ll ans = INF;
		FOR(mask, (1<<N)) {
			int vis = 0;
			ll cost = 0;
			FOR(i, N) {
				if (mask & (1<<i)) {
					for(int e : g[i]) {
						vis |= (1<<e);
					}
					cost += t[i];
				}
			}
			if (vis == (1<<(N-1))-1) ans = min(ans, cost);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
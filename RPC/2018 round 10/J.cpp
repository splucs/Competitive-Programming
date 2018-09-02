#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define MAXN 29
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define pb push_back
#define fi first
#define se second
#define mset(x, y) memset(&x, y, sizeof x);
typedef pair<int, int> ii;
typedef vector<int> vi;

int like[MAXN], incomp[MAXN];

int main() {
	int m, g;
	while(scanf("%d %d", &m, &g) != EOF) {
		mset(incomp, false);
		int c;
		scanf("%d", &c);
		while(c --> 0) {
			int n, mask = 0, j;
			scanf("%d", &n);
			while(n --> 0) {
				scanf("%d", &j);
				j--;
				mask |= (1<<j);
			}
			FOR(i, m) {
				if (!(mask & (1<<i))) continue;
				incomp[i] = mask^(1<<i);
			}
		}
		//FOR(i, m) FOR(j, m) {
		//	printf("incomp[%d][%d] = %d\n", i, j, incomp[i][j]);
		//}
		FOR(i, g) {
			int l;
			scanf("%d", &l);
			like[i] = 0;
			while (l --> 0) {
				int j;
				scanf("%d", &j);
				j--;
				like[i] |= (1<<j);
			}
		}
		ii ans = {-INF, -INF};
		FOR(mask, (1<<m)) {
			bool ok = true;
			FOR(i, m) {
				if (!(mask & (1<<i))) continue;
				if (mask & incomp[i]) ok = false;
			}
			if (!ok) continue;
			int cur = 0;
			int nmelodies = __builtin_popcount(mask);
			FOR(i, g) {
				if (mask & like[i]) {
					cur++;
				}
			}
			ans = max(ans, {cur, -nmelodies});
		}
		printf("%d %d\n", ans.fi, -ans.se);
	}
	return 0;
}
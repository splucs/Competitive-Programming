#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define MAXN 100009
#define fi first
#define se second
#define mset(x, y) memset(&x, y, sizeof x)
typedef long long ll;

int bit[MAXN];

void update(int i, int k) {
	for(; i < MAXN; i += (i&-i)) bit[i] += k;
}

int query(int i) {
	int ans = 0;
	for(; i; i -= (i&-i)) ans += bit[i];
	return ans;
}

int query(int i, int j) {
	return query(j) - query(i-1);
}

int n, a[MAXN];
ll k;

int main() {
	while(scanf("%d %lld", &n, &k) != EOF) {
		map<int, int> reduce;
		FOR1(i, n) {
			scanf("%d", &a[i]);
			reduce[a[i]] = 0;
		}
		int cnt = 0;
		for(auto & pp : reduce) {
			pp.se = ++cnt;
		}
		FOR1(i, n) a[i] = reduce[a[i]];
		int i = 1;
		ll inv = 0;
		mset(bit, 0);
		ll ans = n*(n+1LL)/2;
		FOR1(j, n) {
			inv += query(a[j]+1, cnt);
			update(a[j], 1);
			while(j >= i && inv >= k) {
				update(a[i], -1);
				inv -= query(1, a[i]-1);
				i++;
			}
			ans -= j-i+1;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
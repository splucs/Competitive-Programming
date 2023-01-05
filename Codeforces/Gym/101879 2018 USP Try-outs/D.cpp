#include <bits/stdc++.h>
#define FOR(x,n) for(int x=0;x<n;x++)
using namespace std;
#define MAXN 1000009

struct voter {
	int x, y;
	char c;
} v[MAXN];
int n, tw = 0, tb = 0;

bool operator < (voter a, voter b) {
	return a.x < b.x;
}

int solve() {
	int nw = 0, nb = 0, ans = 0;
	sort(v, v+n);
	FOR(i, n) {
		if (v[i].c == 'w') nw++;
		else nb++;
		while(i+1 < n && v[i+1].x == v[i].x) {
			i++;
			if (v[i].c == 'w') nw++;
			else nb++;
		}
		ans = max(ans, max(nb+tw-nw, nw+tb-nb));
	}
	return ans;
}

int main() {
	scanf("%d", &n);
	FOR(i, n) {
		scanf("%d %d %c", &v[i].x, &v[i].y, &v[i].c);
		if (v[i].c == 'w') tw++;
		else tb++;
	}
	int ans = solve();
	FOR(i, n) swap(v[i].x, v[i].y);
	ans = max(ans, solve());
	printf("%d\n", ans);
	return 0;
}
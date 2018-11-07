#include <bits/stdc++.h>
#define MAXN 2009
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define fi first
#define se second
using namespace std;
typedef pair<int, int> ii;

int a[MAXN], b[MAXN];

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	map<int, int> cnt;
	FOR(i, n) scanf("%d", &a[i]);
	FOR(j, m) scanf("%d", &b[j]);
	FOR(i, n) FOR(j, m) cnt[b[j]-a[i]]++;
	int mans = 0;
	int ans = 0;
	for(ii p : cnt) {
		if (p.fi <= 0) continue;
		if (p.se > mans) {
			ans = p.fi;
			mans = p.se;
		}
	}
	printf("%d\n", ans);
	return 0;
}
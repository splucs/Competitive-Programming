#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(),x.end()
#define sz(x) int(x.size())
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
typedef long long ll;
#define MAXN 109

bool solve(const int k, vector<int> a) {
	int n = sz(a);
	int tot = 0;
	FOR(i, n) tot += a[i];
	if (tot&1) return false;
	int cur = k;
	FOR(i, n) {
		while(a[i] > 0 && cur > 0) {
			if (cur > a[i]) return false;
			a[i] -= cur;
			cur--;
		}
	}
	if (cur > 0) return false;
	cur = k;
	REP(i, n) {
		while(a[i] > 0 && cur > 0) {
			if (cur > a[i]) return false;
			a[i] -= cur;
			cur--;
		}
	}
	if (cur > 0) return false;
	return true;
}

int main() {
	int n;
	scanf("%d", &n);
	vector<int> a(n);
	FOR(i, n) scanf("%d", &a[i]);
	int tot = 0;
	FOR(i, n) tot += a[i];
	int ans = 0;
	FOR1(i, 100) if (solve(i, a)) ans = i;
	if (ans == 1 && tot != 2) ans = 0;
	if (ans == 0) printf("no quotation\n");
	else printf("%d\n", ans);
	return 0;
}
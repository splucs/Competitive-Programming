#include <bits/stdc++.h>
#define MAXN 100009
#define MAXM 50009
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define EPS 1e-9
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define fi first
#define se second
#define sz(x) int(x.size())
#define all(x) x.begin(),x.end()
#define mset(x, y) memset(&x, y, sizeof x)
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;

int n;
int a[MAXN], st[MAXN];
int cost[10];
vector<ii> op[10];

int ceillog(int n) {
	int ans = -1;
	while(n > 0) {
		ans++;
		n /= 2;
	}
	return ans;
}

void solve(int h, int i, int j, int k) {
	if (i == j) return;
	if (h > 0) {
		int m = (i+j) / 2;
		solve(h-1, i, m, (k/2) + (k%2));
		solve(h-1, m+1, j, k/2);
	}

	int inv = 0;
	assert(a[i-1]);
	for(int it = i; it < j; it++) {
		if (a[it] == 1) {
			inv++;
			a[it] = 0;
		}
	}
	cost[h] = max(cost[h], (j-i+1)*ceillog(inv+1));
	op[h].pb({i, j});
}

int main() {
	int n;
	scanf("%d", &n);
	FOR(i, n) a[i] = 1;
	FOR(i, 10) cost[i] = 0;
	solve(9, 1, n, 1000);
	int o = 0;
	int fullcost = 0;
	FOR(i, 10) {
		if (!op[i].empty()) o++;
		assert(sz(op[i]) <= min(n, 1000));
		fullcost += cost[i];
	}
	assert(fullcost <= 7*n);
	printf("%d\n", o);
	FOR(i, 10) {
		if (op[i].empty()) continue;
		printf("%d\n", sz(op[i]));
		for(ii p : op[i]) printf("%d %d\n", p.fi, p.se);
	}
	return 0;
}
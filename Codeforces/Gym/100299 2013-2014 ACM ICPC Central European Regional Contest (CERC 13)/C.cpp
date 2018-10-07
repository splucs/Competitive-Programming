#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define MAXLOGN 20
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
typedef long long ll;

ll ans = 0;
ll st[MAXN][MAXLOGN];

struct SparseTable {
	int sz;
	SparseTable() {}
	SparseTable(ll arr[], int _sz) : sz(_sz) {
		FOR(i, sz) st[i][0] = arr[i];
		for(int j = 1; (1<<j) <= sz; j++) {
			for(int i = 0; i + (1<<j) <= sz; i++) {
				st[i][j] = __gcd(st[i][j-1], st[i+(1<<(j-1))][j-1]);
			}
		}
	}
	ll query(int l, int r) {
		int k = (int)floor(log(r-l+1.0)/log(2.0));
		ll cur = __gcd(st[l][k], st[r-(1<<k)+1][k]);
		//printf("gcd [%d,%d] = %lld\n", l, r, cur);
		ans = max((r-l+1LL)*cur, ans);
		return cur;
	}
};

SparseTable spt;

void solve(int i, int l, ll gl, int r, ll gr) {
	if (gl == gr) return;
	if (r <= l+1) return;
	//printf("solve %d,%d\n", l, r);
	int m = (l + r) / 2;
	ll gm = spt.query(i, m);
	solve(i, l, gl, m, gm);
	solve(i, m, gm, r, gr);
}

ll arr[MAXN];

int main() {
	int T;
	scanf("%d", &T);
	FOR1(caseNo, T) {
		int n;
		scanf("%d", &n);
		FOR(i, n) scanf("%lld", &arr[i]);
		spt = SparseTable(arr, n);
		ans = 0;
		FOR(i, n) {
			int l = i, r = n-1;
			ll gl = spt.query(i, l);
			ll gr = spt.query(i, r);
			solve(i, l, gl, r, gr);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
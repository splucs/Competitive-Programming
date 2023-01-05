#include <bits/stdc++.h>
#define MAXN 100009
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define fi first
#define se second
#define mset(x, y) memset(&x, y, sizeof x)
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;

int value(ii p) {
	return min(p.fi, p.se);
}
const ii neutral(-INF, -INF);
ii join(ii a, ii b) {
	int va = value(a);
	int vb = value(b);
	if (va > vb) return a;
	else return b;
}

ii st[4*MAXN];
int lazy[4*MAXN];

struct SegmentTree {
#define left(u) (u<<1)
#define right(u) ((u<<1)+1)
	void push(int u, int l, int r) {
		st[u].se = max(st[u].se, lazy[u]);
		if (l != r) {
			lazy[left(u)] = max(lazy[left(u)], lazy[u]);
			lazy[right(u)] = max(lazy[right(u)], lazy[u]);
		}
		lazy[u] = -INF;
	}
	void update(int a, int b, int k, int u=1, int l=0, int r=MAXN-1) {
		push(u, l, r);
		if (a > r || b < l) return;
		else if (l >= a && r <= b) {
			lazy[u] = k;
			push(u, l, r); return;
		}
		int m = (l + r) / 2;
		update(a, b, k, left(u), l, m);
		update(a, b, k, right(u), m+1, r);
		st[u] = join(st[left(u)], st[right(u)]);
	}
	int query(int a, int b, int u=1, int l=0, int r=MAXN-1) {
		push(u, l, r);
		if (a > r || b < l) return value(neutral);
		if (l >= a && r <= b) return value(st[u]);
		int m = (r + l) / 2;
		int p1 = query(a, b, left(u), l, m);
		int p2 = query(a, b, right(u), m+1, r);
		return max(p1, p2);
	}
	void setdp(int i, int k, int u=1, int l=0, int r=MAXN-1) {
		push(u, l, r);
		if (l == r) {
			st[u].fi = k;
			return;
		}
		int m = (l + r) / 2;
		if (i <= m) setdp(i, k, left(u), l, m);
		else setdp(i, k, right(u), m+1, r);
		st[u] = join(st[left(u)], st[right(u)]);
	}
	SegmentTree() {
		FOR(i, 4*MAXN) {
			st[i] = neutral;
			lazy[i] = -INF;
		}
	}
};

SegmentTree seg;

int n, L, R;
int dp[MAXN], A[MAXN];

int main() {
	scanf("%d %d %d", &n, &L, &R);
	seg.setdp(0, INF);
	FOR(i, n) {
		scanf("%d", &A[i]);
		seg.update(0, i, A[i]);
		int lb = i-R+1;
		int rb = i-L+1;
		if (lb < 0) lb = 0;

		if (rb < 0) dp[i] = -INF;
		else dp[i] = seg.query(lb, rb);

		seg.setdp(i+1, dp[i]);
	}
	printf("%d\n", dp[n-1]);
	return 0;
}
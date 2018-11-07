#include <bits/stdc++.h>
#define MAXN 100009
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define mset(x, y) memset(&x, y, sizeof x)
using namespace std;
typedef long long ll;

int a[4*MAXN];

struct SegmentTree {
	int n;
	SegmentTree(int sz = MAXN) {
		for(n = 1; n < sz; n <<= 1);
		FOR(i, 4*MAXN) a[i] = -INF;
	}
	void update(int i, int x) {
		a[i+n] = x;
		for(i += n, i >>= 1; i; i >>= 1) {
			a[i] = max(a[i<<1], a[1+(i<<1)]);
		}
	}
	int query(int l, int r) {
		int ans = -INF;
		for(l += n, r += n+1; l < r; l >>= 1, r >>= 1) {
			if (l & 1) ans = max(ans, a[l++]);
			if (r & 1) ans = max(ans, a[--r]);
		}
		return ans;
	}
};

SegmentTree st;
int h[MAXN], dh[MAXN], n, q;

int getR(int i, int H) {
	if (i == n-1 || dh[i] > H) return 0;
	int l = i;
	int r = n-1;
	while(r > l+1) {
		int m = (r + l) / 2;
		if (st.query(i, m) > H) r = m;
		else l = m;
	}
	return r-i;
}

int getL(int i, int H) {
	if (i == 0 || dh[i-1] > H) return 0;
	int l = -1;
	int r = i-1;
	while(r > l+1) {
		int m = (r + l) / 2;
		if (st.query(m, i-1) > H) l = m;
		else r = m;
	}
	return i-1-l;
}

int main() {
	scanf("%d %d", &n, &q);
	FOR(i, n) {
		scanf("%d", &h[i]);
		if (i > 0) {
			dh[i-1] = abs(h[i]-h[i-1]);
			st.update(i-1, dh[i-1]);
		}
	}
	while(q --> 0) {
		int op, i, H;
		scanf("%d %d %d", &op, &i, &H);
		i--;
		if (op == 1) {
			h[i] = H;
			if (i+1 < n) {
				dh[i] = abs(h[i]-h[i+1]);
				st.update(i, dh[i]);
			}
			if (i > 0) {
				dh[i-1] = abs(h[i]-h[i-1]);
				st.update(i-1, dh[i-1]);
			}
		}
		else {
			printf("%d\n", 1 + getR(i, H) + getL(i, H));
		}
	}
	return 0;
}
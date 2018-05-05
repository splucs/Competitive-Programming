#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define MAXM ((1e+18) + 100)
#define MOD 1000000007
#define INF 1000000009
#define EPS 1e-9
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;
#define EPS 1e-9

class SegmentTree {
	vector<int> a;
	int n;
public:
	SegmentTree() {}
	SegmentTree(int sz) {
		for (n = 1; n < sz; n <<= 1);
		a.assign(n << 1, 0);
	}
	void update(int i, int x) {
		a[i+n] = max(x, a[i+n]); //substitui
		for (i += n, i >>= 1; i; i >>= 1)
			a[i] = max(a[i<<1], a[1+(i<<1)]);
	}
	int query(int l, int r) {
		int ans = 0;
		for (l += n, r += n+1; l < r; l >>= 1, r >>= 1) {
			if (l & 1) ans = max(ans, a[l++]);
			if (r & 1) ans = max(ans, a[--r]);
		}
		return ans;
	}
};

int n, m, eu[MAXN], ev[MAXN];
ll w[MAXN];
map<ll, int> reduce[MAXN];
SegmentTree st[MAXN];

int main() {
	scanf("%d %d", &n, &m);
	FOR(j, m) {
		int u, v;
		scanf("%d %d %I64d", &u, &v, &w[j]);
		eu[j] = u; ev[j] = v;
		reduce[v][w[j]] = 0;
		reduce[u][w[j]] = 0;
	}
	FOR1(u, n) {
		int cnt = 0;
		for(auto & pp : reduce[u]) {
			pp.second = cnt++;
		}
		st[u] = SegmentTree(cnt);
	}
	int ans = 0;
	FOR(j, m) {
		int u = eu[j];
		int v = ev[j];
		int l = 0;
		int r = reduce[u][w[j]] - 1;
		int val = st[u].query(l, r) + 1;
		ans = max(ans, val);
		st[v].update(reduce[v][w[j]], val);
	}
	printf("%d\n", ans);
	return 0;
}
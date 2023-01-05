#include <bits/stdc++.h>
using namespace std;
#define MAXN 4009
#define MAXLOGN 20
#define MOD 1000000007
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define pb push_back
#define fi first
#define se second
#define sz(x) int(x.size())
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;

int m;

struct state {
	int c[20];
	state() {
		FOR(j, 20) c[j] = 0;
		c[0]++;
	}
	state(int v) {
		FOR(j, 20) c[j] = 0;
		c[0]++; c[v]++;
	}
};

state operator +(state &a, state &b) {
	state c; c.c[0] = 0;
	FOR(i, m) if (a.c[i] > 0) FOR(j, m) {
		c.c[(i+j)%m] = (c.c[(i+j)%m] + a.c[i]*1ll*b.c[j])%MOD;
	}
	return c;
}

vector<state> suff[MAXN], pref[MAXN];
int a[MAXN], n;
state st[MAXN];

void build(int u, int l, int r) {
	state cur;
	for(int i = l; i <= r; i++) {
		cur = st[i] + cur;
		pref[u].pb(cur);
	}
	cur = state();
	for(int i = r; i >= l; i--) {
		cur = st[i] + cur;
		suff[u].pb(cur);
	}
	if (l == r) return;
	int m = (l + r) / 2;
	build(u+u, l, m);
	build(u+u+1, m+1, r);
}

void query(int u, int l, int r, int a, int b, state &ans) {
	if (a > r || b < l) return;
	if (a <= l && l <= b) {
		assert(b-l < sz(pref[u]));
		ans = ans + pref[u][b-l];
	}
	else if (a <= r && r <= b) {
		assert(r-a < sz(suff[u]));
		ans = ans + suff[u][r-a];
	}
	else {
		int m = (l + r) / 2;
		query(u+u, l, m, a, b, ans);
		query(u+u+1, m+1, r, a, b, ans);
	}
}

int main() {
	scanf("%d %d", &n, &m);
	FOR(i, n) {
		scanf("%d", &a[i]);
		a[i] %= m;
		st[i] = state(a[i]);
	}
	build(1, 0, n-1);
	int q;
	scanf("%d", &q);
	while(q --> 0) {
		int l, r;
		scanf("%d %d", &l, &r);
		state ans;
		query(1, 0, n-1, l-1, r-1, ans);
		//ans.print();
		printf("%d\n", ans.c[0]);
	}
	return 0;
}
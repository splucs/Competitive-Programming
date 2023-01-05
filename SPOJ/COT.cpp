#include <bits/stdc++.h>
#define DEBUG false
#define debugf if (DEBUG) printf
#define MAXN 200309
#define MAXM 900009
#define MAXLOGN 20
#define ALFA 256
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define EPS 1e-9
#define PI 3.141592653589793238462643383279502884
#define FOR(x,n) for(int x=0; (x)<int(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=int(n); (x)++)
#define REP(x,n) for(int x=int(n)-1; (x)>=0; (x)--)
#define REP1(x,n) for(int x=(n); (x)>0; (x)--)
#define pb push_back
#define pf push_front
#define fi first
#define se second
#define mp make_pair
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define mset(x,y) memset(&x, (y), sizeof(x))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef unsigned int uint;
typedef vector<int> vi;
typedef pair<int, int> ii;

int n;
ll a[MAXN], x[MAXN];

const int neutral = 0;
#define comp(a, b) ((a)+(b))

#define MAXS 50000009
int nds, st[MAXS], ls[MAXS], rs[MAXS];

class PersistentSegmentTree {
private:
	int vroot[MAXN];
	int size, nds, nv;
	int newnode() {
		ls[nds] = rs[nds] = -1;
		st[nds++] = neutral;
		return nds-1;
	}
	void build(int p, int l, int r, int* A) {
		if (l == r) {
			st[p] = A ? A[l] : neutral;
			return;
		}
		int m = (l + r) / 2;
		build(ls[p] = newnode(), l, m, A);
		build(rs[p] = newnode(), m+1, r, A);
		st[p] = comp(st[ls[p]], st[rs[p]]);
	}
	void update(int prv, int p, int l, int r, int i, int k) {
		if (l == r) { st[p] = st[prv] + k; return; }
		int m = (l + r) / 2;
		if (i <= m) {
			rs[p] = rs[prv];
			update(ls[prv], ls[p] = newnode(), l, m, i, k);
		}
		else {
			ls[p] = ls[prv];
			update(rs[prv], rs[p] = newnode(), m+1, r, i, k);
		}
		st[p] = comp(st[ls[p]], st[rs[p]]);
	}
	int query(int u, int v, int w, int p, int l, int r, int k) {
		//printf("%d to %d\n", x[l], x[r]);
		if (l == r) return r;
		int m = (l + r) / 2;
		int val = st[u] + st[v] - st[w] - (p == -1 ? 0 : st[p]);
		int lval = st[ls[u]] + st[ls[v]] - st[ls[w]] - (p == -1 ? 0 : st[ls[p]]);
		//printf("val = %d, lval = %d (<=%d)\n", val, lval, x[m]);
		//assert(k <= val);
		if (k <= lval) return query(ls[u], ls[v], ls[w], p == -1 ? -1 : ls[p], l, m, k);
		else return query(rs[u], rs[v], rs[w], p == -1 ? -1 : rs[p], m+1, r, k-lval);
	}
public:
	PersistentSegmentTree(int _size = 1) {
		nds = nv = 0; size = _size;
		vroot[nv++] = newnode();
		build(vroot[0], 0, size-1, NULL);
	}
	int query(int vu, int vv, int vw, int vp, int k) {
		vu = vroot[vu]; vv = vroot[vv];
		vw = vroot[vw]; vp = vroot[vp];
		if (vw == vp) vp = -1;
		return query(vu, vv, vw, vp, 0, size-1, k);
	}
	int update(int i, int v, int k) {
		vroot[nv++] = newnode();
		update(vroot[v], vroot[nv-1], 0, size-1, i, k);
		return nv-1;
	}
};

vi g[MAXN];
PersistentSegmentTree pst;
int ver[MAXN];

int level[MAXN], N;
int P[MAXN][MAXLOGN];

void depthdfs(int u, int pver) {
	ver[u] = pst.update(a[u], pver, 1);
	//printf("node %d, pos %d(%d)\n", u, a[u], x[a[u]]);
	FOR(i, sz(g[u])) {
		int v = g[u][i];
		if (v == P[u][0]) continue;
		P[v][0] = u;
		level[v] = 1 + level[u];
		depthdfs(v, ver[u]);
	}
}

int LCA(int u, int v) {
	if (level[u] > level[v]) swap(u, v);
	int d = level[v] - level[u];
	int ans = neutral;
	for(int i = 0; i < MAXLOGN; i++) {
		if (d & (1<<i)) v = P[v][i];
	}
	if (u == v) return u;
	for(int i = MAXLOGN-1; i >= 0; i--)
		while(P[u][i] != P[v][i]) {
			u = P[u][i]; v = P[v][i];
		}
	return P[u][0];
}

ll search(int u, int v, int k) {
	int w = LCA(u, v);
	int p = P[w][0];
	//printf("u,v,w,p = %d,%d,%d,%d k = %d\n", u, v, w, p, k);
	return x[pst.query(ver[u], ver[v], ver[w], ver[p], k)];
}

int main() {
	int q;
	scanf("%d %d", &n, &q);
	map<ll, int> reduce;
	FOR1(i, n) {
		scanf("%lld", &a[i]);
		reduce[a[i]] = 0;
	}
	int cnt = 0;
	for(map<ll, int>::iterator it = reduce.begin(); it != reduce.end(); it++) {
		x[cnt] = it->fi;
		it->se = cnt++;
	}
	FOR1(i, n) a[i] = reduce[a[i]];
	FOR(j, n-1) {
		int u, v;
		scanf("%d %d", &u, &v);
		g[u].pb(v);
		g[v].pb(u);
	}
	int root = 1;
	level[root] = 0;
	P[root][0] = root;
	pst = PersistentSegmentTree(cnt);
	depthdfs(root, 0);
	for(int j = 1; j < MAXLOGN; j++)
		for(int i = 1; i <= n; i++) {
			P[i][j] = P[P[i][j-1]][j-1];
		}
	FOR1(qt, q) {
		int u, v, k;
		scanf("%d %d %d", &u, &v, &k);
	//	printf("query %d %d %d\n", u, v, k);
		printf("%lld\n", search(u, v, k));
	}
	return 0;
}
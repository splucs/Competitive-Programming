#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define MAXM ((1e+18) + 100)
#define MOD 1000000007
#define INF (1<<30)
#define EPS 1e-9
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;

class SegmentTree {
	vector<ii> a;
	int n;
public:
	SegmentTree(int sz) {
		for (n = 1; n < sz; n <<= 1);
		a.assign(n << 1, ii(0, -1));
		for(int i=n+sz-1; i; i--)
			a[i>>1] = max(a[i>>1], a[i]);
	}
	void update(int i, int x) {
		a[i+n] = ii(x, i); //substitui
		for (i += n, i >>= 1; i; i >>= 1)
			a[i] = max(a[i<<1], a[1+(i<<1)]);
	}
	ii query(int l, int r) {
		ii ans = ii(0, -1);
		for (l += n, r += n+1; l < r; l >>= 1, r >>= 1) {
			if (l & 1) ans = max(ans, a[l++]);
			if (r & 1) ans = max(ans, a[--r]);
		}
		return ans;
	}
};

map<char, int> g[MAXN];
int cnt, depth[MAXN], N;
bool leaf[MAXN];
SegmentTree st(MAXN);

int newnode(int h) {
	++N;
	depth[N] = h;
	leaf[N] = false;
	g[N].clear();
	return N;
}

void insert(int u, char *s) {
	char c = s[0];
	if (!c) {
		leaf[u] = true;
		return;
	}
	if (!g[u].count(c)) {
		int v = newnode(depth[u]+1);
		g[u][c] = v;
	}
	insert(g[u][c], s+1);
}

int pre[MAXN];

void dfs(int u) {
	int l = pre[u] = ++cnt;
	for(auto & pp : g[u]) {
		int v = pp.second;	
		dfs(v);
	}
	int r = cnt;
	if (depth[u] == 0) return;
	if (!leaf[u]) {
		int i = st.query(l, r).second;
		st.update(i, depth[u]);
	}
	else {
		st.update(pre[u], depth[u]);
	}
}

char buffer[MAXN];

int main () {
	cnt = 0;
	int M;
	scanf("%d", &M);
	N = 0;
	int root = newnode(0);
	FOR(j, M) {
		scanf(" %s", buffer);
		insert(root, buffer);
	}
	dfs(root);
	ll ans = 0;
	FOR1(u, N) {
		ans += st.query(u, u).first;
	}
	printf("%I64d\n", ans);
	return 0;
}
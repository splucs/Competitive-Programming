#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009
#define MAXM MAXN*MAXN
#define MAXLOGN 22
#define INF 0x3f3f3f3f
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define fi first
#define se second
#define mset(x, y) memset(&x, y, sizeof x);
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;

char field[MAXN][MAXN];
int n;
int dp[MAXN][MAXN], mx[MAXM];
int pos[MAXN][MAXN], x[MAXM], y[MAXM], cnt;

inline bool rec(int i1, int j1, int i2, int j2) {
	if (i1 == 0 || j1 == 0) return false;
	return dp[i2][j2] - dp[i2][j1-1] - dp[i1-1][j2] + dp[i1-1][j1-1] == 0;
}

void computedp() {
	FOR(i, n+2) {
		FOR(j, n+2) {
			if (i == 0 || j == 0 || i == n+1 || j == n+1) field[i][j] = '#';
			if (i == 0 && j == 0) dp[i][j] = 1;
			else if (i == 0) dp[i][j] = 1 + dp[i][j-1];
			else if (j == 0) dp[i][j] = 1 + dp[i-1][j];
			else {
				dp[i][j] = dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1];
				if (field[i][j] == '#') dp[i][j]++;
			}
			//printf("%2d ", dp[i][j]-i-j-1);
		}
		//printf("\n");
	}
}

void computemx() {
	FOR1(i, n) {
		FOR1(j, n) {
			int u = pos[i][j];
			int k = (i > 1) ? mx[pos[i-1][j]]-1 : -1;
			if (k < -1) k = -1;
			while(rec(i-k-1, j-k-1, i+k+1, j+k+1)) k++;
			mx[u] = k;
			//printf("%2d ", k);
		}
		//printf("\n");
	}
}

vector<int> getadj(int u) {
	int i = x[u];
	int j = y[u];
	vi ans;
	if (i > 1) ans.pb(pos[i-1][j]);
	if (j > 1) ans.pb(pos[i][j-1]);
	return ans;
}

vi g[MAXM];

struct UnionFind {
	vector<int> par;
	UnionFind(int n = 0) {
		par.resize(++n);
		FOR(i, n) par[i] = i;
	}
	int find(int i) {
		if (i == par[i]) return i;
		return par[i] = find(par[i]);
	}
	bool isSameSet(int i, int j) {
		return find(i) == find(j);
	}
	void unionSet(int i, int j) {
		par[find(i)] = find(j);
	}
};

bool in[MAXM];
int P[MAXM][MAXLOGN], depth[MAXM];
int D[MAXM][MAXLOGN];

UnionFind uf;

void kruskal() {
	uf = UnionFind(cnt);
	priority_queue< pair<int, ii> > pq;
	FOR1(u, cnt) {
		g[u].clear();
		vi adj = getadj(u);
		for(int v : adj) {
			int w = min(mx[u], mx[v]);
			if (w == -1) continue;
			pq.push({w, {u, v}});
		}
	}
	while(!pq.empty()) {
		int u = pq.top().se.fi;
		int v = pq.top().se.se;
		pq.pop();
		if (!uf.isSameSet(u, v)) {
			uf.unionSet(u, v);
			g[u].pb(v);
			g[v].pb(u);
		}
	}
}

void dfs(int u, int p, int h) {
	assert(P[u][0] == -1);
	P[u][0] = p;
	D[u][0] = min(mx[u], mx[p]);
	depth[u] = h;
	//printf("%d\n", )
	
	//printf("edge (%d,%d)%d->(%d,%d)%d: %d\n", x[p], y[p], depth[p], x[u], y[u], depth[u], D[u][0]);
	for(int v : g[u]) {
		if (v == p) continue;
		dfs(v, u, h+1);
	}
}

int la(int & u, int i) {
	int ans = INF;
	FOR(j, MAXLOGN) {
		if (!(i & (1<<j))) continue;
		ans = min(ans, D[u][j]);
		u = P[u][j];
	}
	return ans;
}

int query(int u, int v) {
	int ans = INF;
	//printf("depth %d-%d\n", depth[u], depth[v]);
	if (depth[u] > depth[v]) {
		ans = min(ans, la(u, depth[u]-depth[v]));
	}
	if (depth[u] < depth[v]) {
		ans = min(ans, la(v, depth[v]-depth[u]));
	}
	if (u == v) return ans;
	//printf("not ancestral\n");
	REP(j, MAXLOGN) {
		if (P[u][j] != P[v][j]) {
			ans = min(ans, D[u][j]);
			ans = min(ans, D[v][j]);
			u = P[u][j];
			v = P[v][j];
		}
	}
	ans = min(ans, D[u][0]);
	ans = min(ans, D[v][0]);
	return ans;
}

int main() {
	scanf("%d", &n);
	FOR1(i, n) scanf(" %s", field[i] + 1);
	cnt = 0;
	FOR1(i, n) {
		FOR1(j, n) {
			pos[i][j] = ++cnt;
			x[cnt] = i;
			y[cnt] = j;
			//printf("%c ", field[i][j]);
		}
		//printf("\n");
	}
	computedp();
	computemx();
	kruskal();
	mset(P, -1);
	FOR1(u, cnt) {
		if (P[u][0] == -1) {
			dfs(u, u, 0);
		}
	}
	FOR1(j, MAXLOGN-1) FOR1(u, cnt) {
		P[u][j] = P[P[u][j-1]][j-1];
		D[u][j] = min(D[P[u][j-1]][j-1], D[u][j-1]);
	}
	int q;
	scanf("%d", &q);
	while(q --> 0) {
		int i1, j1, i2, j2;
		scanf("%d %d %d %d", &i1, &j1, &i2, &j2);
		int u = pos[i1][j1];
		int v = pos[i2][j2];
		//printf("query (%d,%d)-(%d,%d)\n", x[u], y[u], x[v], y[v]);
		int ans;
		if (!uf.isSameSet(u, v)) ans = 0;
		else ans = 2*query(u, v)+1;
		printf("%d\n", ans);
	}
	return 0;
}
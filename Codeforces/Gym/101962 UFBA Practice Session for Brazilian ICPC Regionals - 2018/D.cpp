#include <bits/stdc++.h>
#define MAXN 2009
#define MAXM 100009
#define MOD 1000000007
#define INF 0x3f3f3f3f
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

struct edge {int v, ac, inv;};

vector<edge> dir[MAXN], rev[MAXN];

void add(int u, int v) {
	int invv = dir[u].size();
	int invu = rev[v].size();
	dir[u].pb({v, 1, invu});
	rev[v].pb({u, 1, invv});
}

int q[MAXN], n, m;
bool vis[MAXN];
set<ii> candidates;

bool bfs(int s, vector<edge> g[], bool find) {
	FOR1(i, n) vis[i] = false;
	int en = 0;
	q[en++] = s;
	vis[s] = true;
	FOR(st, en) {
		int u = q[st], v;
		FOR(i, sz(g[u])) {
			edge e = g[u][i];
			v = e.v;
			if (!e.ac || vis[v]) continue;
			vis[v] = true;
			q[en++] = v;
			if (find) {
				if (g == dir) candidates.insert({u, i});
				else candidates.insert({v, e.inv});
			}
		}
	}
	FOR1(i, n) {
		if (!vis[i]) return false;
	}
	return true;
}


int main() {
	scanf("%d %d", &n, &m);
	FOR(i, m) {
		int u, v;
		scanf("%d %d", &u, &v);
		add(u, v);
	}

	assert(bfs(1, dir, true));
	assert(bfs(1, rev, true));

	set<ii> ans;
	for(ii p : candidates) {
		int u = p.fi;
		int i = p.se;
		edge &e = dir[u][i];
		int v = e.v;
		e.ac = 0;
		rev[v][e.inv].ac = 0;
		if (!bfs(1, dir, false) || !bfs(1, rev, false)) {
			ans.insert({u, v});
		}
		e.ac = 1;
		rev[v][e.inv].ac = 1;
	}

	printf("%u\n", ans.size());
	for(ii p : ans) printf("%d %d\n", p.fi, p.se);
	return 0;
}
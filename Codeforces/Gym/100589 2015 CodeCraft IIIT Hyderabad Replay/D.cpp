#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define MAXN 100009
#define MAXLOGN 20
#define fi first
#define se second
#define mset(x, y) memset(&x, y, sizeof x)
typedef long long ll;
typedef pair<ll, int> ii;

vector<ii> g[MAXN];
int n;
int num[MAXN], label[MAXN], dist[MAXN], depth[MAXN];
int P[MAXN][MAXLOGN];
bool incycle[MAXN];
vector<int> cycle;
vector<ll> cycled;
int pos[MAXN];

vector<int> callstack;
void findcycle(int u, int p) {
	callstack.pb(u);
	num[u] = 1;
	for(ii pp : g[u]) {
		int v = pp.se;
		if (v == p) continue;
		if (num[v] == 2) continue;
		else if (num[v] == 1) {
			int j = callstack.size()-1;
			while(callstack[j] != v) {
				incycle[callstack[j]] = true;
				cycle.pb(callstack[j]);
				j--;
			}
			incycle[callstack[j]] = true;
			cycle.pb(callstack[j]);
		}
		else if (num[v] == 0) findcycle(v, u);
	}
	callstack.pop_back();
	num[u] = 2;
}

void dfs(int u, int p, int lbl, ll d, int h) {
	label[u] = lbl;
	P[u][0] = p;
	dist[u] = d;
	depth[u] = h;
	for(ii pp : g[u]) {
		ll w = pp.fi;
		int v = pp.se;
		if (incycle[v] || v == p) continue;
		dfs(v, u, lbl, d+w, h+1);
	}
}

int LA(int u, int i) {
	FOR(j, MAXLOGN) {
		if (i & (1<<j)) u = P[u][j];
	}
	return u;
}

int LCA(int u, int v) {
	assert(label[u] == label[v]);
	if (depth[u] > depth[v]) u = LA(u, depth[u] - depth[v]);
	if (depth[u] <depth[v]) v = LA(v, depth[v] - depth[u]);
	if (u == v) return u;
	REP(j, MAXLOGN) {
		if (P[u][j] != P[v][j]) {
			u = P[u][j];
			v = P[v][j];
		}
	}
	return P[u][0];
}

void computeP() {
	FOR1(j, MAXLOGN-1) FOR1(i, n) {
		P[i][j] = P[P[i][j-1]][j-1];
	}
}

ll dist(int u, int v) {
	if (label[u] == label[v]) {
		return dist[u] + dist[v] - 2*dist[LCA(u, v)];
	}
	ll ans = dist[u] + dist[v];

}

void processcycle() {
	FOR(i, sz(cycle)) {
		
	}
}

int main() {

}
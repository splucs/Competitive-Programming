#include <queue>
#include <list>
using namespace std;
typedef pair<int, int> ii;

/*
 * MAX QUEUE
 */

class MaxQueue {
	list<ii> q, l;
	int cnt = 0;
public:
	MaxQueue() : cnt(0) {}
	void push(int x) {
		ii cur = ii(x, cnt++);
		while(!l.empty() && l.back() <= cur) l.pop_back();
		q.push_back(cur);
		l.push_back(cur);
	}
	int front() { return q.front().first; }
	void pop() {
		if (q.front().second == l.front().second) l.pop_front();
		q.pop_front();
	}
	int max() { return l.front().first; }
	int size() { return q.size(); }
};

/*
 * Codeforces 980F
 */

#include <bits/stdc++.h>
#define DEBUG false
#define debugf if (DEBUG) printf
#define MAXN 500309
#define MAXM 300009
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define EPS 1e-9
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define ROF(x,n) for(int x=(n)-1; (x)>=0; (x)--)
#define ROF1(x,n) for(int x=(n); (x)>0; (x)--)
#define pb push_back
#define pf push_front
#define fi first
#define se second
#define all(x) x.begin(), x.end()
typedef vector<int> vi;
typedef long long ll;

int n, m;
vi g[MAXN], st;
int cycle[MAXN], num[MAXN], pos[MAXN], par[MAXN];
int cnt = 0;
vi cycles[MAXN];
int down[MAXN], up[MAXN];

void buildcycles(int u, int p) {
	num[u] = 1;
	pos[u] = st.size();
	st.pb(u);
	for(int v : g[u]) {
		if (v == p) continue;
		else if (num[v] == 1 && cycle[u] == -1) {
			cycles[cnt].clear();
			for(int i = pos[v]; i <= pos[u]; i++) {
				cycle[st[i]] = cnt;
				cycles[cnt].pb(st[i]);
			}
			cnt++;
		}
		else if (num[v] == 0) {
			buildcycles(v, u);
			if (cycle[u] == -1 || cycle[v] != cycle[u]) par[v] = u;
		}
	}
	num[u] = 2;
	st.pop_back();
}

int find(vi & v, int u) {
	FOR(i, int(v.size())) {
		if (v[i] == u) return i;
	}
	return -1;
}

int nodedown(int u);

int cycledown(int u) {
	if (down[u] != -1) return down[u];
	int c = cycle[u];
	if (c == -1) return nodedown(u);
	vi & arr = cycles[c];
	int sz = arr.size();
	nodedown(u);
	int j = find(arr, u);
	assert(j != -1);
	FOR(i, sz) {
		int d = abs(i-j);
		if (i == j) continue;
		down[u] = max(down[u], min(d, sz-d) + nodedown(arr[i]));
	}
	return down[u];
}

int nodedown(int u) {
	if (down[u] != -1) return down[u];
	down[u] = 0;
	for(int v : g[u]) {
		if (v == par[u]) continue;
		if (cycle[u] != -1 && cycle[u] == cycle[v]) continue;
		down[u] = max(down[u], 1 + cycledown(v));
	}
	return down[u];
}

void solve(vi & L, vi & Z) {
	int sz = L.size();
	int k = sz/2;
	FOR(i, sz) L.pb(L[i]);
	vi left = L, right = L;
	FOR(i, 2*sz) left[i] += i;
	FOR(i, 2*sz) right[i] += 2*sz-i-1;
	Z.assign(sz, 0);
	MaxQueue q;
	for(int i = 0; i < sz; i++) {
		q.push(right[i]);
	}
	while(q.size() > k) q.pop();
	for(int i = sz; i < 2*sz; i++) {
		Z[i-sz] = max(Z[i-sz], q.max() - (2*sz-i-1));
		q.push(right[i]);
		q.pop();
	}
	q = MaxQueue();
	for(int i = 2*sz-1; i >= sz; i--) {
		q.push(left[i]);
	}
	while(q.size() > k) q.pop();
	for(int i = sz-1; i >= 0; i--) {
		Z[i] = max(Z[i], q.max() - i);
		q.push(left[i]);
		q.pop();
	}
}

void nodeup(int u, int d);

void cycleup(int u, int d) {
	int c = cycle[u];
	if (c == -1) {
		nodeup(u, d);
		return;
	}
	cycledown(u);
	vi & arr = cycles[c];
	int sz = arr.size();
	up[u] = d;
	int j = find(arr, u);
	assert(j != -1);
	vi L(sz), Z;
	int daux = d;
	for(int v : g[u]) {
		if (v == par[u]) continue;
		if (cycle[u] != -1 && cycle[u] == cycle[v]) continue;
		daux = max(daux, 1 + nodedown(v));
	}
	FOR(i, sz) {
		if (i == j) L[i] = daux;
		else L[i] = nodedown(arr[i]);
	}
	solve(L, Z);
	FOR(i, sz) {
		if (i == j) nodeup(arr[i], max(Z[i], d));
		else nodeup(arr[i], Z[i]);
	}
}

void nodeup(int u, int d) {
	up[u] = d;
	nodedown(u);
	int sz = g[u].size();
	int x = d, y = -1;
	for(int v : g[u]) {
		if (v == par[u]) continue;
		if (cycle[u] != -1 && cycle[u] == cycle[v]) continue;
		if (x >= y && 1+nodedown(v) > y) y = 1+down[v];
		else if (x < y && 1+nodedown(v) > x) x = 1+down[v];
	}
	for(int v : g[u]) {
		if (v == par[u]) continue;
		if (cycle[u] != -1 && cycle[u] == cycle[v]) continue;
		if (1+nodedown(v) == max(x, y))
			cycleup(v, min(x, y)+1);
		else cycleup(v, max(x, y)+1);
	}
}

int main() {
	scanf("%d %d", &n, &m);
	FOR(j, m) {
		int u, v;
		scanf("%d %d", &u, &v);
		g[u].pb(v);
		g[v].pb(u);
	}
	memset(&cycle, -1, sizeof cycle);
	memset(&down, -1, sizeof down);
	memset(&up, -1, sizeof up);
	memset(&num, 0, sizeof num);
	buildcycles(1, -1);
	cycleup(1, 0);
	FOR1(u, n) {
		printf("%d ", max(up[u], down[u]));
	}
	printf("\n");
	return 0;
}
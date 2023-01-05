#include <bits/stdc++.h>
using namespace std;
#define MAXN 409
#define MAXM 100009
#define MAXLOGN 20
#define INF 0x3f3f3f3f
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define fi first
#define se second
#define pb push_back
#define mset(x, y) memset(&x, y, sizeof x)
typedef long long ll;
typedef pair<int, int> ii;

int ned, first[MAXN], work[MAXN];
int cap[MAXM], to[MAXM], nxt[MAXM], dist[MAXN];

void init() {
	mset(first, -1);
	ned = 0;
}

void add(int u, int v, int f) {
	to[ned] = v; cap[ned] = f;
	nxt[ned] = first[u];
	first[u] = ned++;

	to[ned] = u; cap[ned] = 0;
	nxt[ned] = first[v];
	first[v] = ned++;
}

int dfs(int u, int f, int s, int t) {
	if (u == t) return f;
	int v, df;
	for(int &e = work[u]; e != -1; e = nxt[e]) {
		v = to[e];
		if (dist[v] == dist[u] + 1 && cap[e] > 0) {
			int df = dfs(v, min(f, cap[e]), s, t);
			if (df > 0) {
				cap[e] -= df;
				cap[e^1] += df;
				return df;
			}
		}
	}
	return 0;
}

int q[MAXN];

bool bfs(int s, int t) {
	int u, v;
	mset(dist, -1);
	dist[s] = 0;
	int en = 0;
	q[en++] = s;
	FOR(st, en) {
		u = q[st];
		for(int e = first[u]; e != -1; e = nxt[e]) {
			v = to[e];
			if (dist[v] < 0 && cap[e] > 0) {
				dist[v] = 1 + dist[u];
				q[en++] = v;
			}
		}
	}
	return dist[t] >= 0;
}

int dinic(int s, int t) {
	int ans = 0, f;
	while(bfs(s, t)) {
		memcpy(work, first, sizeof work);
		while(f = dfs(s, INF, s, t)) ans += f;
	}
	return ans;
}

char field[MAXN][MAXN];
int nid[MAXN][MAXN];

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	init();
	int cnt = 0;
	int s = ++cnt;
	int t = ++cnt;
	FOR(i, n) {
		scanf(" %s", field[i]);
		FOR(j, m) nid[i][j] = ++cnt;
	}
	int f1 = 0, f2 = 0;
	FOR(i, n) FOR(j, m) {
		if (i+1 < n && (i+j)%2 == 0) {
			add(nid[i][j], nid[i+1][j], 2);
		}
		if (i+1 < n && (i+j)%2 != 0) {
			add(nid[i+1][j], nid[i][j], 2);
		}
		if (j+1 < m && (i+j)%2 == 0) {
			add(nid[i][j], nid[i][j+1], 2);
		}
		if (j+1 < m && (i+j)%2 != 0) {
			add(nid[i][j+1], nid[i][j], 2);
		}
		int df = (field[i][j] == '-') ? 2 : 1;
		if ((i+j) % 2 == 0) {
			add(s, nid[i][j], df);
			f1 += df;
		}
		else {
			add(nid[i][j], t, df);
			f2 += df;
		}
	}
	bool ok = (f1 == f2);
	if (f1 != dinic(s, t)) ok = false;
	puts(ok ? "Y" : "N");
	return 0;
}
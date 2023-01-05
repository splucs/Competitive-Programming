#include <bits/stdc++.h>
using namespace std;
#define MAXN 60009
#define MAXM 60009
#define INF 0x3f3f3f3f
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef pair<int, int> ii;

int ned, first[MAXN], work[MAXN];
int cap[MAXM], to[MAXM], nxt[MAXM], dist[MAXN];

void init(int n) {
	FOR1(u, n) first[u] = -1;
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
			df = dfs(v, min(f, cap[e]), s, t);
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

bool bfs(int s, int t, int n) {
	int u, v;
	FOR1(i, n) dist[i] = -1;
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

int dinic(int s, int t, int n) {
	int ans = 0, f;
	while(bfs(s, t, n)) {
		FOR1(i, n) work[i] = first[i];
		while(f = dfs(s, INF, s, t)) ans += f;
	}
	return ans;
}

int eid[MAXN], nid[MAXN], deg[MAXN];
int ed[MAXN], col[MAXN];

int main() {
	int T;
	scanf("%d", &T);
	FOR1(caseNo, T) {
		int n, m, k;
		scanf("%d %d %d", &n, &m, &k);
		int cnt = 0;
		int s = ++cnt;
		int t = ++cnt;
		FOR1(i, n) {
			nid[i] = ++cnt;
			deg[i] = 0;
		}
		FOR1(j, m) {
			eid[j] = ++cnt;
			ed[cnt] = j;
		}
		init(cnt);
		FOR1(j, m) {
			int u, v;
			scanf("%d %d", &u, &v);
			add(eid[j], t, 1);
			add(nid[u], eid[j], 1);
			add(nid[v], eid[j], 1);
			deg[u]++;
			deg[v]++;
		}
		int f = 0;
		FOR1(i, n) {
			if (deg[i] > k) {
				int df = 2*(deg[i]-k);
				add(s, nid[i], df);
				f += df;
			}
		}
		f -= dinic(s, t, cnt);
		FOR1(j, m) col[j] = 0;
		if (f == 0) {
			int ncol = 0;
			FOR1(i, n) {
				int par = 0;
				int u = nid[i];
				for(int e = first[u]; e != -1; e = nxt[e]) {
					int v = to[e];
					int j = ed[v];
					if (cap[e] == 0) {
						if (par) col[j] = ncol, par = 0;
						else col[j] = ++ncol, par = 1;
					}
				}
			}
			FOR1(j, m) if (!col[j]) col[j] = ++ncol;
		}
		FOR1(j, m) printf("%d ", col[j]);
		printf("\n");
	}
	return 0;
}
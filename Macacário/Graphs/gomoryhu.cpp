#include <queue>
#include <cstring>
using namespace std;
#define MAXN 3009
#define MAXM 200009
#define INF (1<<30)

/*
 * Edmonds-Karp's Algorithm - O(VE^2)
 */

int N, M, ned, prv[MAXN], first[MAXN];
int cap[MAXM], to[MAXM], nxt[MAXM], dist[MAXN];

void init() {
   memset(first, -1, sizeof first);
   ned = 0;
}

void add(int u, int v, int f) {
    to[ned] = v, cap[ned] = f;
    nxt[ned] = first[u];
    first[u] = ned++;
    
    to[ned] = u, cap[ned] = 0;
    nxt[ned] = first[v];
    first[v] = ned++;
}

int augment(int v, int minEdge, int s) {
	int e = prv[v];
	if (e == -1) return minEdge;
	int f = augment(to[e^1], min(minEdge, cap[e]), s);
	cap[e] -= f;
	cap[e^1] += f;
	return f;
}

bool bfs(int s, int t) {
	int u, v;
	memset(&dist, -1, sizeof dist);
	dist[s] = 0;
	queue<int> q; q.push(s);
	memset(&prv, -1, sizeof prv);
	while (!q.empty()) {
		u = q.front(); q.pop();
		if (u == t) break;
		for(int e = first[u]; e!=-1; e = nxt[e]) {
			v = to[e];
			if (dist[v] < 0 && cap[e] > 0) {
				dist[v] = dist[u] + 1;
				q.push(v);
				prv[v] = e;
			}
		}
	}
	return dist[t] >= 0;
}

int edmondskarp(int s, int t) {
	int result = 0;
	while (bfs(s, t)) {
		result += augment(t, INF, s);
	}
	return result;
}

/*
 * Gomory Hu Tree / Gusfield's Algorithm - O((V-1)*(Flow Algorithm))
 */

typedef pair<int, int> ii;
int par[MAXN], fpar[MAXN];	//parent in tree, flow to parent
int backup[MAXM];			//backup for cap
bool inCut[MAXN];
vector<ii> ghtree[MAXN];

void cutGraph(int s) {
	inCut[s] = true;
	for(int e = first[s]; e!=-1; e = nxt[e]) {
		int v = to[e];
		if (!inCut[v] && cap[e] > 0) {
			cutGraph(v);
		}
	}
}

int computeMinCut(int s, int t) {
	memcpy(backup, cap, sizeof cap);
	memset(inCut, false, sizeof inCut);
	int f = edmondskarp(s, t);
	cutGraph(s);
	memcpy(cap, backup, sizeof cap);
	return f;
}

//1-indexed
void gomoryhu() {
	for (int i = 1; i <= N; i++) par[i] = 1;
	for (int s = 2; s <= N; s++) {
		int t = par[s];
		fpar[s] = computeMinCut(s, t);
		for (int u = s+1; u <= N; u++) {
			if (par[u] == t && inCut[u]) {
				par[u] = s;
			}
			if (par[t] == u && inCut[u]) {
				par[s] = u; par[t] = s;
				swap(fpar[s], fpar[t]);
			}
		}
	}
	for (int i = 1; i <= N; i++) ghtree[i].clear();
	for (int i = 1; i <= N; i++) {
		if (par[i] == i) continue;
		ghtree[i].push_back(ii(fpar[i], par[i]));
		ghtree[par[i]].push_back(ii(fpar[i], i));
	}
}

/*
 * Codeforces 101480J
 */
#include <cstdio>

int dfs(int u, int prv, int k) {
	int ans = 0, v, w;
	for (int i = 0; i < (int)ghtree[u].size(); i++) {
		v = ghtree[u][i].second;
		w = ghtree[u][i].first;
		if (v == prv) continue;
		ans += min(k, w);
		ans += dfs(v, u, min(k, w));
	}
	return ans;
}

int main() {
	int a, b;
	scanf("%d %d", &N, &M);
	init();
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &a, &b);
		add(a, b, 1);
		add(b, a, 1);
	}
	gomoryhu();
	int ans = 0;
	for (int i = 1; i <= N; i++) {
		ans += dfs(i, -1, INF);
	}
	printf("%d\n", ans/2);
}
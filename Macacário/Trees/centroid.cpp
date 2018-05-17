#include <cstring>
#include <vector>
#include <iostream>
using namespace std;
#define MAXN 500009
#define INF (1LL<<60)

typedef long long ll;
typedef pair<ll, int> ii;
int clevel[MAXN], cpar[MAXN], csize[MAXN];
vector<int> csons[MAXN];
vector<ii> adjList[MAXN];
int N, K;

int subsize(int u, int p) {
	csize[u]=1;
	for(int i=0; i<(int)adjList[u].size(); i++) {
		int v = adjList[u][i].second;
		if (v != p && clevel[v] < 0)
			csize[u] += subsize(v, u);
	}
	return csize[u];
}
int findcentroid(int u, int p, int nn) {
	for(int i=0; i<(int)adjList[u].size(); i++) {
		int v = adjList[u][i].second;
		if (v != p && clevel[v] < 0 && csize[v] > nn/2)
			return findcentroid(v, u, nn);
	}
	return u;
}
int decompose(int root, int par) {
	subsize(root, -1);
	int u = findcentroid(root, -1, csize[root]);
	cpar[u] = par;
	clevel[u] = par >= 0 ? clevel[par]+1 : 0;
	csize[u] = 1;
	for(int i=0; i<(int)adjList[u].size(); i++) {
		int v = adjList[u][i].second;
		if (v != par && clevel[v] < 0) {
			v = decompose(v, u);
			csons[u].push_back(v);
			csize[u] += csize[v];
		}
	}
	return u;
}
int centroiddecomposition(int root) {
	memset(&clevel, -1, sizeof clevel);
	for(int i=0; i<=N; i++) csons[i].clear();
	return decompose(root, -1);
}

/*
 * Codeforces 101040J
 */

#include <cstdio>

vector<ll> cost(MAXN), subs(MAXN);
int limit;
ll depth[MAXN];

void dfs(int u, int par, int h) {
	while(cost.size() < h+1) cost.push_back(INF);
	cost[h] = min(cost[h], depth[u]);
	for(int i=0; i<(int)adjList[u].size(); i++) {
		int v = adjList[u][i].second;
		ll w = adjList[u][i].first;
		if (clevel[v] <= limit || v == par) continue;
		depth[v] = depth[u] + w;
		dfs(v, u, h+1);
	}
}

ll merge() {
	ll ans = INF;
	while(subs.size() < cost.size()) subs.push_back(INF);
	for(int i=0; i<(int)cost.size(); i++) {
		int j = K-i;
		if (j >= 0 && j < (int)subs.size()) ans = min(ans, subs[j] + cost[i]);
	}
	for(int i=0; i<(int)cost.size(); i++) {
		subs[i] = min(subs[i], cost[i]);
	}
	return ans;
}

ll solve(int u) {
	ll ans = INF;
	for(int i=0; i<(int)csons[u].size(); i++) {
		int v = csons[u][i];
		ans = min(ans, solve(v));
	}
	subs.clear();
	subs.push_back(0);
	limit = clevel[u];
	for(int i=0; i<(int)adjList[u].size(); i++) {
		int v = adjList[u][i].second;
		ll w = adjList[u][i].first;
		if (clevel[v] <= limit) continue;
		depth[v] = depth[u] + w;
		cost.clear();
		dfs(v, u, 1);
		ans = min(ans, merge());
	}
	return ans;
}
int main() {
	scanf("%d %d", &N, &K);
	int P;
	ll C, ans;
	for(int i=2; i<=N; i++) {
		scanf("%d %I64d", &P, &C);
		adjList[i].push_back(ii(C, P));
		adjList[P].push_back(ii(C, i));
	}
	int root = centroiddecomposition(1);
	ans = solve(root);
	if (ans < INF) printf("%I64d\n", ans);
	else printf("-1\n");
	return 0;
}
#include <bits/stdc++.h>
using namespace std;
#define MAXN 500009
#define INF (1LL<<60)

typedef long long ll;
typedef pair<int, ll> ii;
vector<ii> adjList[MAXN];
vector<ll> costs[MAXN];
ll depth[MAXN], ans;
int N, K;

ll merge(int u, int v){
	vector<ll> & vu = costs[u];
	vector<ll> & vv = costs[v];
	ll mincost = INF;
	if (vv.size() > vu.size()) vu.swap(vv);
	for(int j=0; j<(int)vv.size(); j++) {
		int dj = vv.size() - j - 1;
		int i = vu.size() - (K-dj) - 1;
		if (i >= 0 && i < (int)vu.size()) {
			mincost = min(mincost, vv[j] + vu[i]);
		}
	}
	for(int j=0; j<(int)vv.size(); j++) {
		int d = vv.size() - j - 1;
		int i = vu.size() - d - 1;
		vu[i] = min(vu[i], vv[j]);
	}
	return mincost;
}

void dfs(int u, int par){
	costs[u].clear();
	costs[u].push_back(depth[u]);
	ll mincost = INF;
	for(int i=0; i<(int)adjList[u].size(); i++) {
		int v = adjList[u][i].first;
		ll w = adjList[u][i].second;
		if (v == par) continue;
		depth[v] = depth[u] + w;
		dfs(v, u);
		costs[v].push_back(INF);
		mincost = min(mincost, merge(u, v));
	}
	if (mincost < INF) ans = min(ans, mincost - 2*depth[u]);
}

int main(){
	scanf("%d %d", &N, &K);
	int P;
	ll C;
	for(int i=2; i<=N; i++){
		scanf("%d %I64d", &P, &C);
		adjList[i].push_back(ii(P, C));
		adjList[P].push_back(ii(i, C));
	}
	depth[1] = 0;
	ans = INF;
	dfs(1, -1);
	if (ans == INF) printf("-1\n");
	else printf("%I64d\n", ans);
	return 0;
}
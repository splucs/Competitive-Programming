#include <bits/stdc++.h>
using namespace std;
#define MAXN 500009
#define INF (1LL << 60)
#define UNVISITED -1
#define EXPLORING -2
#define DONE -3

typedef pair<int, int> ii;
vector<ii> adjList[MAXN];
int points[MAXN];
typedef long long ll;
ll val[MAXN], ans;
int vis[MAXN];

map<ll, int> x2id;
int N = 0;
int getnode(ll x) {
	if (!x2id.count(x)) {
		x2id[x] = ++N;
		val[N] = x;
		vis[N] = UNVISITED;
		adjList[N].clear();
		points[N] = -1;
	}
	return x2id[x];
}

void setpoints(int u, int v, int vi) {
	if (points[u] != -1) return;
	points[u] = v;
	//printf("%I64d points to %I64d\n", val[u], v >= 0 ? val[v] : -1);
	vis[u] = DONE;
	ans += val[v];
	for (int i = 0, v; i < (int)adjList[u].size(); i++) {
		int w = adjList[u][i].first;
		if (i == vi) continue;
		setpoints(w, u, adjList[u][i].second);
	}
}

bool findcycle(int u, int p, int pi) {
	vis[u] = EXPLORING;
	for (int i = 0, v; i < (int)adjList[u].size(); i++) {
		v = adjList[u][i].first;
		if (v == p && adjList[u][i].second == pi) continue;
		if (vis[v] == EXPLORING) { 
			//printf("%I64d and %I64d are in a cycle\n", val[u], val[v]);
			setpoints(u, v, i);
			return true;
		}
		else if (vis[v] == UNVISITED){
			if (findcycle(v, u, i)) {
				vis[u] = DONE;
				return true;
			}
		}
	}
	vis[u] = DONE;
	return false;
}

int getmin(int u, int p) {
	int ans = u;
	for (int i = 0, v; i < (int)adjList[u].size(); i++) {
		v = adjList[u][i].first;
		if (v == p) continue;
		int cur = getmin(v, u);
		if (val[cur] > val[ans]) ans = cur;
	}
	return ans;
}

int main() {
	int n;
	while(scanf("%d", &n)!=EOF) {
		N = 0;
		x2id.clear();
		for(int j=0; j<n; j++) {
			ll w1, w2;
			scanf("%I64d %I64d", &w1, &w2);
			int u = getnode(w1);
			int v = getnode(w2);
			int szu = adjList[u].size();
			int szv = adjList[v].size();
			adjList[u].push_back(ii(v, szv));
			adjList[v].push_back(ii(u, szu));
		}
		
		ans = 0;
		val[0] = 0;
		for(int u=1; u<=N; u++) {
			if (vis[u] == UNVISITED) {
				if (!findcycle(u, -1, -1)) {
					//printf("%I64d belongs to no cycle\n", val[u]);
					int mn = getmin(u, -1);
					setpoints(mn, 0, -1);
				}
			}
		}
		
		printf("%I64d\n", ans);
	}
	return 0;	
}
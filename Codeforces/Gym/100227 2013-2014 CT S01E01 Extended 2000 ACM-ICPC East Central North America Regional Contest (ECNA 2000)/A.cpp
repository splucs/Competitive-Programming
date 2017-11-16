#include <bits/stdc++.h>
using namespace std;
#define INF (1LL<<60)
#define MAXN 29

class UnionFind {
private:
	vector<int> parent, rank;
public:
	UnionFind(int N) {
		rank.assign(N+9, 0);
		parent.assign(N+9, 0);
		for (int i = 0; i < N; i++) parent[i] = i;
	}
	int find(int i) {
		while(i != parent[i]) i = parent[i];
		return i;
	}
	bool isSameSet(int i, int j) {
		return find(i) == find(j);
	}
	void unionSet (int i, int j) {
		if (isSameSet(i, j)) return;
		int x = find(i), y = find(j);
		if (rank[x] > rank[y]) parent[y] = x;
		else {
			parent[x] = y;
			if (rank[x] == rank[y]) rank[y]++;
		}
	}
};

typedef pair<int, int> ii;
typedef long long ll;

int N, M, K;
ll dist[MAXN][MAXN];
vector< ii > edgeList, specialEdges; // (weight, two vertices) of the edge

bool comp(ii a, ii b) {
	return dist[a.first][a.second] < dist[b.first][b.second];
}

ll kruskal(int mask){
	ll cost = 0;
	UnionFind uf(N);
	int u, v, cnt = 0;
	for(int i=0; i<(int)specialEdges.size(); i++) {
		if (mask & (1<<i)) {
			cnt++;
			u = specialEdges[i].first;
			v = specialEdges[i].second;
			cost += dist[u][v];
			uf.unionSet(u, v);
		}
	}
	if (cnt > K) return INF;
	for (int i = 0; i < (int)edgeList.size(); i++) {
		u = edgeList[i].first;
		v = edgeList[i].second;
		if (!uf.isSameSet(u, v)) { 
			cost += dist[u][v];
			uf.unionSet(u, v);
		}
	}
	for(int i=0; i<N; i++) {
		if (!uf.isSameSet(0, i)) return INF;
	}
	return cost;
}

char buffer[MAXN];
map<string, int> mp;

int main() {
	int u, v;
	ll w;
	scanf("%d", &M);
	N = 0;
	string cur;
	mp[string("Park")] = N++;
	for(int i=0; i<MAXN; i++) {
		for(int j=0; j<MAXN; j++) {
			dist[i][j] = INF;
		}
	}
	for(int i=0; i<M; i++) {
		scanf(" %s", buffer);
		cur = buffer;
		if (!mp.count(cur)) mp[cur] = N++;
		u = mp[cur];
		scanf(" %s", buffer);
		cur = buffer;
		if (!mp.count(cur)) mp[cur] = N++;
		v = mp[cur];
		scanf("%I64d", &w);
		if (dist[u][v] == INF) {
			if (u == 0 || v == 0) {
				specialEdges.push_back(ii(u, v));
			}
			else edgeList.push_back(ii(u, v));
		}
		dist[u][v] = min(dist[u][v], w);
		dist[v][u] = dist[u][v];
	}
	sort(edgeList.begin(), edgeList.end(), comp);
	scanf(" %d", &K);
	ll ans = INF;
	for(int mask = 0; mask < (1<<specialEdges.size()); mask++) {
		ans = min(ans, kruskal(mask));
	}
	printf("Total miles driven: %I64d\n", ans);
	return 0;
}
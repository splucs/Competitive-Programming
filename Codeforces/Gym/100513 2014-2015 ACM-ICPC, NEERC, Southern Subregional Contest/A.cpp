#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define MAXS 319

typedef pair<int, int> ii;

class UnionFind {
private:
	vector<int> parent, rank, odd;
	stack<ii> rk, pr, od;
public:
	UnionFind(int N) {
		rank.assign(N+1, 0);
		parent.assign(N+1, 0);
		odd.assign(N+1, 0);
		for (int i = 0; i <= N; i++) {
			parent[i] = i;
			odd[i] = 0;
		}
	}
	ii find(int i) {
		int p = 0;
		while(i != parent[i]) {
			p ^= odd[i];
			i = parent[i];
		}
		return ii(i, p);
	}
	bool isSameSet(int i, int j) {
		return find(i).first == find(j).first;
	}
	bool sameParity(int i, int j) {
		return find(i).second == find(j).second;
	}
	bool unionSet (int i, int j) {
		if (isSameSet(i, j)) {
			return !sameParity(i, j);
		}
		ii px = find(i), py = find(j);
		int x = px.first, ox = px.second;
		int y = py.first, oy = py.second;
		if (rank[x] > rank[y]) {
			pr.push(ii(y, parent[y]));
			parent[y] = x;
			od.push(ii(y, odd[y]));
			odd[y] = ox^oy^1;
		}
		else {
			pr.push(ii(x, parent[x]));
			parent[x] = y;
			od.push(ii(x, odd[x]));
			odd[x] = ox^oy^1;
			if (rank[x] == rank[y]) {
				rk.push(ii(y, rank[y]));
				rank[y]++;
			}
		}
		return true;
	}
	void reset() {
		while(!rk.empty()) {
			rank[rk.top().first] = rk.top().second;
			rk.pop();
		}
		while(!od.empty()) {
			odd[od.top().first] = od.top().second;
			od.pop();
		}
		while(!pr.empty()) {
			parent[pr.top().first] = pr.top().second;
			pr.pop();
		}
	}
	void save() {
		while(!rk.empty()) rk.pop();
		while(!od.empty()) od.pop();
		while(!pr.empty()) pr.pop();
	}
	
};

int eu[MAXN], ev[MAXN], N, M, sm, Q;
bool ans[MAXN];
vector<ii> queries[MAXN][MAXS];
UnionFind uf(1);

void solvequeries(int l, int r, int bl) {
	for(int k=0; k<(int)queries[l][bl].size(); k++) {
		while(r < queries[l][bl][k].first) {
			r++;
			if(!uf.unionSet(eu[r], ev[r])) return;
		}
		ans[queries[l][bl][k].second] = true;
	}
}

void solveblock(int bl) {
	uf = UnionFind(N);
	int r = min(bl*sm, M);
	for(int l=r; l > 0; l--) {
		if(!uf.unionSet(eu[l], ev[l])) return;
		uf.save();
		solvequeries(l, r, bl);
		uf.reset();
	}
}

void blockquery(int l, int r, int id) {
	uf.reset();
	for(int i=l; i<=r; i++) {
		if (!uf.unionSet(eu[i], ev[i])) return;
	}
	ans[id] = true;
}

int main() {
	int u, v;
	scanf("%d %d %d", &N, &M, &Q);
	sm = sqrt(M);
	uf = UnionFind(N);
	memset(&ans, false, sizeof ans);
	for(int i=1; i<=M; i++) {
		scanf("%d %d", &eu[i], &ev[i]);
	}
	for(int q=1; q<=Q; q++) {
		scanf("%d %d", &u, &v);
		if (u/sm == v/sm) blockquery(u, v, q);
		else queries[u][v/sm].push_back(ii(v, q));
	}
	for(int i=1; i<=M; i++) {
		for(int j=0; j<MAXS; j++) {
			sort(queries[i][j].begin(), queries[i][j].end());
		}
	}
	for(int j=1; j<MAXS; j++) {
		solveblock(j);
	}
	for(int q=1; q<=Q; q++) {
		if (ans[q]) printf("Possible\n");
		else printf("Impossible\n");
	}
	return 0;
}
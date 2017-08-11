#include <bits/stdc++.h>
using namespace std;
#define MAXN 30009

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

struct edge {
	int u, v, p, r;
	int id;
	bool operator < (edge o) {
		if (r != o.r) return r < o.r;
		return p < o.p;
	}
};

typedef long long ll;

int N, M;
edge edgeList[MAXN]; // (weight, two vertices) of the edge

ll kruskal(){
	ll cost = 0;
	UnionFind UF(N);
	edge ed;
	sort(edgeList, edgeList + M);
	for (int i = M-1; i >=0; i--) {
		ed = edgeList[i];
		if (!UF.isSameSet(ed.u, ed.v)) { 
			cost += ed.p;
			UF.unionSet(ed.u, ed.v);
		}
	}
	return cost;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	map<int, int> mp;
	scanf("%d", &M);
	int a, b, r, p;
	N = 0;
	for(int i=0; i<M; i++) {
		scanf("%d %d %d %d", &a, &b, &r, &p);
		if (!mp.count(a)) mp[a] = N++;
		if (!mp.count(b)) mp[b] = N++;
		edgeList[i].u = mp[a];
		edgeList[i].v = mp[b];
		edgeList[i].id = i+1;
		edgeList[i].r = r;
		edgeList[i].p = p;
	}
	printf("%I64d\n", kruskal());
	for(int i=0; i<M; i++) {
		printf("%d ", edgeList[i].id);
	}
	printf("\n");
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}
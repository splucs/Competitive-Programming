#include <bits/stdc++.h>
using namespace std;

class UnionFind {
private:
	vector<int> parent, rank;
public:
	UnionFind(int N) {
		rank.assign(N, 0);
		parent.assign(N, 0);
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

UnionFind uf(1);

int main() {
	int N, M, Q, A, B;
	bool hasprinted = false;
	while(scanf("%d %d %d", &N, &M, &Q) != EOF) {
		if (hasprinted) printf("\n");
		hasprinted = true;
		uf = UnionFind(N);
		while(M-->0){
			scanf("%d %d", &A, &B);
			uf.unionSet(A-1, B-1);
		}
		while(Q-->0) {
			scanf("%d %d", &A, &B);
			if (uf.isSameSet(A-1, B-1)) printf("S\n");
			else printf("N\n");
		}
	}
	return 0;
}
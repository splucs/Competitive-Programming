#include <cstdio>
#include <vector>
using namespace std;

class UnionFind {
private:
	vector<int> parent, rank;
public:
	UnionFind(int N) {
		rank.assign(N+1, 0);
		parent.assign(N+1, 0);
		for (int i = 0; i <= N; i++) parent[i] = i;
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

int main() {
	int a, b;
	char c;
	UnionFind uf(100009);
	while(scanf(" %c %d %d", &c, &a, &b)!=EOF) {
		if (c=='U' || c=='u') {
			uf.unionSet(a,b);
		}
		else if (c=='i' || c=='I') {
			if (uf.isSameSet(a,b)) printf("yes\n");
			else printf("no\n");
		}
		else break;
	}
	return 0;
}
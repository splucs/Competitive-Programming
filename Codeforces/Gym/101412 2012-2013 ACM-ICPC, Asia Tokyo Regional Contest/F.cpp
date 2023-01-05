#include <bits/stdc++.h>
using namespace std;
typedef double ld;
#define EPS 1e-9
typedef pair<int, int> ii;

class UnionFind {
private:
	vector<int> parent;
	vector<long long> distance;
public:
	UnionFind(int N) {
		parent.assign(N+1, 0);
		distance.assign(N+1, 0);
		for (int i = 0; i <= N; i++) parent[i] = i;
	}
	int find(int i) {
		if (parent[i] == i) return i;
		int r = find(parent[i]);
		distance[i] += distance[parent[i]];
		parent[i] = r;
		return r;
	}
	bool isSameSet(int i, int j) {
		return find(i) == find(j);
	}
	long long dist(int i, int j) {
		return distance[j] - distance[i];
	}
	void unionSet (int i, int j, long long val) {
		if (isSameSet(i, j)) return;
		int r1 = find(i), r2 = find(j);
		val += distance[i] - distance[j];
		distance[r2] = val;
		parent[r2] = r1;
	}
};

int main() {
	int n, m, a, b;
	long long w;
	char op;
	while(scanf("%d %d", &n, &m) != EOF && n) {
		UnionFind uf(n+5);
		while (m--) {
			scanf(" %c %d %d", &op, &a, &b);
			if (op == '!') {
				scanf("%I64d", &w);
				uf.unionSet(a, b, w);
			} else {
				if (!uf.isSameSet(a, b)) printf("UNKNOWN\n");
				else printf("%I64d\n", uf.dist(a, b));
			}
		}
	}
}
#include <bits/stdc++.h>
using namespace std;
#define MAXN 6000009

int parent[MAXN];
char rnk[MAXN];

class UnionFind {
private:
	int nxt;
public:
	UnionFind() {
		memset(&rnk, 0, sizeof rnk);
		nxt = 1000001;
		for (int i = 0; i < MAXN; i++) parent[i] = i;
	}
	int find(int i) {
		while(i != parent[i]) i = parent[i];
		return i;
	}
	int par(int i) {
		int ans = 0;
		while(i != parent[i]) i = parent[i], ans ^= 1;
		return ans;
	}
	bool isSameSet(int i, int j) {
		return find(i) == find(j);
	}
	bool unionSet (int i, int j) {
		if (isSameSet(i, j)) {
			return par(i) != par(j);
		}
		int x = find(i), y = find(j);
		int pi = par(i), pj = par(j);
		if (pi == pj) {
			if (rnk[x] > rnk[y]) parent[y] = x;
			else {
				parent[x] = y;
				if (rnk[x] == rnk[y]) rnk[y]++;
			}
		}
		else {
			int cur = nxt++;
			if (rnk[x] > rnk[y]) {
				parent[y] = cur;
				rnk[cur] = 1 + rnk[y];
				parent[cur] = x;
				if (rnk[cur] == rnk[x]) rnk[x]++;
			}
			else if (rnk[x] < rnk[y]) {
				parent[x] = cur;
				rnk[cur] = 1 + rnk[x];
				parent[cur] = y;
				if (rnk[cur] == rnk[y]) rnk[y]++;
			}
			else {
				parent[x] = cur;
				parent[y] = cur;
				rnk[cur] = 1 + rnk[x];
			}
		}
		return true;
	}
};

UnionFind uf;

int main(){	
	freopen("meciul.in", "r", stdin);
	freopen("meciul.out", "w", stdout);
	
	int T, N, M, u, v;
	scanf("%d", &T);
	while (T --> 0){
		scanf("%d %d", &N, &M);
		uf = UnionFind();
		for(int j=0; j<M; j++) {
			scanf("%d %d", &u, &v);
			if (uf.unionSet(u, v)) printf("YES\n");
			else printf("NO\n");
		}
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}
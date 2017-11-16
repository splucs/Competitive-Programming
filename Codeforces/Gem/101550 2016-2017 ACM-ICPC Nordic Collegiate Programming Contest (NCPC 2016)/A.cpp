#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009
#define MAXQ 10009

int ans = 0;
int pos[MAXN][MAXN], N, M, Q, mat[MAXN][MAXN];

class UnionFind {
private:
	vector<int> parent, rank;
public:
	UnionFind(int sz) {
		ans = sz;
		rank.assign(sz+1, 0);
		parent.assign(sz+1, 0);
		for (int i = 0; i <= sz; i++) parent[i] = i;
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
		ans--;
		int x = find(i), y = find(j);
		if (rank[x] > rank[y]) parent[y] = x;
		else {
			parent[x] = y;
			if (rank[x] == rank[y]) rank[y]++;
		}
	}
};

int x_1[MAXQ], x_2[MAXQ], y_1[MAXQ], y_2[MAXQ];
UnionFind uf(1);

bool valid(int i, int j) {
	if (i < 1 || j < 1 || i > N || j > M) return false;
	return mat[i][j] == 0;
}

int di[4] = {0, 1, 0, -1};
int dj[4] = {1, 0, -1, 0};

void refresh(int i, int j) {
	if (!valid(i, j)) return;
	for(int k=0; k<4; k++) {
		int ni = i + di[k];
		int nj = j + dj[k];
		if (!valid(ni, nj)) continue;
		uf.unionSet(pos[i][j], pos[ni][nj]);
	}
}

int main() {
	scanf("%d %d %d", &N, &M, &Q);
	
	memset(&mat, 0, sizeof mat);
	int nblack = 0;
	for(int q=1; q<=Q; q++) {
		scanf("%d %d %d %d", &x_1[q], &y_1[q], &x_2[q], &y_2[q]);
		if (x_2[q] < x_1[q]) swap(x_1[q], x_2[q]);
		if (y_2[q] < y_1[q]) swap(y_1[q], y_2[q]);
		for(int i=x_1[q]; i<=x_2[q]; i++) {
			for(int j=y_1[q]; j<=y_2[q]; j++) {
				mat[i][j]++;
				if (mat[i][j] == 1) nblack++; 
			}
		}
	}
	
	for(int i=1, k=0; i<=N; i++) {
		for(int j=1; j<=M; j++) {
			pos[i][j] = ++k;
		}
	}
	
	uf = UnionFind(N*M);
	for(int i=1; i<=N; i++) {
		for(int j=1; j<=M; j++) {
			refresh(i, j);
		}
	}
	
	stack<int> s;
	for(int q=Q; q>0; q--) {
		s.push(ans - nblack);
		for(int i=x_1[q]; i<=x_2[q]; i++) {
			for(int j=y_1[q]; j<=y_2[q]; j++) {
				mat[i][j]--;
				if (mat[i][j] == 0) nblack--; 
			}
		}
		for(int i=x_1[q]; i<=x_2[q]; i++) {
			for(int j=y_1[q]; j<=y_2[q]; j++) {
				refresh(i, j);
			}
		}
	}
	
	while(!s.empty()) {
		printf("%d\n", s.top());
		s.pop();
	}
	
	return 0;
	
}
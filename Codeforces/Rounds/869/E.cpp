#include <bits/stdc++.h>
using namespace std;
#define T 3

class FenwickTree2D {
private:
	vector< vector<int> > ft;
public:
	FenwickTree2D() {}
	FenwickTree2D(int n, int m) {
		ft.assign(n + 1, vector<int>(m + 1, 0));	//1-indexed
	}
	int rsq(int i, int j) { // returns RSQ((1,1), (i,j))
		int sum = 0, _j = j;
		while(i > 0) {
			j = _j;
			while(j > 0) {
				sum ^= ft[i][j];
				j -= (j & -j);
			}
			i -= (i & -i);
		}
		return sum;
	}
	void update(int x1, int y1, int x2, int y2, int v) {
		update(x1, y1, v);
		update(x1, y2+1, v);
		update(x2+1, y1, v);
		update(x2+1, y2+1, v);
	}
	void update(int i, int j, int v) {
		int _j = j;
		while(i < (int)ft.size()) {
			j = _j;
			while(j < (int)ft[i].size()) {
				ft[i][j] ^= v;
				j += (j & -j);
			}
			i += (i & -i);
		}
	}
};

#define MAXN 2509
FenwickTree2D ft[T];

int main() {
	int N, M, Q, t, x1, x2, y1, y2;
	scanf("%d %d %d", &N, &M, &Q);
	for(int i=0; i<T; i++) ft[i] = FenwickTree2D(N, M);
	while(Q --> 0) {
		scanf("%d %d %d %d %d", &t, &x1, &y1, &x2, &y2);
		if (t == 1) {
			for(int i=0; i<T; i++) ft[i].update(x1, y1, x2, y2, rand());
		}
		else if (t == 2) {
			for(int i=0; i<T; i++) {
				int v1 = ft[i].rsq(x1-1, y1);
				int v2 = ft[i].rsq(x1, y1);
				ft[i].update(x1, y1, x2, y2, v1^v2);
			}
		}
		else if (t == 3) {
			bool ok = true;
			for(int i=0; i<T; i++) {
				int v1 = ft[i].rsq(x1, y1);
				int v2 = ft[i].rsq(x2, y2);
				ok = ok && (v1 == v2);
			}
			if (ok) printf("Yes\n");
			else printf("No\n");
		}
	}
	return 0;
}
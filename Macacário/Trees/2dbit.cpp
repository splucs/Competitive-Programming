#include <vector>
using namespace std;

const int neutral = 0;
#define comp(a, b) ((a)+(b))

class FenwickTree2D {
private:
	vector< vector<int> > ft;
public:
	FenwickTree2D(int n, int m) {
		ft.assign(n + 1, vector<int>(m + 1, 0));	//1-indexed
	}
	int rsq(int i, int j) { // returns RSQ((1,1), (i,j))
		int sum = 0, _j = j;
		while(i > 0) {
			j = _j;
			while(j > 0) {
				sum = comp(sum, ft[i][j]);
				j -= (j & -j);
			}
			i -= (i & -i);
		}
		return sum;
	}
	void update(int i, int j, int v) {
		int _j = j;
		while(i < (int)ft.size()) {
			j = _j;
			while(j < (int)ft[i].size()) {
				ft[i][j] = comp(v, ft[i][j]);
				j += (j & -j);
			}
			i += (i & -i);
		}
	}
};

/*
 *	TEST MATRIX
 */
#include <cstdio>
#include <algorithm>

vector< vector<int> > A;

int rsq(int x, int y) {
	int ans = neutral;
	for(int i=1; i<=x; i++) {
		for(int j=1; j<=y; j++) {
			ans = comp(ans, A[i][j]);
		}
	}
	return ans;
}

void update(int x, int y, int v) {
	A[x][y] += v;
}

bool test() {
	int N = 500, nTests = 10000;
	int x, y, v;
	A.resize(N+1);
	for(int i=1; i<=N; i++) A[i].resize(N+1);
	FenwickTree2D ft(N, N);
	for(int i=1; i<=N; i++) {
		for(int j=1; j<=N; j++) {
			A[i][j] = rand() % N;
			ft.update(i, j, A[i][j]);
		}
	}
	printf("starting tests...\n");
	for(int q=1; q<=nTests; q++) {
		x = rand()%N + 1;
		y = rand()%N + 1;
		v = rand()%N;
		ft.update(x, y, v);
		update(x, y, v);
		x = rand()%N + 1;
		y = rand()%N + 1;
		int q1 = rsq(x, y);
		int q2 = ft.rsq(x, y);
		if (q1 != q2) {
			printf("Failed test %d, q1 = %d, q2 = %d\n", q, q1, q2);
			return false;
		}
	}
	printf("all tests passed\n");
	return true;
}

int main() {
	test();
	return 0;
}

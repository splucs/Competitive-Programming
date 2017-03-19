#include <cstdio>
#include <map>
#include <vector>
using namespace std;
#define MAXN 1009

int dp[MAXN][MAXN];

int comp(int a, int b) {
	return a + b;
}

class FenwickTree {
private:
	vector<int> ft;
public:
	FenwickTree(int n) {
		ft.assign(n + 1, 0);	//1-indexed
	}
	int rsq(int i) { // returns RSQ(1, i)
		int sum = 0;
		while (i > 0) {
			sum = comp(sum, ft[i]);
			i -= (i & -i);
		}
		return sum;
	}
	void update(int i, int v) {
		while (i < (int)ft.size()) {
			ft[i] = comp(v, ft[i]);
			i += (i & -i);
		}
	}
};

void solve(int * arr, int N, int M) {
	for (int i = 1; i <= N; i++) dp[i][1] = 1;
	for (int p = 2; p <= M; p++) {
		FenwickTree ft(N);
		for (int i = 2; i <= N; i++) {
			ft.update(arr[i - 1], dp[i - 1][p - 1]);
			dp[i][p] = ft.rsq(arr[i] - 1);
		}
	}
}
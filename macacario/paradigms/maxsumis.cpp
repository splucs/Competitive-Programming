#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#define MAXN 100009
using namespace std;

int comp(int a, int b) {
	return max(a, b);
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

int arr[MAXN], A[MAXN];
int rank[MAXN], invrank[MAXN], N;

bool rankcomp(int a, int b) {
	//if (arr[a] == arr[b]) return a<b;	//crescente
	if (arr[a] == arr[b]) return a>b;	//estritamente crescente
	else return arr[a] < arr[b];
}

int MSIS() {
	for (int i = 1; i <= N; i++) invrank[i] = i;
	sort(invrank + 1, invrank + 1 + N, &rankcomp);
	for (int i = 1; i <= N; i++) rank[invrank[i]] = i;
	memset(&A, 0, sizeof A);
	FenwickTree ft(N);
	for (int i = 1, j; i <= N; i++) {
		j = rank[i];
		A[j] = arr[i] + ft.rsq(j - 1);
		ft.update(j, A[j]);
	}
	return ft.rsq(N);
}
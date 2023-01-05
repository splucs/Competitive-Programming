#include <vector>
#include <algorithm>
#define INF (1<<30)
using namespace std;

/*
 * Merge Sort Tree
 */

class MergeSortTree {
private:
	vector< vector<int> > st;
	int size;
	#define left(p) (p << 1)
	#define right(p) ((p << 1) + 1)
	void build(int p, int l, int r, int* A) { // O(n)
		st[p].resize(r-l+1);
		if (l == r) { st[p][0] = A[l]; return; }
		int pl = left(p), pr = right(p), m = (l+r)/2;
		build(pl, l, m, A);
		build(pr, m+1, r, A);
		merge(st[pl].begin(), st[pl].end(),
			st[pr].begin(), st[pr].end(),
			st[p].begin());
	}
	int query(int p, int l, int r, int i, int j, int a, int b) {
		if (j < l || i > r) return 0;
		if (i <= l && j >= r)
			return upper_bound(st[p].begin(), st[p].end(), b) -
				lower_bound(st[p].begin(), st[p].end(), a);
		int m = (l + r) / 2;
  		return query(left(p), l, m, i, j, a, b) +
			query(2*p+1, m+1, r, i, j, a, b);
	}
public:
	MergeSortTree(int* begin, int* end) {
		size = (int)(end-begin);
		st.assign(4*size, vector<int>());
		build(1, 0, size-1, begin);
	}
	int query(int i, int j, int a, int b) {
		return query(1, 0, size-1, i, j, a, b);
	}
};

/*
 * TEST MATRIX
 */

#include <cstdio>


int vet[100009], aux[100009];
int query(int i, int j, int a, int b) {
	int ans = 0;
	for(int k=i; k<=j; k++) if (a <= vet[k] && vet[k] <= b) ans++;
	return ans;
}

bool test(int N) {
	for(int i = 0; i < N; i++) vet[i] = rand()%N;
	MergeSortTree st(vet, vet+N);
	for(int q=0, a, b, i, j, n; q<N; q++) {
		a = rand()%N;
		b = rand()%N;
		if (a>b) swap(a, b);
		i = rand()%N;
		j = rand()%N;
		if (i>j) swap(i, j);

		if (query(i, j, a, b) != st.query(i, j, a, b)) {
			printf("test %d failed\n", q+1);
			return false;
		}
	}
	printf("all tests passed\n");
	return true;
}

int main() {
	test(10000);
	return 0;
}

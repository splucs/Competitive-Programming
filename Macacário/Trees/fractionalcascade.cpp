#include <vector>
#include <algorithm>
#define INF (1<<30)
using namespace std;

/*
 * Merge Sort Tree
 */

class MergeSortTree {
private:
	vector< vector<int> > st, li, ri;
	int size;
	#define left(p) (p << 1)
	#define right(p) ((p << 1) + 1)
	void build(int p, int l, int r, int* A) { // O(n)
		st[p].resize(r-l+1);
		if (l == r) { st[p][0] = A[l]; return; }
		int pl = left(p), pr = right(p), m = (l+r)/2;
		vector<int> &vl = st[pl], &vr = st[pr];
		build(pl, l, m, A);
		build(pr, m+1, r, A);
		merge(st[pl].begin(), st[pl].end(),
			st[pr].begin(), st[pr].end(),
			st[p].begin());
		for(int k = 0, i = 0, j = 0; k < r-l+1; k++) {
			while(i < vl.size() && st[p][k] > vl[i]) i++;
			while(j < vr.size() && st[p][k] > vr[j]) j++;
			li[p].push_back(i), ri[p].push_back(j);
		}
		li[p].push_back(vl.size());
		ri[p].push_back(vr.size());
	}
	int query(int p, int l, int r, int i, int j, int a, int b) {
		if (j < l || i > r) return 0;
		if (i <= l && j >= r) return b-a;
		int m = (l + r) / 2;
  		return query(left(p), l, m, i, j, li[p][a], li[p][b]) +
			query(right(p), m+1, r, i, j, ri[p][a], ri[p][b]);
	}
public:
	MergeSortTree(int* begin, int* end) {
		size = (int)(end-begin);
		st.assign(4*size, vector<int>());
		li.assign(4*size, vector<int>());
		ri.assign(4*size, vector<int>());
		build(1, 0, size-1, begin);
	}
	int query(int i, int j, int a, int b) {
		a = lower_bound(st[1].begin(), st[1].end(), a) - st[1].begin();
		b = upper_bound(st[1].begin(), st[1].end(), b) - st[1].begin();
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
			printf("test %d failed [i,j]=[%d,%d] [a,b]=[%d,%d], control %d mst %d\n",
				q+1, i, j, a, b, query(i, j, a, b), st.query(i, j, a, b));
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

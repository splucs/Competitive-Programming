#include <vector>
#define INF (1<<30)
using namespace std;

class MergeSortTree { // the MergeSort tree is stored like a heap array
private:
	vector< vector<int> > st;
	int size;
	#define parent(p) (p >> 1)
	#define left(p) (p << 1)
	#define right(p) ((p << 1) + 1)
	void build(int p, int l, int r, int* A) { // O(n)
		st[p].resize(r-l+1);
		if (l == r) {
			st[p][0] = A[l];
		}
		else {
			int pl = left(p), pr = right(p), m = (l+r)/2;
			build(pl , l, m, A);
			build(pr, m+1, r, A);
			unsigned int i=0, j=0, k=0;
			while(i < st[pl].size() && j < st[pr].size()) {
				if (st[pl][i] < st[pr][j]) st[p][k++] = st[pl][i++];
				else st[p][k++] = st[pr][j++];
			}
			while(i < st[pl].size()) st[p][k++] = st[pl][i++];
			while(j < st[pr].size()) st[p][k++] = st[pr][j++];
		}
	}
	int less(int p, int l, int r, int a, int b, int k) { // O(log n)
		if (st[p][0] >= k || a > r || b < l) return 0;
		if (l >= a && r <= b) {
			l = 0; r = (int)st[p].size();
			int m;
			while(r > l + 1) {
				m = (r+l)/2;
				if (st[p][m] < k) l = m;
				else r = m;
			}
			return r;
		}
		int p1 = less(left(p), l, (l+r)/2, a, b, k);
		int p2 = less(right(p), (l+r)/2+1, r, a, b, k);
		return p1+p2;
	}
public:
	MergeSortTree(int* begin, int* end) {
		size = (int)(end-begin);
		st.assign(4*size, vector<int>());
		build(1, 0, size-1, begin);
	}
	int less(int a, int b, int k) {
		return less(1, 0, size-1, a, b, k);
	}
	int nth_element(int a, int b, int n) {
		int l = -INF, r = INF, m;
		while(r > l+1) {
			m = (r+l)/2;
			if (less(a, b, m) <= n) l = m;
			else r = m;
		}
		return l;
	}
};

/*
 *	TEST MATRIX
 */
#include <cstdio>
#include <algorithm>


int vet[100009], aux[100009];
int less(int a, int b, int k) {
	int ans = 0;
	for(int i=a; i<=b; i++) if (vet[i] < k) ans++;
	return ans;
}

int nth_element(int a, int b, int n) {
	int k=0;
	for(int i=a; i<=b; i++) {
		aux[k++] = vet[i];
	}
	sort(aux, aux+k);
	return aux[n];
}

bool test() {
	int N = 10000;
	/*for(int i=0; i<N; i++) {
		vet[i] = rand()%N;
		printf("%d ", vet[i]);
	}
	printf("\n");*/
	MergeSortTree st(vet, vet+N);
	for(int q=0, a, b, k, n; q<N; q++) {

		//printf("test #%d:\n", q+1);
		a = rand()%N;
		b = rand()%N;
		if (a>b) swap(a, b);
		k = rand()%N;

		if (less(a, b, k) != st.less(a, b, k)) {
			printf("test %d failed\n", q+1);
			return false;
		}

		a = rand()%N;
		b = rand()%N;
		if (a>b) swap(a, b);
		n = rand()%(b-a+1);

		/*printf("%d-th (%d, %d):\n", n, a, b);
		for(int i=a; i<=b; i++) {
			printf("%d ", vet[i]);
		}
		printf("\n");*/

		if (nth_element(a, b, n) != st.nth_element(a, b, n)) {
			printf("test %d failed, n = %d, nth = %d, st.nth = %d\n", q+1, n, nth_element(a, b, n), st.nth_element(a, b, n));
			return false;
		}
	}
	return true;
}

int main() {
	if (test()) {
		printf("all tests passed\n");
	}
	return 0;
}

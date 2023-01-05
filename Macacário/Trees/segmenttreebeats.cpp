#include <vector>
#include <map>
using namespace std;
#define INF 0x3f3f3f3f

/*
 * Segment Tree Beats
 */

class SegmentTreeBeats {
	vector<int> st, lazy;
	vector<int> val[2], cnt[2];
	int size;
#define left(p) (p << 1)
#define right(p) ((p << 1) + 1)
	void update(int u) {
		map<int, int> aux;
		for(int k = 0; k < 2; k++) {
			aux[val[k][left(u)]] += cnt[k][left(u)];
			aux[val[k][right(u)]] += cnt[k][right(u)];
		}
		for(int k = 0; k < 2; k++) {
			val[k][u] = aux.rbegin()->first;
			cnt[k][u] = aux.rbegin()->second;
			aux.erase(aux.rbegin()->first);
		}
		st[u] = st[left(u)] + st[right(u)];
	}
	void push(int u, int l, int r) {
		if (lazy[u] < val[0][u]) {
			st[u] -= cnt[0][u]*val[0][u];
			val[0][u] = lazy[u];
			st[u] += cnt[0][u]*val[0][u];
		}
		if (l < r) {
			lazy[left(u)] = min(lazy[left(u)], lazy[u]);
			lazy[right(u)] = min(lazy[right(u)], lazy[u]);
		}
	}
	void build(int u, int l, int r, int A[]) {
		if (l == r) {
			val[0][u] = A ? A[r] : INF; cnt[0][u] = 1;
			val[1][u] = -INF; cnt[1][u] = 0;
			st[u] = A[r]; return;
		}
		int m = (l + r) / 2;
		build(left(u), l, m, A);
		build(right(u), m+1, r, A);
		update(u);
	}
	void update(int u, int l, int r, int a, int b, int k) {
		push(u, l, r);
		if (b < l || r < a || k >= val[0][u]) return;
		if (a <= l && r <= b && val[1][u] < k) {
			lazy[u] = k;
			push(u, l, r); return;
		}
		int m = (l + r) / 2;
		update(left(u), l, m, a, b, k);
		update(right(u), m+1, r, a, b, k);
		update(u);
	}
	int query(int u, int l, int r, int a, int b) {
		push(u, l, r);
		if (b < l || r < a) return 0;
		if (a <= l && r <= b) return st[u];
		int m = (l + r) / 2;
		int p1 = query(left(u), l, m, a, b);
		int p2 = query(right(u), m+1, r, a, b);
		return p1 + p2;
	}
public:
	SegmentTreeBeats(int *bg, int *en) {
		size = int(en - bg);
		st.resize(4 * size);
		for(int k = 0; k < 2; k++) {
			val[k].resize(4 * size);
			cnt[k].resize(4 * size);
		}
		lazy.assign(4 * size, INF);
		build(1, 0, size-1, bg);
	}
	void update(int a, int b, int k) {
		update(1, 0, size-1, a, b, k);
	}
	int query(int a, int b) {
		return query(1, 0, size-1, a, b);
	}
};

/*
 * TEST MATRIX
 */

#include <cstdio>
#include <ctime>
#include <cstdlib>
#define MAXN 1000000
#define RANGE 1000
#define NQUERY 10

int arr[MAXN];

void update(int a, int b, int k) {
	for(int i = a; i <= b; i++) arr[i] = min(arr[i], k);
}

int query(int a, int b) {
	int sum = 0;
	for(int i = a; i <= b; i++) sum += arr[i];
	return sum;
}

bool test(int suits, int n) {
	srand(time(NULL));
	clock_t t = clock();
	for(int suit = 0; suit < suits; suit++) {
		for(int i = 0; i < n; i++) arr[i] = 2*RANGE;
		SegmentTreeBeats stb(arr, arr+n);
		for(int test = 0; test < n; test++) {
			int i = rand()%n;
			int j = rand()%n;
			int k = (rand()%100) + n-test;
			if (i > j) swap(i, j);
			update(i, j, k);
			stb.update(i, j, k);
			for(int q = 0; q < NQUERY; q++) {
				i = rand()%n;
				j = rand()%n;
				if (i > j) swap(i, j);
				int v2 = stb.query(i, j);
				//int v1 = v2;
				int v1 = query(i, j);
				if (v1 != v2) {
					printf("failed on test %d, query [%d,%d] => %d,%d\n", test, i, j, v1, v2);
					return false;
				}
			}
		}
	}
	t = clock() - t;
	printf("all tests passed, time %.3f\n", t*1.0/CLOCKS_PER_SEC);
	return true;
}

int main() {
	test(10, 10000);
	return 0;
}
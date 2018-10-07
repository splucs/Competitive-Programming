#include <cstdio>
#include <vector>
#include <algorithm>
#define INF (1<<30)
using namespace std;

/*
 * Lazy Propagation Segment Tree
 */

const int neutral = 0; //comp(x, neutral) = x
#define comp(a, b) ((a)+(b))

class SegmentTree {
private:
	vector<int> st, lazy;
	int size;
#define left(p) (p << 1)
#define right(p) ((p << 1) + 1)
	void build(int p, int l, int r, int* A) {
		if (l == r) { st[p] = A[l]; return; }
		int m = (l + r) / 2;
		build(left(p), l, m, A);
		build(right(p), m+1, r, A);
		st[p] = comp(st[left(p)], st[right(p)]);
	}
	void push(int p, int l, int r) {
		st[p] += (r - l + 1)*lazy[p];	//Caso RSQ
		//st[p] += lazy[p]; 		    //Caso RMQ
		if (l != r) {
			lazy[right(p)] += lazy[p];
			lazy[left(p)] += lazy[p];
		}
		lazy[p] = 0;
	}
	void update(int p, int l, int r, int a, int b, int k) {
		push(p, l, r);
		if (a > r || b < l) return;
		else if (l >= a && r <= b) {
			lazy[p] = k; push(p, l, r); return;
		}
		int m = (l + r) / 2;
		update(left(p), l, m, a, b, k);
		update(right(p), m+1, r, a, b, k);
		st[p] = comp(st[left(p)], st[right(p)]);
	}
	int query(int p, int l, int r, int a, int b) {
		push(p, l, r);
		if (a > r || b < l) return neutral;
		if (l >= a && r <= b) return st[p];
		int m = (l + r) / 2;
		int p1 = query(left(p), l, m, a, b);
		int p2 = query(right(p), m+1, r, a, b);
		return comp(p1, p2);
	}
public:
	SegmentTree(int* bg, int* en) {
		size = (int)(en - bg);
		st.assign(4 * size, neutral);
		lazy.assign(4 * size, 0);
		build(1, 0, size - 1, bg);
	}
	int query(int a, int b) { return query(1, 0, size - 1, a, b); }
	void update(int a, int b, int k) { update(1, 0, size - 1, a, b, k); }
};

/*
 * TEST MATRIX
 */

int vet[16];

int main() {
	int n, k;
	scanf("%d", &n);
	for(int i=0; i<n; i++) scanf("%d", &vet[i]);
	char c;
	int a, b;
	SegmentTree st(vet, vet+n);
	while(scanf(" %c", &c), c=='u' || c=='s' ) {
		if (c == 'u') {
			scanf("%d %d %d", &a, &b, &k);
			st.update(a, b, k);
		}
		else {
			scanf("%d %d", &a, &b);
			printf("soma(%d,%d)=%d\n", a, b, st.query(a, b));
		}
	}
	return 0;
}
#include <vector>
#include <cstdio>
using namespace std;
#define MAXN 500009
#define MAXS 2000009

/*
 * Split-merge segment tree
 */

class SegmentTree {
	int root[MAXN], sz, n;
	int s[MAXS], ls[MAXS], rs[MAXS];

	#define getsize(t) (t == -1 ? 0 : s[t])
	void print(int p) {
		if (p == -1) return;
		printf("s[%d] = %d, ls[%d] = %d, rs[%d] = %d\n", p, s[p], p, ls[p], p, rs[p]);
	}
	int newnode(int _s) {
		ls[sz] = rs[sz] = -1;
		s[sz++] = _s;
		return sz-1;
	}
	int build(int l, int r, int i) {
		int p = newnode(1);
		if (l == r) return p;
		int m = (l + r) / 2;
		if (i <= m) ls[p] = build(l, m, i);
		else rs[p] = build(m + 1, r, i);
	}
	int split(int t1, int k) {
		if (t1 == -1) return t1;
		int t2 = newnode(s[t1] - k);
		s[t1] = k;
		int sl = ls[t1] == -1 ? 0 : s[ls[t1]];
		if (k > sl) rs[t2] = split(rs[t1], k - sl);
		else swap(rs[t1], rs[t2]);
		if (k < sl) ls[t2] = split(ls[t1], k);
	}
	int merge(int t1, int t2) {
		if(t1 == -1 || t2 == -1) return t1+t2+1;
		ls[t1] = merge(ls[t1], ls[t1]);
		rs[t1] = merge(rs[t1], rs[t1]);
		s[t1] += s[t2];
		return t1;
	}
public:
	SegmentTree() { }
	SegmentTree(int *begin, int *end) {
		n = int(end - begin);
		sz = 0;
		for(int i = 0; i <= n; i++) root[i] = -1;
		for(int i = 0, x; i < n; i++) {
			x = begin[i];
			printf("adding %d to pos %d\n", x, i);
			root[x] = build(root[x], i, 0, n-1);
			printf("size of root[%d]=%d is %d\n", x, root[x], getsize(root[x]));
		}
	}
	void update(int a, int b, int x, int y) {
		int lt, mrt, mt, rt;
		split(root[x], lt, mrt, a, 0, n-1);
		split(mrt, mt, rt, b+1, 0, n-1);
		root[x] = merge(lt, rt);
		root[y] = merge(root[y], mt);
	}
	int query(int a, int b, int x) {
		int lt, mrt, mt, rt;
		printf("query(%d,%d,%d), size(root[%d]) = %d\n", a, b, x, x, s[root[x]]);
		split(root[x], lt, mrt, a, 0, n-1);
		split(mrt, mt, rt, b+1, 0, n-1);
		printf("size(lt) = %d\n", s[lt]);
		printf("size(mrt) = %d\n", s[mrt]);
		printf("size(rt) = %d\n", s[rt]);
		printf("size(mt) = %d\n", s[mt]);
		return s[mt];
	}
};

/*
 * Hackerearth Replace
 */

SegmentTree st;

int arr[MAXN];

int main() {
	int N, Q, op, a, b, x, y;
	scanf("%d %d", &N, &Q);
	for(int i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
	}
	st = SegmentTree(arr, arr+N);
	printf("seg tree built\n");
	for(int q = 0; q < Q; q++) {
		scanf("%d", &op);
		if (op == 1) {
			scanf("%d %d %d %d", &a, &b, &x, &y);
			a--; b--;
			st.update(a, b, x, y);
		}
		if (op == 2) {
			scanf("%d %d %d", &a, &b, &x);
			a--; b--;
			printf("%d\n", st.query(a, b, x));
		}
	}
	return 0;
}
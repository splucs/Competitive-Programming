#include <vector>
#include <cstdio>
using namespace std;
#define MAXN 500009
#define MAXS 2000009

/*
 * Split-merge segment tree
 */
	int root[MAXN], sz, n;
	int s[MAXS], ls[MAXS], rs[MAXS];

class SegmentTree {
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
	int build(int t, int i, int l, int r) {
		if (i < l || i > r) return t;
		printf("build %d-%d, t = %d\n", l, r, t);
		if (t == -1) t = newnode(0);
		s[t]++;
		if (l < r) {
			int m = (l + r) >> 1;
			ls[t] = build(ls[t], i, l, m);
			rs[t] = build(rs[t], i, m+1, r);
		}
		print(t);
		return t;
	}
	void split(int t, int &t1, int &t2, int i, int l, int r) {
		if (t == -1 || l == r) {
			t2 = t; t1 = -1; return;
		}
		int m = (l + r) >> 1, lt, rt;
		t1 = newnode(0); t2 = newnode(0);
		if (i > m) {
			split(rs[t], lt, rt, i, m+1, r);
			rs[t1] = lt; rs[t2] = rt;
			ls[t1] = ls[t];
		}
		else {
			split(ls[t], lt, rt, i, l, m);
			ls[t1] = lt; ls[t2] = rt;
			rs[t2] = rs[t];
		}
		s[t1] = getsize(ls[t1]) + getsize(rs[t1]);
		s[t2] = getsize(ls[t2]) + getsize(rs[t2]);
		print(t1);
		print(t2);
		printf("split %d/%d s1=%d, s2=%d\n", l, r, s[t1], s[t2]);
	}
	int merge(int t1, int t2) {
		if (t1 == -1 && t2 == -1) return -1;
		if (t1 == -1) return t2;
		if (t2 == -1) return t1;
		int t = newnode(s[t1] + s[t2]);
		rs[t] = merge(rs[t1], rs[t2]);
		ls[t] = merge(ls[t1], ls[t2]);
		print(t);
		return t;
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
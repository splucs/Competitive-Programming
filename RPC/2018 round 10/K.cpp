#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define MAXN 50009
#define MAXM 1000009
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define pb push_back
#define fi first
#define se second
#define mset(x, y) memset(&x, y, sizeof x);
typedef pair<int, int> ii;

struct matrix {
	int A[3][3];
};

matrix L[MAXM];
matrix base, zero, id;

matrix operator *(matrix & a, matrix & b) {
	matrix c = zero;
	FOR(i, 3) FOR(j, 3) FOR(k, 3) {
		c.A[i][j] = (c.A[i][j] + a.A[i][k]*1ll*b.A[k][j]) % MOD;
	}
	return c;
}

matrix operator +(matrix & a, matrix & b) {
	matrix c = zero;
	FOR(i, 3) FOR(j, 3) {
		c.A[i][j] = (a.A[i][j] + b.A[i][j]) % MOD;
	}
	return c;
}

matrix Lexp(int b) {
	if (b < MAXM) return L[b];
	matrix c = Lexp(b/2);
	c = c*c;
	if (b % 2 != 0) c = (c*base);
	return c;
}

class SegmentTree {
	vector<matrix> st;
	vector<int> lazy;
	int size;
#define left(p) (p<<1)
#define right(p) ((p<<1)+1)
	void build(int p, int l, int r, int A[]) {
		//printf("build node %d, [%d,%d]\n", p, l, r);
		if (l == r) {
			st[p] = zero;
			st[p].A[0][0] = 0;
			st[p].A[1][0] = 1;
			st[p].A[2][0] = 1;
			matrix x = Lexp(A[l]);
			st[p] = x*st[p];
		}
		else {
			int m = (l+r) / 2;
			build(left(p), l, m, A);
			build(right(p), m+1, r, A);
			st[p] = st[left(p)] + st[right(p)];
		}
		//printf("[%d,%d], st[%d] = %d\n", l, r, st[p][0][0]);
	}
	void push(int p, int l, int r) {
		matrix x = Lexp(lazy[p]);
		st[p] = x*st[p];
		if (r > l) {
			lazy[left(p)] += lazy[p];
			lazy[right(p)] += lazy[p];
		}
		lazy[p] = 0;
	}
	void update(int p, int l, int r, int a, int b, int k) {
		push(p, l, r);
		if (a > r || b < l) return;
		else if (l >= a && r <= b) {
			lazy[p] = k;
			push(p, l, r); 
			//printf("st[%d] = %d\n", p, st[p][0][0]);
			return;
		}
		int m = (l + r) / 2;
		update(left(p), l, m, a, b, k);
		update(right(p), m+1, r, a, b, k);
		st[p] = st[left(p)] + st[right(p)];
		//printf("st[%d] = %d\n", p, st[p][0][0]);
	}
	int query(int p, int l, int r, int a, int b) {
		push(p, l, r);
		if (a > r || b < l) return 0;
		if (l >= a && r <= b) return (st[p].A[0][0])%MOD;
		int m = (l + r) / 2;
		int p1 = query(left(p), l, m, a, b);
		int p2 = query(right(p), m+1, r, a, b);
		return (p1+p2)%MOD;
	}
public:
	SegmentTree() {}
	SegmentTree(int A[], int sz) {
		size = sz;
		st.resize(4*size);
		lazy.assign(4*size, 0);
		build(1, 0, size-1, A);
	}
	int query(int a, int b) {
		//printf("query [%d,%d]\n", a, b);
		return query(1, 0, size-1, a, b);
	}
	void update(int a, int b, int k) {
		//printf("update [%d,%d] += k\n", a, b, k);
		update(1, 0, size-1, a, b, k);
	}
};

int A[MAXN];
SegmentTree st;

int main() {
	matrix zero;
	FOR(i, 3) FOR(j, 3) zero.A[i][j] = 0;

	matrix id = zero;
	FOR(i, 3) id.A[i][i] = 1;

	base = zero;
	base.A[0][0] = base.A[0][1] = base.A[0][2] = 1;
	base.A[1][0] = base.A[2][1] = 1;

	L[0] = id;
	for(int i = 1; i < MAXM; i++) {
		L[i] = L[i-1]*base;
	}
	
	int T;
	scanf("%d", &T);
	FOR1(caseNo, T) {
		int n, q;
		scanf("%d", &n);
		FOR(i, n) scanf("%d", &A[i]);
		//printf("building seg tree\n");
		st = SegmentTree(A, n);
		//printf("seg tree built\n");
		scanf("%d", &q);
		while(q --> 0) {
			int op, l, r, d;
			scanf("%d %d %d", &op, &l, &r);
			l--; r--;
			if (op == 1) {
				printf("%d\n", st.query(l, r));
			}
			else {
				scanf("%d", &d);
				st.update(l, r, d);
			}
		}
	}
	return 0;
}
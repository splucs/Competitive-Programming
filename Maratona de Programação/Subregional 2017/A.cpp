#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;
#define MAXN 100009

struct freq {
	int f[9];
	freq() {
		for(int i=0; i<9; i++) f[i] = 0;
	}
	freq operator +(freq o) {
		freq q;
		for(int i=0; i<9; i++) {
			q.f[i] = f[i] + o.f[i];
		}
		return q;
	}
	int max() {
		int ans = 0;
		for(int i=1; i<9; i++) {
			if (f[i] >= f[ans]) ans = i;
		}
		return ans;
	}
	void shift(int n) {
		int tmp[9];
		for(int i=0; i<9; i++) tmp[i] = f[i];
		for(int i=0; i<9; i++) f[i] = tmp[(i-n+9)%9];
	}
};

freq st[4*MAXN];
int lazy[4*MAXN];

class SegmentTree {
	private:
	
	int size;
	#define parent(p) (p >> 1)
	#define left(p) (p << 1)
	#define right(p) ((p << 1) + 1)
	
	void build (int p, int l, int r, int *A) {
		if (l == r) {
			st[p].f[A[l]] = 1;
		} else {
			build(left(p), l, (l+r)/2, A);
			build(right(p), (l+r)/2+1, r, A);
			st[p] = st[left(p)] + st[right(p)];
		}	
	}
	void push(int p, int l, int r) {
		st[p].shift(lazy[p]);
		if (l != r) {
			lazy[right(p)] += lazy[p];
			lazy[left(p)] += lazy[p];
			lazy[right(p)] %= 9;
			lazy[left(p)] %= 9;
		}
		lazy[p] = 0;
	}
	
	void update(int p, int l, int r, int a, int b, int k) {
		push(p, l, r);
		if (a > r || b < l) return;
		else if (l >= a && r <= b) {
			lazy[p] = k; push(p, l, r);
		} else {
			update(left(p), l, (l+r)/2, a, b, k);
			update(right(p), (l+r)/2+1, r, a, b, k);
			st[p] = st[left(p)] + st[right(p)];
		}
	}
	
	freq query(int p, int l, int r, int a, int b) {
		push(p, l, r);
		if (a > r || b < l) return freq();
		if (l >= a && r <= b) return st[p];
		
		freq p1 = query(left(p), l, (l+r)/2, a, b);
		freq p2 = query(right(p), (l+r)/2+1, r, a, b);
		return p1 + p2;
	}
	
	public:
	SegmentTree(int *ini, int* fim) {
		size = (int)(fim - ini);
		memset(st, 0, sizeof(st));
		memset(lazy, 0, sizeof(lazy));
		build(1, 0, size-1, ini);
	}
	
	freq query(int a, int b) {
		return query(1, 0, size-1, a, b);
	}
	void update(int a, int b, int k) {
		update(1, 0, size-1, a, b, k);
	}
};

int piano[MAXN];

int main() {
	int n, q, a, b;
	scanf("%d %d", &n, &q);
	for (int i = 0; i < n; i++) piano[i] = 1;
	SegmentTree mst(piano, piano + n);
	for (int i = 0; i < q; i++) {
		scanf("%d %d", &a, &b);
		int v = mst.query(a, b).max();
		mst.update(a, b, v);
	}
	for (int i = 0; i < n; i++) {
		printf("%d\n", mst.query(i, i).max());
	}
}


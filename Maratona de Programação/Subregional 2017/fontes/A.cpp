#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;
#define MAXN 100005

int st[4*MAXN][9], lazy[4*MAXN];

class SegmentTree {
	private:
	int size, helper[9];
	#define parent(p) (p >> 1)
	#define left(p) (p << 1)
	#define right(p) ((p << 1) + 1)
	
	void build (int p, int l, int r, int *A) {
		if (l == r) {
			st[p][A[l]] = 1;
		} else {
			build(left(p), l, (l+r)/2, A);
			build(right(p), (l+r)/2+1, r, A);
			for (int i = 0; i < 9; i++) {
				st[p][i] = st[left(p)][i] + st[right(p)][i];
			}
		}	
	}
	void push(int p, int l, int r) {
		for (int i = 0; i < 9; i++) {
			helper[i] = st[p][(i-lazy[p]+9000000)%9];
		}
		for (int i = 0; i < 9; i++) {
			st[p][i] = helper[i];
		}
		if (l != r) {
		//	printf("%d %d %d %d %d %d\n", right(p), lazy[right(p)], left(p), lazy[left(p)], p, lazy[p]);
			lazy[right(p)] += lazy[p];
			lazy[left(p)] += lazy[p];
		//	printf("%d %d %d %d\n", right(p), lazy[right(p)], left(p), lazy[left(p)]);
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
			for (int i = 0; i < 9; i++) {
				st[p][i] = st[left(p)][i] + st[right(p)][i];
			}
		}
	}
	
	vector<int> query(int p, int l, int r, int a, int b) {
		push(p, l, r);
		if (a > r || b < l) {
			vector<int> val;
			for (int i = 0; i < 9; i++) val.push_back(0);
			return val;
		}
		if (l >= a && r <= b) {
			vector<int> val;
			for (int i = 0; i < 9; i++) val.push_back(st[p][i]);
			return val;
		}
		
		vector<int> v1 = query(left(p), l, (l+r)/2, a, b);
		vector<int> v2 = query(right(p), (l+r)/2+1, r, a, b);
		for (int i = 0; i < 9; i++) {
			v1[i] += v2[i];
		}
		return v1;
	}
	
	public:
	SegmentTree(int *ini, int* fim) {
		size = (int)(fim - ini);
		memset(st, 0, sizeof(st));
		memset(lazy, 0, sizeof(lazy));
		build(1, 0, size-1, ini);
	}
	
	int query(int a, int b) {
		vector<int> v1 = query(1, 0, size-1, a, b);
		int maximum = 0;
		for (int i = 0; i < 9; i++) {
			if (v1[i] >= v1[maximum]) maximum = i;
		}
		//printf("\n");
		return maximum;
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
		int v = mst.query(a, b);
		mst.update(a, b, v);

	}
	for (int i = 0; i < n; i++) {
		printf("%d\n", mst.query(i, i));
	}
}

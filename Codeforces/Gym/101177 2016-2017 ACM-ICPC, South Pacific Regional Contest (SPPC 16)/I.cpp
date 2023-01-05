#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
int ini[MAXN], fim[MAXN], arr[3*MAXN];
map<int, int> vals;

const int neutral = 0;
int comp(int a, int b) {
	return max(a,b);
}

class SegmentTree {
private:
	vector<int> st, pos;
	int size;
#define parent(p) (p >> 1)
#define left(p) (p << 1)
#define right(p) ((p << 1) + 1)
	void build(int p, int l, int r, int* A) {
		if (l == r) {
			st[p] = A[l];
			pos[l] = p;
		}
		else {
			build(left(p), l, (l + r) / 2, A);
			build(right(p), (l + r) / 2 + 1, r, A);
			st[p] = comp(st[left(p)], st[right(p)]);
		}
	}
	int find(int p, int l, int r, int a, int b) {
		if (a > r || b < l) return neutral;
		if (l >= a && r <= b) return st[p];
		int p1 = find(left(p), l, (l + r) / 2, a, b);
		int p2 = find(right(p), (l + r) / 2 + 1, r, a, b);
		return comp(p1, p2);
	}
public:
	SegmentTree(int* begin, int* end) {
		size = (int)(end - begin);
		st.assign(4 * size, neutral);
		pos.assign(size + 9, 0);
		build(1, 0, size - 1, begin);
	}
	int query(int a, int b) { return find(1, 0, size - 1, a, b); }
	void update(int n, int num) {
		st[pos[n]] = num;
		n = parent(pos[n]);
		while (n>0) {
			st[n] = comp(st[left(n)], st[right(n)]);
			n = parent(n);
		}
	}
};

int main() {
	int n, k;
	while(scanf("%d", &n) != EOF) {
		vals.clear();
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &ini[i], &fim[i]);
			vals[ini[i]] = 0;
			vals[fim[i]] = 0;
		}
		
		k = 0;
		for (map<int,int>::iterator it = vals.begin(); it != vals.end(); it++) {
			it->second = k++;
			arr[k] = 0;
		}
		
		SegmentTree st(arr, arr + k);
		
		int resp = 0, v;
		for (int i = n-1; i >= 0; i--) {
			v = fim[i] - ini[i] + 1;
			v += st.query(vals[fim[i]]+1, k+1);
			
			st.update(vals[ini[i]], v);
			resp = max(resp, v);
		}
		printf("%d\n", resp);
	}
}
#include <bits/stdc++.h>
using namespace std;
#define MAXN 300009
#define INF 1000000009
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define sz(x) ((int)x.size())
typedef long long ll;

const int neutral = INF;
int comp(int a, int b) { return min(a, b); }

class SegmentTree {
	private:
	vector<int> st, lazy;
	int size;
#define left(p) (p << 1)
#define right(p) ((p << 1) + 1)
	void build(int p, int l, int r, int* A) {
		if (l == r) { st[p] = A[l]; return; }
		int m = (l+r)/2;
		build(left(p), l, m, A);
		build(right(p), m+1, r, A);
		st[p] = comp(st[left(p)], st[right(p)]);
	}
	void push(int p, int l, int r) {
		st[p] += lazy[p];
		if (l != r) {
			lazy[right(p)] += lazy[p];
			lazy[left(p)] += lazy[p];
		}
		lazy[p] = 0;
	}
	void update(int p, int l, int r, int a, int b, int k) {
		push(p, l, r);
		if (a > r || b < l) return;
		if (l >= a && r <= b) {
			lazy[p] = k; push(p, l, r); return;
		}
		update(left(p), l, (l+r)/2, a, b, k);
		update(right(p), (l+r)/2 + 1, r, a, b, k);
		st[p] = comp(st[left(p)], st[right(p)]);
	}
	int query(int p, int l, int r, int a, int b) {
		push(p, l, r);
		if (a > r || b < l) return neutral;
		if (l >= a && r <= b) return st[p];
		int m = (l+r)/2;
		int p1 = query(left(p), l, m, a, b);
		int p2 = query(right(p), m+1, r, a, b);
		return comp(p1, p2);
	}
public:
	SegmentTree(int *ini, int* en) {
		size = (int)(en - ini);
		st.assign(4*size, neutral);
		lazy.assign(4*size, 0);
		build(1, 0, size-1, ini);
	}
	int query(int a, int b) {
		return query(1, 0, size-1, a, b);
	}
	void update(int a, int b, int k) {
		update(1, 0, size-1, a, b, k);
	}
};

char str[MAXN];
int sum[MAXN];
set<int> open, closing;

void change(int p) {
	if (str[p] == '(') {
		open.erase(p);
		closing.insert(p);
		str[p] = ')';
	} else {
		closing.erase(p);
		open.insert(p);
		str[p] = '(';
	}
}
int main() {
	int N, Q;
	scanf("%d %d %s", &N, &Q, str);
	FOR(i, N) {
		sum[i+1] = sum[i];
		if (str[i] == '(') {
			sum[i+1]++;
			open.insert(i);
		} else { 
			sum[i+1]--;
			closing.insert(i);
		}
	}
	SegmentTree st(sum, sum + N + 1);
	while (Q--) {
		int p;
		scanf("%d", &p); p--;
		if (str[p] == '(') {
			change(p);
			int l = *closing.begin();
			change(l);
			printf("%d\n", l + 1);

			st.update(l+1, p, 2);
		} else {
			if (st.query(p, p) < 2) {
				printf("%d\n", p+1); continue;
			}
			int lo = 0, hi = p;
			while (lo < hi) {
				int mid = (lo + hi)/2;
				if (st.query(mid, p) >= 2) hi = mid;
				else lo = mid+1;
			}
			
			change(p);
			change(hi-1);
			printf("%d\n", hi);

			st.update(hi, p, -2);
		}
	}
}
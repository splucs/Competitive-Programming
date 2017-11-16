#include <bits/stdc++.h>
using namespace std;
#define MAXN 300009

struct iii {
	int am, xid, mid;
	iii(int _am, int _xid, int _mid) {
		am = _am; xid = _xid; mid = _mid;
	}
};

typedef pair<int, int> iii;
iii comp(iii a, iii b) {
	iii c;
	c.am = min(a.am, b.am);
	c.second = a.xid^b.xid;
	return c;
}

const iii neutral = iii(0,0); //comp(x, neutral) = x

class SegmentTree {
private:
	vector<iii> st, lazy;
	int size;
#define parent(p) (p >> 1)
#define left(p) (p << 1)
#define right(p) ((p << 1) + 1)
	void build(int p, int l, int r) {
		if (l == r) {
			st[p] = neutral;
		}
		else {
			build(left(p), l, (l + r) / 2);
			build(right(p), (l + r) / 2 + 1, r);
			st[p] = comp(st[left(p)], st[right(p)]);
		}
	}
	void push(int p, int l, int r) {
		st[p].first += lazy[p].first;
		st[p].second ^= lazy[p].second;
		if (l != r) {
			lazy[right(p)] = comp(lazy[right(p)], lazy[p]);
			lazy[left(p)] = comp(lazy[left(p)], lazy[p]);
		}
		lazy[p] = neutral;
	}
	void update(int p, int l, int r, int a, int b, ii k) {
		push(p, l, r);
		if (a > r || b < l) return;
		else if (l >= a && r <= b) {
			lazy[p] = k; push(p, l, r);
		}
		else {
			update(left(p), l, (l + r) / 2, a, b, k);
			update(right(p), (l + r) / 2 + 1, r, a, b, k);
			st[p] = comp(st[left(p)], st[right(p)]);
		}
	}
	ii query(int p, int l, int r, int a, int b) {
		push(p, l, r);
		if (a > r || b < l) return neutral;
		if (l >= a && r <= b) return st[p];
		ii p1 = query(left(p), l, (l + r) / 2, a, b);
		ii p2 = query(right(p), (l + r) / 2 + 1, r, a, b);
		return comp(p1, p2);
	}
public:
	SegmentTree(int _size) {
		size = _size;
		st.assign(4 * size, neutral);
		lazy.assign(4 * size, neutral);
		build(1, 0, size - 1);
	}
	ii query(int a, int b) { return query(1, 0, size - 1, a, b); }
	void update(int a, int b, ii k) { update(1, 0, size - 1, a, b, k); }
};

map<int, int> x2id;
int N, arr[MAXN], l[MAXN], r[MAXN], id[MAXN], ans[MAXN];
ii val[MAXN];

SegmentTree st(MAXN);

bool scomp(int i, int j) {
	return val[i] < val[j];
}

int main() {
	scanf("%d", &N);
	for(int i=0; i<N; i++) {
		scanf("%d", &arr[i]);
		x2id[arr[i]] = 0;
		id[i] = i;
	}
	for(int i=0; i<N; i++) {
		scanf("%d %d", &l[i], &r[i]);
		x2id[l[i]] = 0;
		x2id[r[i]] = 0;
	}
	int cnt = 0;
	for(map<int, int>::iterator it = x2id.begin(); it != x2id.end(); it++) {
		it->second = cnt++;
	}

	for(int i=0; i<N; i++) {
		arr[i] = x2id[arr[i]];
	}
	for(int i=0; i<N; i++) {
		l[i] = x2id[l[i]];
		r[i] = x2id[r[i]];
		st.update(l[i], r[i], ii(1, i));
	}
	for (int i = 0; i < N; i++) {
		val[i] = st.query(arr[i], arr[i]);
	}

	sort(id, id+N, scomp);

	bool possible = true;
	bool one = true;

	for(int it=0; it<N && possible && one; it++) {
		int i = id[it];
		ii am = st.query(arr[i], arr[i]);
		if (am.first > 1) one = false;
		else if (am.first == 0) possible = false;
		else {
			ans[i] = am.second;
			st.update(l[ans[i]], r[ans[i]], ii(-1, ans[i]));
		}
	}

	if (!possible) printf("Let's search for another office.\n");
	else if (!one) printf("Ask Shiftman for help.\n");
	else {
		printf("Perfect!\n");
		for(int i=0; i<N; i++) printf("%d ", ans[i]+1);
		printf("\n");
	}
	return 0;

}
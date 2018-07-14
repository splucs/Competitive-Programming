#include <set>
#include <vector>
#include <algorithm>
using namespace std;
#define MOD 998244353
#define MAXN 200009
typedef pair<int, int> ii;

/*
 * Lazy propagation segment tree
 */

class SegmentTree {
private:
	vector<int> st;
	vector<ii> lazy;
	int size;
#define parent(p) (p >> 1)
#define left(p) (p << 1)
#define right(p) ((p << 1) + 1)
	ii aggregate(ii a, ii b) {
		return ii((a.first*1ll*b.first)%MOD, (a.second*1ll*b.first + b.second)%MOD);
	} 
	void push(int p, int l, int r) {
		st[p] = (lazy[p].first*1ll*st[p] + (r - l + 1ll)*lazy[p].second)%MOD;
		if (l != r) {
			lazy[right(p)] = aggregate(lazy[right(p)], lazy[p]);
			lazy[left(p)] = aggregate(lazy[left(p)], lazy[p]);
		}
		lazy[p] = ii(1, 0);
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
			st[p] = (st[left(p)] + st[right(p)]) % MOD;
		}
	}
	int query(int p, int l, int r, int a, int b) {
		push(p, l, r);
		if (a > r || b < l) return 0;
		if (l >= a && r <= b) return st[p];
		int p1 = query(left(p), l, (l + r) / 2, a, b);
		int p2 = query(right(p), (l + r) / 2 + 1, r, a, b);
		return (p1 + p2) % MOD;
	}
public:
	SegmentTree(int _size) {
		size = _size;
		st.assign(4 * size, 0);
		lazy.assign(4 * size, ii(1, 0));
	}
	int query(int a, int b) { return query(1, 0, size - 1, a, b); }
	void update(int a, int b, ii k) { update(1, 0, size - 1, a, b, k); }
};

SegmentTree st(MAXN);

/*
 * Interval Tree
 */

struct node {
	int l, r, x;
	node(int _l, int _r, int _x = 0) : l(_l), r(_r), x(_x) { }
	void update(int dx) { x = min(x+dx, 2); }
};

bool operator < (node a, node b) {
	if (a.l != b.l) return a.l < b.l;
	return a.r < b.r;
}

class IntervalTree {
	set<node> tree;
	void split(int i) {
		set<node>::iterator it = --tree.upper_bound(node(i, 0));
		node t = *it;
		if (t.l == i) return;
		tree.erase(it);
		tree.insert(node(t.l, i-1, t.x));
		tree.insert(node(i, t.r, t.x));
	}
public:
	IntervalTree() { tree.insert(node(0, MAXN, 0)); }
	vector<node> get(int l, int r, bool update, int dx) {
		split(l); split(r+1);
		set<node>::iterator it = tree.lower_bound(node(l, 0));
		vector<node> q;
		while(it != tree.end() && it->l <= r) {
			node t = *it;
			it = tree.erase(it);
			if (update) t.update(dx);
			if (q.empty() || q.back().x != t.x) q.push_back(t);
			else q.back().r = t.r;
		}
		for(int i = 0; i < int(q.size()); i++) {
			tree.insert(q[i]);
		}
		return q;
	}
};

/*
 * Codeforces 981G
 */

#include <cstdio>

IntervalTree it[MAXN];

int main() {
	int n, q;
	scanf("%d %d", &n, &q);
	while(q --> 0) {
		int t, l, r, x;
		scanf("%d", &t);
		if (t == 1) {
			scanf("%d %d %d", &l, &r, &x);
			vector<node> q = it[x].get(l, r, true, 1);
			for(int i = 0; i < int(q.size()); i++) {
				if (q[i].x == 1) st.update(q[i].l, q[i].r, ii(1, 1));
				else st.update(q[i].l, q[i].r, ii(2, 0));
			}
		}
		else {
			scanf("%d %d", &l, &r);
			printf("%d\n", st.query(l, r));
		}
	}
	return 0;
}


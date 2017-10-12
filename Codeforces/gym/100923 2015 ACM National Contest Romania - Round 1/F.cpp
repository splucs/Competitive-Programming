#include <bits/stdc++.h>
using namespace std;
#define INF (1<<30)
#define MAXN 300009

class SegmentTree {
private:
	vector< vector<int> > st;
#define parent(p) (p >> 1)
#define left(p) (p << 1)
#define right(p) ((p << 1) + 1)
	void add(int p, int l, int r, int a, int b, int k) {
		if (a > r || b < l) return;
		else if (l >= a && r <= b) {
			if(!st[p].empty() && k > st[p].back()) k = st[p].back();
			st[p].push_back(k);
		}
		else {
			add(left(p), l, (l + r) / 2, a, b, k);
			add(right(p), (l + r) / 2 + 1, r, a, b, k);
		}
	}
	void remove(int p, int l, int r, int a, int b) {
		if (a > r || b < l) return;
		else if (l >= a && r <= b) {
			st[p].pop_back();
		}
		else {
			remove(left(p), l, (l + r) / 2, a, b);
			remove(right(p), (l + r) / 2 + 1, r, a, b);
		}
	}
	int query(int p, int l, int r, int i) {
		if (i > r || i < l) return INF;
		if (l == r) return st[p].empty() ? INF : st[p].back();
		int p1 = query(left(p), l, (l + r) / 2, i);
		int p2 = query(right(p), (l + r) / 2 + 1, r, i);
		int p3 = st[p].empty() ? INF : st[p].back();
		return min(p1, min(p2, p3));
	}
public:
	SegmentTree() {
		st.resize(4 * MAXN);
	}
	int query(int i) { return query(1, 0, MAXN - 1, i); }
	void add(int a, int b, int k) { add(1, 0, MAXN - 1, a, b, k); }
	void remove(int a, int b) { remove(1, 0, MAXN - 1, a, b); }
};

SegmentTree st;
typedef pair<int, int> ii;
stack<ii> s;

int main() {
	freopen("invazia.in", "r", stdin);
	freopen("invazia.out", "w", stdout);
	
	int N, M, x, y, z;
	char op;
	scanf("%d %d", &N, &M);
	while (M --> 0) {
		scanf(" %c", &op);
		if (op == 'I') {
			scanf("%d %d %d", &x, &y, &z);
			st.add(x, y, z);
			s.push(ii(x, y));
		}
		else if (op == 'E') {
			st.remove(s.top().first, s.top().second);
			s.pop();
		}
		else if (op == 'R') {
			scanf("%d", &x);
			z = st.query(x);
			if (z < INF) printf("%d\n", z);
			else printf("GUITZZZ!\n");
		}
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}
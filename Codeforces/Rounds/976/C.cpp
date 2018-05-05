#include <bits/stdc++.h>
using namespace std;
#define MAXN 300009
#define MAXM ((1e+18) + 100)
#define MOD 1000000007
#define INF 1000000009
#define EPS 1e-9
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;

const ii neutral = ii(-1, -1); //comp(x, neutral) = x

class SegmentTree {
private:
	vector<ii> st;
	int size;
#define parent(p) (p >> 1)
#define left(p) (p << 1)
#define right(p) ((p << 1) + 1)
	void update(int p, int l, int r, int a, int b, ii k) {
		if (a > r || b < l) return;
		else if (l >= a && r <= b) {
			st[p] = max(k, st[p]);
		}
		else {
			update(left(p), l, (l + r) / 2, a, b, k);
			update(right(p), (l + r) / 2 + 1, r, a, b, k);
		}
	}
	ii query(int p, int l, int r, int i) {
		if (i > r || i < l) return neutral;
		ii ans = st[p];
		if (l == r) return ans;
		ans = max(ans, query(left(p), l, (l + r) / 2, i));
		ans = max(ans, query(right(p), (l + r) / 2 + 1, r, i));
		return ans;
	}
public:
	SegmentTree(int _sz) {
		size = _sz;
		st.assign(4 * size, neutral);
	}
	ii query(int i) { return query(1, 0, size - 1, i); }
	void update(int a, int b, int k, int id) { update(1, 0, size - 1, a, b, ii(k, id)); }
};

int N, id[MAXN], l[MAXN], r[MAXN];

bool comp(int i, int j) {
	return r[i] - l[i] > r[j] - l[j];
}

int main() {
	scanf("%d", &N);
	map<int, int> reduce;
	FOR1(i, N) {
		id[i] = i;
		scanf("%d %d", &l[i], &r[i]);
		reduce[l[i]] = 0;
		reduce[r[i]] = 0;
	}
	int cnt = 0;
	for(auto & pp : reduce) {
		pp.second = cnt++;
	}
	FOR1(i, N) {
		l[i] = reduce[l[i]];
		r[i] = reduce[r[i]];
	}

	sort(id+1, id+1+N, comp);
	SegmentTree st(cnt);
	int ansi = -1, ansj = -1;
	FOR1(it, N) {
		int i = id[it];
		int j = st.query(l[i]).second;
		if (j >= 0 && r[j] >= r[i]) {
			ansi = i;
			ansj = j;
		}
		st.update(l[i], r[i], r[i], i);
	}
	printf("%d %d", ansi, ansj);
	return 0;
}
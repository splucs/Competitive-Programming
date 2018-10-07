#include <vector>
using namespace std;
#define MAXN 200009
#define MAXS 5000009

/*
 * Split-merge Segment Tree
 */

const int neutral = 0;
#define comp(a, b) ((a)+(b))

class SegmentTree {
	int cnt, n, root[MAXN], nroot;
	int sz[MAXS], ls[MAXS], rs[MAXS];

	int newnode(int _s) {
		ls[cnt] = rs[cnt] = -1;
		sz[cnt++] = _s;
		return cnt-1;
	}
	int build(int l, int r, int i) {
		int t = newnode(1);
		if (l == r) return t;
		int m = (l + r) / 2;
		if (i <= m) ls[t] = build(l, m, i);
		else rs[t] = build(m + 1, r, i);
		return t;
	}
	int split(int t1, int k) {
		if (t1 == -1 || sz[t1] <= k) return -1;
		int t2 = newnode(sz[t1] - k);
		sz[t1] = k;
		int sl = ls[t1] == -1 ? 0 : sz[ls[t1]];
		if (k > sl) rs[t2] = split(rs[t1], k - sl);
		else swap(rs[t1], rs[t2]);
		if (k < sl) ls[t2] = split(ls[t1], k);
		return t2;
	}
	int merge(int t1, int t2) {
		if(t1 == -1 || t2 == -1) return t1+t2+1;
		ls[t1] = merge(ls[t1], ls[t2]);
		rs[t1] = merge(rs[t1], rs[t2]);
		sz[t1] = comp(sz[t1], sz[t2]);
		return t1;
	}
	int query(int t, int l, int r, int a, int b) {
		if (t == -1 || l > b || r < a) return neutral;
		if (l >= a && r <= b) return sz[t];
		int m = (l + r) / 2;
		int p1 = query(ls[t], l, m, a, b);
		int p2 = query(rs[t], m+1, r, a, b);
		return comp(p1, p2);
	}
	int at(int t, int l, int r, int i) {
		if (l == r) return l;
		int sl = ls[t] == -1 ? 0 : sz[ls[t]];
		int m = (l + r) / 2;
		if (i < sl) return at(ls[t], l, m, i);
		else return at(rs[t], m+1, r, i - sl);
	}
	void to_vector(int t, int l, int r, vector<int> & v) {
		if (t == -1) return;
		int m = (l + r) / 2;
		to_vector(ls[t], l, m, v);
		to_vector(rs[t], m+1, r, v);
		for(int i = 0; i < sz[t] && l == r; i++)
			v.push_back(l);
	}
public:
	SegmentTree() { }
	SegmentTree(int _n) : n(_n), cnt(0), nroot(0) { }
	int newSet(int i) {
		root[nroot++] = build(0, n, i);
		return nroot-1;
	}
	void unionSet(int r1, int r2) {
		root[r1] = merge(root[r1], root[r2]);
		root[r2] = -1;
	}
	int query(int r, int a, int b) { return query(root[r], 0, n, a, b); }
	int size(int r) { return root[r] == -1 ? 0 : sz[root[r]]; }
	int splitSet(int r, int k) {
		if (k >= size(r)) return -1;
		if (k <= 0) {
			root[nroot++] = root[r];
			root[r] = -1;
		}
		else root[nroot++] = split(root[r], k);
		return nroot-1;
	}
	int at(int r, int i) { return at(root[r], 0, n, i); }
	void to_vector(int r, vector<int> & v) { to_vector(root[r], 0, n, v); }
};

/*
 * TEST MATRIX
 */
/*
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <cstdio>
#define NTESTS 1000009
#define all(x) x.begin(), x.end()

vector<int> a[NTESTS];
int cnt;
SegmentTree st;

void print(int r) {
	printf("%d: {", r);
	bool ok = false;
	for (int v : a[r]) {
		if (ok) printf(", ");
		ok = true;
		printf("%d", v);
	}
	printf("} ");
	printf("\n");
}

void merge(int r1, int r2) {
	a[r1].insert(a[r1].end(), all(a[r2]));
	sort(all(a[r1]));
	a[r2].clear();
}

int query(int r, int i, int j) {
	int ans = 0;
	for(int v : a[r]) {
		if (v >= i && v <= j) ans++;
	}
	return ans;
}

int split(int r1, int k) {
	int sz = (r1 == -1 ? 0 : int(a[r1].size()));
	if (k >= sz) {
		return -1;
	}
	else if (k <= 0) {
		a[cnt].clear();
		a[r1].swap(a[cnt]);
		cnt++;
		return cnt-1;
	}
	else {
		a[cnt] = vector<int>(a[r1].begin()+k, a[r1].end());
		a[r1].resize(k);
		cnt++;
		return cnt-1;
	}
}

bool test(int ntests) {
	srand(time(NULL));
	vector<int> alive;
	st = SegmentTree(ntests);
	cnt = 0;
	for(int i = 0; i <= ntests; i++) {
		a[cnt].clear();
		a[cnt].push_back(i);
		st.newSet(i);
		alive.push_back(cnt);
		cnt++;
	}
	for(int test = 0; test < ntests; test++) {
		//printf("\ntest %d\n", test);
		int r1, r2, i1, i2;
		//merge
		do {
			i1 = rand()%alive.size();
			i2 = rand()%alive.size();
		} while(i1 == i2);
		r1 = alive[i1];
		r2 = alive[i2];
		merge(r1, r2);
		st.unionSet(r1, r2);
		swap(alive[i2], alive.back());
		alive.pop_back();
		//split
		i1 = rand()%alive.size();
		r1 = alive[i1];
		int k = rand()%(a[r1].size()+1);
		r2 = split(r1, k);
		int r2l = st.splitSet(r1, k);
		if (r2 != r2l) {
			printf("failed on test %d, split r2test=%d r2st=%d\n", test, r2, r2l);
			return false;
		}
		if (r2 != -1) alive.push_back(r2);
		//test element by element
		for(int j = 0; j <= ntests; j++) {
			int ans1 = query(r1, j, j);
			int ans2 = st.query(r1, j, j);
			if (ans1 != ans2) {
				printf("failed on test %d, element %d ans1=%d ans2=%d\n", test, j, ans1, ans2);
				return false;
			}
		}
		//test size
		if (a[r1].size() != st.size(r1)) {
			printf("failed on test %d, size1=%d size2=%d\n", test, a[r1].size(), st.size(r1));
			return false;
		}
		//test element by index
		for(int i = 0; i < (int)a[r1].size(); i++) {
			int ans1 = a[r1][i];
			int ans2 = st.at(r1, i);
			if (ans1 != ans2) {
				print(r1);
				printf("failed on test %d, pos %d ans1=%d ans2=%d\n", test, i, ans1, ans2);
				return false;
			}
		}
		//test random queries
		for(int j = 0; j <= ntests; j++) {
			int a = rand()%(ntests+1);
			int b = rand()%(ntests+1);
			int ans1 = query(r1, a, b);
			int ans2 = st.query(r1, a, b);
			if (ans1 != ans2) {
				printf("failed on test %d, segment [%d,%d] ans1=%d ans2=%d\n", test, a, b, ans1, ans2);
				return false;
			}
		}
	}
	printf("all tests passed\n");
	return true;
}

int main() {
	test(1000);
	return 0;
}*/

/*
 * Szkoput Tree Rotations
 */

#include <cstdio>
typedef long long ll;
typedef pair<ll, int> ii;
typedef vector<int> vi;

SegmentTree st;

int n;
void dfs(int & t, ll & ans) {
	int a;
	scanf("%d", &a);
	if (a == 0) {
		int t1, t2;
		dfs(t1, ans);
		dfs(t2, ans);
		ll sum1 = 0, sum2 = 0;
		vi arr;
		if (st.size(t1) > st.size(t2)) {
			t = t1;
			st.to_vector(t2, arr);
			for (int b : arr) {
				sum1 += st.query(t1, 0, b-1);
				sum2 += st.query(t1, b+1, n);
			}
			st.unionSet(t1, t2);
		}
		else {
			t = t2;
			st.to_vector(t1, arr);
			for (int b : arr) {
				sum1 += st.query(t2, 0, b-1);
				sum2 += st.query(t2, b+1, n);
			}
			st.unionSet(t2, t1);
		}
		ans += min(sum1, sum2);
	}
	else {
		t = st.newSet(a);
	}
}

int main() {
	scanf("%d", &n);
	st = SegmentTree(n);
	ll ans = 0;
	int t;
	dfs(t, ans);
	printf("%lld\n", ans);
	return 0;
}
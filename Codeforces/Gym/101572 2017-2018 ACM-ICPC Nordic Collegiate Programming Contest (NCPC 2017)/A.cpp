#include <bits/stdc++.h>
using namespace std;
#define INF 1e+18
#define MAXN 500009

typedef pair<double, int> ii;
const ii neutral = ii(INF, -1);

class SegmentTree {
private:
	vector<ii> st;
	vector<int> pos;
	int size;
#define parent(p) (p >> 1)
#define left(p) (p << 1)
#define right(p) ((p << 1) + 1)
	void build(int p, int l, int r) {
		if (l == r) {
			st[p] = neutral;
			pos[l] = p;
		}
		else {
			build(left(p), l, (l + r) / 2);
			build(right(p), (l + r) / 2 + 1, r);
			st[p] = min(st[left(p)], st[right(p)]);
		}
	}
	ii find(int p, int l, int r, int a, int b) {
		if (a > r || b < l) return neutral;
		if (l >= a && r <= b) return st[p];
		ii p1 = find(left(p), l, (l + r) / 2, a, b);
		ii p2 = find(right(p), (l + r) / 2 + 1, r, a, b);
		return min(p1, p2);
	}
public:
	SegmentTree() {
		size = MAXN;
		st.assign(4 * size, neutral);
		pos.assign(size + 9, 0);
		build(1, 0, size - 1);
	}
	ii query(int a, int b) {
		if (a > b) return neutral;
		return find(1, 0, size - 1, a, b);
	}
	void update(int n, ii v) {
		st[pos[n]] = v;
		n = parent(pos[n]);
		while (n>0) {
			st[n] = min(st[left(n)], st[right(n)]);
			n = parent(n);
		}
	}
};

SegmentTree sta, stb;
int N;
double t, r, a, b, l, x[MAXN];
ii dp[MAXN];

void update(int j) {
	sta.update(j, ii(dp[j].first + x[j]/a, j));
	stb.update(j, ii(dp[j].first + x[j]/b, j));
}

int bs(int i, int lim) {
	int lo = i;
	int hi = N+1;
	while(hi > lo + 1) {
		int mid = (hi+lo)/2;
		if (x[mid] - x[i] < lim) lo = mid;
		else hi = mid;
	}
	return lo;
}

int getL1(int i) { return bs(i, t*a); }
int getL2(int i) { return bs(i, t*a + r*b); }

int main() {
	scanf("%lf %lf %lf %lf %lf %d", &l, &a, &b, &t, &r, &N);
	for(int i=0; i<N; i++) {
		scanf("%lf", &x[i]);
	}
	x[N] = l;
	dp[N] = ii(0, -1);
	update(N);
	ii cur;
	
	for(int i=N-1; i>=0; i--) {
		int l1 = getL1(i);
		int l2 = getL2(i);
		dp[i] = neutral;
		
		cur = sta.query(i+1, l1);
		cur.first += -x[i]/a;
		dp[i] = min(dp[i], cur);
		
		cur = stb.query(l1+1, l2);
		cur.first += t - x[i]/b - t*a/b;
		dp[i] = min(dp[i], cur);
		
		cur = sta.query(l2+1, N);
		cur.first += r - x[i]/a - r*b/a;
		dp[i] = min(dp[i], cur);
		
		update(i);
	}
	
	vector<int> ans;
	int i = 0;
	while(i != N) {
		ans.push_back(i);
		i = dp[i].second;
	}
	printf("%u\n", ans.size());
	for(int j=0; j<(int)ans.size(); j++) {
		printf("%d ", ans[j]);
	}
	printf("\n");
	
	return 0;	
}
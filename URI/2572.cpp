#include <bits/stdc++.h>
using namespace std;
#define INF (1<<30)
#define MAXN 200009
#define MOD 1000000007LL

typedef pair<int, int> ii;
const ii neutral = ii(-INF, -1);
ii comp(ii a, ii b) {
	return max(a, b);
}

class SegmentTree {
private:
	vector<ii> st;
	vector<int> pos;
	int size;
#define parent(p) (p >> 1)
#define left(p) (p << 1)
#define right(p) ((p << 1) + 1)
	void build(int p, int l, int r, ii* A) {
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
	ii find(int p, int l, int r, int a, int b) {
		if (a > r || b < l) return neutral;
		if (l >= a && r <= b) return st[p];
		ii p1 = find(left(p), l, (l + r) / 2, a, b);
		ii p2 = find(right(p), (l + r) / 2 + 1, r, a, b);
		return comp(p1, p2);
	}
public:
	SegmentTree() {}
	SegmentTree(ii* begin, ii* end) {
		size = (int)(end - begin);
		st.assign(4 * size, neutral);
		pos.assign(size + 9, 0);
		build(1, 0, size - 1, begin);
	}
	ii query(int a, int b) { return find(1, 0, size - 1, a, b); }
	void update(int n, ii num) {
		st[pos[n]] = num;
		n = parent(pos[n]);
		while (n>0) {
			st[n] = comp(st[left(n)], st[right(n)]);
			n = parent(n);
		}
	}
};

ii arr[MAXN];
SegmentTree st;

int main() {
	int N, K, Q;
	while(scanf("%d %d %d", &N, &K, &Q)!=EOF) {
		for(int i=0; i<N; i++) {
			scanf("%d", &arr[i].first);
			arr[i].second = i;
		}
		st = SegmentTree(arr, arr+N);
		int l, r;
		long long ans;
		vector<int> used;
		while(Q-->0) {
			scanf("%d %d", &l, &r);
			l--; r--;
			ans = 1;
			for(int j=0; j<K; j++) {
				ii mx = st.query(l, r);
				if (mx.first <= 0) break;
				ans = (ans*(long long)mx.first)%MOD;
				used.push_back(mx.second);
				st.update(mx.second, neutral);
			}
			if (used.empty()) ans = 0;
			printf("%lld\n", ans);
			while(!used.empty()) {
				st.update(used.back(), arr[used.back()]);
				used.pop_back();
			}
		}
	}
	return 0;
}
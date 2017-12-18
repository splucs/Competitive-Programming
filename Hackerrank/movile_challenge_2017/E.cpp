#include <bits/stdc++.h>
using namespace std;
#define MAXN 40000009

typedef long long ll;

const ll neutral = 0;
ll comp(ll a, ll b) {
	return max(a, b);
}

ll st[MAXN];

class SegmentTree {
private:
	int size;
#define parent(p) (p >> 1)
#define left(p) (p << 1)
#define right(p) ((p << 1) + 1)
	void update(int p, int l, int r, int a, int b, ll k) {
		if (a > r || b < l) return;
		else if (l >= a && r <= b) {
			st[p] += k;
		}
		else {
			update(left(p), l, (l + r) / 2, a, b, k);
			update(right(p), (l + r) / 2 + 1, r, a, b, k);
		}
	}
public:
	SegmentTree(int _size) { size = _size; }
	void update(int a, int b, ll k) { update(1, 0, size - 1, a, b, k); }
	void close() {
		for(int i = MAXN - 1; i > 0; i--) {
			if (right(i) < MAXN) st[i] += max(st[left(i)] ,st[right(i)]);
		}
	}
};

SegmentTree ds(1);

int main() {
	int N, Q, i, j;
	ll x;
	scanf("%d %d", &N, &Q);
	ds = SegmentTree(N);
	while(Q --> 0) {
		scanf("%d %d %lld", &i, &j, &x);
		i--; j--;
		ds.update(i, j, x);
	}
	ds.close();
	printf("%lld\n", st[1]);
	return 0;
}
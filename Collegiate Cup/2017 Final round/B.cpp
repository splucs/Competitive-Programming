#include <bits/stdc++.h>
using namespace std;
#define MAXN 300009

typedef long long ll;

const ll neutral = 0;
ll comp(ll a, ll b) {
	return max(a, b);
}

class SegmentTree {
private:
	vector<ll> st, pos;
	int size;
#define parent(p) (p >> 1)
#define left(p) (p << 1)
#define right(p) ((p << 1) + 1)
	void build(int p, int l, int r, ll* A) {
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
	ll find(int p, int l, int r, int a, int b) {
		if (a > r || b < l) return neutral;
		if (l >= a && r <= b) return st[p];
		ll p1 = find(left(p), l, (l + r) / 2, a, b);
		ll p2 = find(right(p), (l + r) / 2 + 1, r, a, b);
		return comp(p1, p2);
	}
public:
	SegmentTree() {}
	SegmentTree(ll* begin, ll* end) {
		size = (int)(end - begin);
		st.assign(4 * size, neutral);
		pos.assign(size + 9, 0);
		build(1, 0, size - 1, begin);
	}
	ll query(int a, int b) {
		a--;
		b--;
		if (a > b) return 0;
		return find(1, 0, size - 1, a, b);
	}
};

int N, Q, l[MAXN], r[MAXN];
ll c[MAXN], A[MAXN];

ll cost(int i, int j){
	ll val = A[i];
	int n = j-i+1;
	if (n > val) n = val;
	return n*val - ((n*1ll*(n-1))/2);
}

SegmentTree st;
	
int main() {
	int L, R;
	scanf("%d %d", &N, &Q);
	for(int i=1; i<=N; i++){
		scanf("%lld", &A[i]);
	}
	A[N+1] = -1;
	for(int i=1, j=1; j<=N+1; j++){
		if (A[j] == A[i]) continue;
		for(int k=i; k<j; k++){
			l[k] = i;
			r[k] = j-1;
			c[k] = cost(l[k], r[k]);
			//printf("cost[%d] = %d\n", k, c[k]);
		}
		i = j;
	}
	st = SegmentTree(c+1, c+1+N);
	while(Q--) {
		scanf("%d %d", &L, &R);
		ll ans = st.query(r[L]+1, l[R]-1);
		ans = max(ans, cost(L, min(r[L], R)));
		ans = max(ans, cost(max(l[R], L), R));
		printf("%lld\n", ans);
	}
	return 0;
}
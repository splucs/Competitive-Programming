#include <vector>
using namespace std;
#define INF (1<<30)

typedef long long ll;
const ll neutral = 0;
ll comp(ll a, ll b) {
	return a+b;
}

class SegmentTree {
	vector<ll> a;
	int n;
public:
	SegmentTree(int* st, int* en) {
		int sz = int(en-st);
		for (n = 1; n < sz; n <<= 1);
		a.assign(n << 1, neutral);
		for(int i=0; i<sz; i++) a[i+n] = st[i];
		for(int i=n+sz-1; i>1; i--)
			a[i>>1] = comp(a[i>>1], a[i]);
	}
	void update(int i, ll x) {
		a[i+n] = x; //substitui
		for (i += n, i >>= 1; i>1; i >>= 1)
			a[i] = comp(a[i<<1], a[1+(i<<1)]);
	}
	ll query(int l, int r) {
		ll ans = neutral;
		for (l += n, r += n+1; l < r; l >>= 1, r >>= 1) {
			if (l & 1) ans = comp(ans, a[l++]);
			if (r & 1) ans = comp(ans, a[--r]);
		}
		return ans;
	}
};

#include <cstdio>
#include <algorithm>
#define MAXN 100009
int arr[2*MAXN];

int main() {
	int N, Q;
	scanf("%d", &N);
	for(int i=MAXN; i<MAXN + N; i++) {
		scanf("%d", &arr[i]);
	}
	for(int i=0; i<MAXN; i++) {
		arr[i] = neutral;
	}
	SegmentTree st(arr, arr+N+MAXN);
	scanf("%d", &Q);
	int k = MAXN-1;
	while(Q --> 0) {
		int i, j, op, x;
		scanf("%d", &op);
		if (op == 1) {
			scanf("%d %d", &i, &j);
			i += k; j += k;
			printf("%lld\n", st.query(i, j));
		}
		if (op == 2) {
			scanf("%d", &x);
			st.update(k, x);
			k--;
		}
	}
	return 0;
}
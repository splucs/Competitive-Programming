#include <bits/stdc++.h>
using namespace std;
#define MAXN 300009
#define INF (1LL<<60)

#define FOR(i, n) for(int (i) = 0; (i)<(n); (i)++)
#define FOR1(i, n) for(int (i) = 1; (i)<=(n); (i)++)
	
typedef long long ll;
const ll neutral = INF;
ll comp(ll a, ll b) {
	return min(a, b);
}

class SegmentTree {
	vector<ll> a;
	int n;
public:
	SegmentTree(int sz) {
		for (n = 1; n < sz; n <<= 1);
		a.assign(n << 1, neutral);
	}
	void update(int i, ll x) {
		a[i+n] = x; //substitui
		for (i += n, i >>= 1; i; i >>= 1)
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

int t[MAXN], op[MAXN];
ll sum0[MAXN], sum1[MAXN];

int main() {
	int n, a, b, c, d, start, len;
	scanf("%d %d %d %d %d %d %d", &n, &a, &b, &c, &d, &start, &len);
	
	sum0[0] = sum1[0] = start;
	t[0] = 0;
	SegmentTree st0(n+1), st1(n+1);
	st0.update(0, start);
	st1.update(0, start);
	
	FOR1(i, n) {
		scanf("%d %d", &t[i], &op[i]);
		
		if (op[i] == 0) sum0[i] = sum0[i-1] - b;
		else sum0[i] = sum0[i-1] + a;
		st0.update(i, sum0[i]);
		
		if (op[i] == 0) sum1[i] = sum1[i-1] - d;
		else sum1[i] = sum1[i-1] + c;
		st1.update(i, sum1[i]);
	}
	
	ll ans = -1;
	
	FOR(i, n+1) {
		if (i>0 && st0.query(0, i-1) < 0) continue;
		int hi = n+1;
		int lo = i;
		while(hi > lo+1) {
			int mid = (hi+lo)/2;
			if (t[mid] < t[i]+len) lo = mid;
			else hi = mid;
		}
		if(st1.query(i, lo) - (i>0?sum1[i-1] - sum0[i-1] : 0) < 0) continue;
		
		if (i > 0) ans = t[i-1]+1;
		else ans = 0;
		break;
	}
	if (ans == -1 && st0.query(0, n) >= 0) ans = t[n]+1;
	
	printf("%I64d\n", ans);
	return 0;
}
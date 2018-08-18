#include <bits/stdc++.h>
using namespace std;

#define FOR(i, N) for (int i = 0; i < N; ++i)
#define MAXN 200009
#define pb push_back
typedef long long int ll;
typedef pair<int, int> ii;
const int INF = 1e9 + 1;

int N, Q, M;
int neutral[2] = {-INF, INF};

class SegmentTree{
	vector<int> a;
	int n, idx;
	
	int comp(int a, int b, int idx){
		if (idx) return min(a, b);
		return max(a, b);
	}
	
public:
	SegmentTree(int idx, int N){
		int sz = N;
		this->idx = idx;
		for (n = 1; n < sz; n <<= 1);
		a.assign(n << 1, neutral[idx]);
	}
	
	void update(int i, int x){
		a[i + n] = x;
		for (i += n, i >>= 1; i; i >>= 1){
			a[i] = comp(a[i << 1], a[1 + (i << 1)], idx);
		}
	}
	
	int query(int l, int r){
		int ans = neutral[idx];
		for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1){
			if (l & 1) ans = comp(ans, a[l++], idx);
			if (r & 1) ans = comp(ans, a[--r], idx);
		}
		return ans;
	}
};

int main() {
	scanf("%d%d", &N, &Q);
	int l, r;
	SegmentTree st1(0, N), st2(1, N);
	FOR(i, N){
		scanf("%d%d", &l, &r);
		st1.update(i, l);
		st2.update(i, r);
	}
	char op;
	int u, a ,b;
	
	FOR(i, Q){
		scanf(" %c", &op);
		if (op == '?'){
			scanf("%d%d", &a, &b); --a, --b;
			l = st1.query(a, b), r = st2.query(a, b);
			printf("%lld\n", max((ll)0, 1LL + r - l));
		} else{
			scanf("%d%d%d", &u, &l, &r);
			--u;
			st1.update(u, l);
			st2.update(u, r);
		}
	}
}
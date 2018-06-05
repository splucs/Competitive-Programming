#include <cstdio>
#include <vector>
#define INF 0x3f3f3f3f3f3f3f3f
#define MAXN 1009
using namespace std;

typedef long long ll;

/*
 * LiChao Segment Tree
 */

class LiChao {
	vector<ll> m, b;
	int n, sz; ll *x;
#define gx(i) (i < sz ? x[i] : x[sz-1])
	void update(int t, int l, int r, ll nm, ll nb) {
		ll xl = nm * gx(l) + nb, xr = nm * gx(r) + nb;
		ll yl = m[t] * gx(l) + b[t], yr = m[t] * gx(r) + b[t];
        if (yl >= xl && yr >= xr) return;
		if (yl <= xl && yr <= xr) {
			m[t] = nm, b[t] = nb; return;
		}
		int mid = (l + r) / 2;
		update(t<<1, l, mid, nm, nb);
		update(1+(t<<1), mid+1, r, nm, nb);
	}
public:
	LiChao(ll *st, ll *en) : x(st) {
		sz = int(en - st);
		for(n = 1; n < sz; n <<= 1);
		m.assign(2*n, 0); b.assign(2*n, -INF);
	}
	void insert_line(ll nm, ll nb) {
		update(1, 0, n-1, nm, nb);
	}
	ll query(int i) {
		ll ans = -INF;
		for(int t = i+n; t; t >>= 1)
			ans = max(ans, m[t] * x[i] + b[t]);
		return ans;
	}
};

/*
 * UVa 12524
 */

ll w[MAXN], x[MAXN], A[MAXN], B[MAXN], dp[MAXN][MAXN];

int main(){
	int N, K;
	while(scanf("%d %d", &N, &K)!=EOF) {
		for(int i=0; i<N; i++){
			scanf("%lld %lld", x+i, w+i);
			A[i] = w[i] + (i>0 ? A[i-1] : 0);
			B[i] = w[i]*x[i] + (i>0 ? B[i-1] : 0);
			dp[i][1] = x[i]*A[i] - B[i];
		}
		for(int k=2; k<=K; k++){
			dp[0][k] = 0;
            LiChao lc(x, x+N);
			for(int i=1; i<N; i++){
				lc.insert_line(A[i-1], -dp[i-1][k-1]-B[i-1]);
				dp[i][k] = x[i]*A[i] - B[i] - lc.query(i);
			}
		}
		printf("%lld\n", dp[N-1][K]);
	}
	return 0;
}
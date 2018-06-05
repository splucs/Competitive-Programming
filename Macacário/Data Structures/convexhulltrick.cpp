#include <cstdio>
#include <vector>
#define INF (1<<30)
#define MAXN 1009
using namespace std;

typedef long long int ll;

/*
 * Partially Dynamic Convex Hull Trick
 */

class CHTrick {
private:
	vector<ll> m, n;
	vector<double> p;
	bool maxCH; int i;
public:
	CHTrick(bool mxch) { maxCH = mxch; i = 0; }
	void clear() { m.clear(); n.clear(); p.clear(); }
	double inter(double nm, double nn, double lm, double ln) {
		return (ln - nn) / (nm - lm);
	}
	void push(ll nm, ll nn) {
		while (!p.empty()) {
			if (nm == m.back() && maxCH && nn <= n.back()) return;
			if (nm == m.back() && !maxCH && nn >= n.back()) return;
			double x = inter(nm, nn, m.back(), n.back());
			if (nm != m.back() && p.back() < x) break;
			m.pop_back(); n.pop_back(); p.pop_back();
		}
		p.push_back(p.empty() ? -INF : inter(nm, nn, m.back(), n.back()));
		m.push_back(nm); n.push_back(nn);
		if (i >= p.size()) i = p.size()-1;
	}
	ll query(ll x) {
		if (p.empty()) return (maxCH ? -1 : 1)*INF;
		ll r = p.size() - 1, l = 0, mid;
		if (x >= p[r]) return m[r] * x + n[r];
		while (r > l + 1) {
			mid = (r + l) / 2;
			if (x < p[mid]) r = mid;
			else l = mid;
		}
		return m[l] * x + n[l];
	}
	ll query_q(ll x) {
		while (p[i] > x) i--;
		while(i+1 < p.size() && p[i+1] <= x) i++;
		return m[i] * x + n[i];
	}
};

/*
 * URI 1282
 */

ll w[MAXN], x[MAXN], A[MAXN], B[MAXN], dp[MAXN][MAXN];

int main(){
	int N, K;
	CHTrick cht(false);
	while(scanf("%d %d", &N, &K)!=EOF) {
		for(int i=0; i<N; i++){
			scanf("%lld %lld", x+i, w+i);
			A[i] = w[i] + (i>0 ? A[i-1] : 0);
			B[i] = w[i]*x[i] + (i>0 ? B[i-1] : 0);
			dp[i][1] = x[i]*A[i] - B[i];
		}
		for(int k=2; k<=K; k++){
			dp[0][k] = 0;
			cht.clear();
			for(int i=1; i<N; i++){
				cht.push(-A[i-1], dp[i-1][k-1]+B[i-1]);
				//dp[i][k] = x[i]*A[i] - B[i] + cht.query(x[i]);
				dp[i][k] = x[i]*A[i] - B[i] + cht.query_q(x[i]);
			}
		}
		printf("%lld\n", dp[N-1][K]);
	}
	return 0;
}
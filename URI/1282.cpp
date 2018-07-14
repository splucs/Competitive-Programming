#include <cstdio>
#include <vector>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define MAXN 1009
using namespace std;

typedef long long ll;

class CHTrick {
private:
	vector<ll> m, n;
	vector<double> p;
	vector<int> ids;
	bool maxCH; int i;
public:
	CHTrick(bool mxch) { maxCH = mxch; i = 0; }
	void clear() { m.clear(); n.clear(); p.clear(); ids.clear(); }
	double inter(double nm, double nn, double lm, double ln) {
		return (ln - nn) / (nm - lm);
	}
	void push(ll nm, ll nn, int id) {
		while (!p.empty()) {
			if (nm == m.back() && maxCH && nn <= n.back()) return;
			if (nm == m.back() && !maxCH && nn >= n.back()) return;
			double x = inter(nm, nn, m.back(), n.back());
			if (nm != m.back() && p.back() < x) break;
			m.pop_back(); n.pop_back(); p.pop_back(); ids.pop_back();
		}
		p.push_back(p.empty() ? -INF : inter(nm, nn, m.back(), n.back()));
		m.push_back(nm); n.push_back(nn); ids.push_back(id);
		if (i >= p.size()) i = p.size()-1;
	}
	pair<ll, int> query_q(ll x) {
		while (p[i] > x) i--;
		while(i+1 < p.size() && p[i+1] <= x) i++;
		return make_pair(m[i] * x + n[i], ids[i]);
	}
};

/*
 * URI 1282
 */

ll w[MAXN], x[MAXN], A[MAXN], B[MAXN];
ll dp[MAXN];
int opt[MAXN], N, K;

CHTrick cht(false);

int computeDp(ll C) {
	cht.clear();
	dp[0] = 0;
	opt[0] = 0;
	for(int i = 1; i <= N; i++) {
		cht.push(-A[i-1], dp[i-1] + B[i-1], i-1);
		pair<ll, int> cur = cht.query_q(x[i]);
		dp[i] = C + x[i]*A[i] - B[i] + cur.first;
		opt[i] = 1 + opt[cur.second];
	}
	return opt[N];
}

ll computeC() {
	ll lo = 0;
	ll hi = INFLL;
	while(hi > lo + 1) {
		ll C = (hi + lo) / 2;
		int k = computeDp(C);
		if (k > K) lo = C;
		else hi = C;
	}
	return hi;
}

int main(){
	while (scanf("%d %d", &N, &K) != EOF){
		A[0] = B[0] = 0;
		for (int i=1; i<=N; i++) {
			scanf("%lld %lld", &x[i], &w[i]);
			A[i] = w[i] + A[i-1];
			B[i] = w[i]*x[i] + B[i-1];
		}
		ll C = computeC();
		int k = computeDp(C);
		printf("%lld\n", dp[N] - C*K);
	}
	return 0;
}
#include <bits/stdc++.h>
using namespace std;
#define MAXN 10009
#define INF (1LL<<60)

typedef long long ll;
int N, M;
ll t1, t2, m[MAXN], b[MAXN], e[MAXN];
typedef pair<ll, ll> ii;
vector<ii> prob;

int main() {
	scanf("%d %d %lld %lld", &N, &M, &t1, &t2);
	double ans = 1;
	for(int i=0; i<N; i++) {
		scanf("%lld", &m[i]);
	}
	for(int i=0; i<M; i++) {
		scanf("%lld %lld", &b[i], &e[i]);
		for(int j=0; j<N; j++) {
			prob.push_back(ii(b[i]-m[j], e[i]-m[j]));
		}
	}
	ll last = -INF;
	ll tot = t2-t1;
	ll cur = 0;
	sort(prob.begin(), prob.end());
	for(int i=0; i<(int)prob.size(); i++) {
		ll d1 = prob[i].first;
		ll d2 = prob[i].second;
		if (d1 >= last) {
			ll mint = max(last, t1);
			ll maxt = min(d1, t2);
			if (maxt >= mint) cur += maxt - mint;
		}
		last = max(last, d2);
	}
	ll mint = max(last, t1);
	ll maxt = min(INF, t2);
	if (maxt >= mint) cur += maxt - mint;
	printf("%.10f\n", cur*1.0/tot);
	return 0;
}
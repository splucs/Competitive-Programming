#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define fi first
#define se second
#define MAXN 29
typedef long long ll;

double p[4];
ll fat[MAXN];

int main() {
	fat[0] = 1;
	FOR1(i, MAXN-1) fat[i] = i*fat[i-1];
	int n;
	scanf("%d", &n);
	FOR(i, 4) scanf("%lf", &p[i]);
	map<double, ll> cnt;
	double pi = 1;
	FOR(i, n+1) {
		double pj = 1;
		FOR(j, n+1) {
			double pk = 1;
			FOR(k, n+1) {
				double pl = 1;
				FOR(l, n+1) {
					if (i+j+k+l == n) {
						cnt[pi*pj*pk*pl] += fat[n]/(fat[i]*fat[j]*fat[k]*fat[l]);
					}
					pl *= p[3];
				}
				pk *= p[2];
			}
			pj *= p[1];
		}
		pi *= p[0];
	}
	double ans = 0;
	while(cnt.size() > 1u || cnt.begin()->se > 1) {
		double prob = cnt.begin()->fi;
		ll am = cnt.begin()->se;
		cnt.erase(cnt.begin());
		if (am > 1) {
			ll nam = am/2;
			am %= 2;
			ans += nam*2*prob;
			cnt[2*prob] += nam;
		}
		if (am == 0) continue;
		if (cnt.empty()) break;
		double prob2 = cnt.begin()->fi;
		assert(prob2 > prob);
		cnt.begin()->se--;
		if (cnt.begin()->se == 0) cnt.erase(cnt.begin());
		cnt[prob + prob2]++;
		ans += prob + prob2;
	}
	printf("%.20f\n", ans);
	return 0;
}
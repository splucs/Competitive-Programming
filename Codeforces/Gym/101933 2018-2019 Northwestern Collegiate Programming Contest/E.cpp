#include <bits/stdc++.h>
using namespace std;
#define MAXN 1109
#define INF 0x3f3f3f3f
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define sz(x) int(x.size())
#define mset(x, y) memset(&x, y, sizeof x)
typedef long long ll;

int encode(int cnt[]) {
	int mask = 0;
	int k = 0;
	FOR1(i, 6) {
		FOR(j, cnt[i]) {
			mask |= (1<<k);
			k++;
		}
		k++;
	}
	return mask;
}

void decode(int mask, int cnt[]) {
	FOR(i, 7) cnt[i] = 0;
	int i = 1;
	while(mask > 0) {
		if (mask & 1) cnt[i]++;
		else i++;
		if (i > 6) return;
		mask >>= 1;
	}
}

double dp[MAXN][MAXN];
int d, tothp;

double DP(const int masku, const int maskv) {
	double &ans = dp[masku][maskv];
	if (ans >= -0.5) return ans;
	int nu = __builtin_popcount(masku);
	int nv = __builtin_popcount(maskv);
	if (nv == 0) return ans = 1.0;

	ans = 0.0;
	int cntu[7], cntv[7];
	decode(masku, cntu);
	decode(maskv, cntv);
	int curhp = 0;
	FOR1(i, 6) curhp += i*(cntu[i] + cntv[i]);
	if (d <= tothp-curhp) return ans = 0.0;
	
	int acum = -1, bit;
	FOR1(i, 6) {
		if (i == 1) {
			ans += cntu[i]*DP(masku>>1, maskv);
		}
		else if (cntu[i] != 0) {
			bit = (1<<acum)^(1<<(acum+1));
			ans += cntu[i]*DP(masku^bit, maskv);
		}
		acum += cntu[i]+1;
	}
	acum = -1;
	FOR1(i, 6) {
		if (i == 1) {
			ans += cntv[i]*DP(masku, maskv>>1);
		}
		else if (cntv[i] != 0) {
			bit = (1<<acum)^(1<<(acum+1));
			ans += cntv[i]*DP(masku, maskv^bit);
		}
		acum += cntv[i]+1;
	}
	ans /= (nu+nv);
	return ans;
}

int main() {
	//FOR(mask, (1<<10)) checkmask(mask);
	int n, m;
	while(scanf("%d %d %d", &n, &m, &d) != EOF) {
		FOR(i, MAXN) FOR(j, MAXN) dp[i][j] = -1;
		tothp = 0;

		int cntu[7], cntv[7];
		mset(cntu, 0);
		mset(cntv, 0);
		while(n --> 0) {
			int hp;
			scanf("%d", &hp);
			cntu[hp]++;
			tothp += hp;
		}
		while(m --> 0) {
			int hp;
			scanf("%d", &hp);
			cntv[hp]++;
			tothp += hp;
		}
		printf("%.20f\n", DP(encode(cntu), encode(cntv)));
	}
	return 0;
}
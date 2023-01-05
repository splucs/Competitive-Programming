#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define FOR(i, n) for(int i = 0; i < n; i++)

typedef long long ll;
ll w[MAXN], h[MAXN], c[MAXN];
ll mulw[MAXN], mulh[MAXN], divw[MAXN], divh[MAXN];

ll gcd(ll x, ll y) {
	if (y == 0) return x;
	return gcd(y, x%y);
}

ll lcm(ll x, ll y) {
	return x / gcd(x, y) * y;
}

int cntdiv(ll N) {
	int cnt = 0;
	for(ll i = 1; i*i <= N; i++) {
		if (N%i == 0) {
			cnt++;
			if (i*i != N) cnt++;
		}
	}
	return cnt;
}

int main() {
	int N;
	scanf("%d", &N);
	map<ll, int> idw, idh;
	int cntw = 0, cnth = 0;
	FOR(i, N) {
		scanf("%I64d %I64d %I64d", &w[i], &h[i], &c[i]);
		if (!idw.count(w[i])) {
			mulw[cntw] = 1;
			divw[cntw] = 0;
			idw[w[i]] = cntw++;
		}
		if (!idh.count(h[i])) {
			mulh[cnth] = 1;
			divh[cnth] = 0;
			idh[h[i]] = cnth++;
		}
	}
	bool ok = true;
	if (cntw*cnth != N) ok = false;
	if (ok) {
		vector<vector<bool> > app;
		app.resize(cntw);
		FOR(i, cntw) app[i].assign(cnth, false);
		FOR(i, N) {
			w[i] = idw[w[i]];
			h[i] = idh[h[i]];
			app[w[i]][h[i]] = true;
		}
		FOR(i, cntw) FOR(j, cnth) {
			if (!app[i][j]) ok = false;
		}
	}
	while(ok) {
		bool changed = false;

		FOR(i, N) {
			ll cur;
			cur = gcd(divw[w[i]], c[i] / (mulh[h[i]] == 0 ? 1 : mulh[h[i]]));
			if (divw[w[i]] != cur) {
				divw[w[i]] = cur;
				changed = true;
			}
			cur = gcd(divh[h[i]], c[i] / (mulw[w[i]] == 0 ? 1 : mulw[w[i]]));
			if (divh[h[i]] != cur) {
				divh[h[i]] = cur;
				changed = true;
			}
			cur = lcm(mulw[w[i]], c[i] / (divh[h[i]] == 0 ? 1 : divh[h[i]]));
			if (mulw[w[i]] != cur) {
				mulw[w[i]] = cur;
				changed = true;
			}
			cur = lcm(mulh[h[i]], c[i] / (divw[w[i]] == 0 ? 1 : divw[w[i]]));
			if (mulh[h[i]] != cur) {
				mulh[h[i]] = cur;
				changed = true;
			}
			if (divh[h[i]] < mulh[h[i]] || divh[h[i]] % mulh[h[i]] != 0) {
				ok = false;
				break;
			}
			if (divw[w[i]] < mulw[w[i]] || divw[w[i]] % mulw[w[i]] != 0) {
				ok = false;
				break;
			}
		}

		if (!changed) break;
	}
	
	int ans = ok ? cntdiv(divw[w[0]] / mulw[w[0]]) : 0;
	printf("%d\n", ans);
	return 0;
}
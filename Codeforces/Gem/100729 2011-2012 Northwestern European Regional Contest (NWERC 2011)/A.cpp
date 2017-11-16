#include <bits/stdc++.h>
using namespace std;
#define MAXN 1109
#define INF 1000000000000009LL

typedef long long ll;
ll M, pascal[MAXN][MAXN];

ll Comb(ll n, ll k) {
	if (k > n) return 0;
	if (n == k) return 1;
	ll prod = 1;
	for(ll d=1; d<=k; d++) {
		prod *= (n-k+d);
		prod /= d;
		if (prod > M) {
			//printf("Comb(%I64d,%I64d)=%I64d\n", n, k, prod);
			return M+1;
		}
	}
	//printf("Comb(%I64d,%I64d)=%I64d\n", n, k, prod);
	return prod;
}

ll get(int k) {
	if (k == 1) return M;
	
	ll hi = 1000000000LL;
	ll lo = 0;
	while(hi > lo + 1) {
		ll mid = (hi + lo) / 2;
		if (Comb(mid, k) <= M) lo = mid;
		else hi = mid;
	}
	//printf("k=%d -> lo = %I64d (%I64d)\n", k, lo, Comb(lo, k));
	if (Comb(lo, k) == M) return lo;
	else return -1;
}

typedef pair<ll, ll> ii;
map<ll, vector<ii> > mppas;

void build() {
	for(int n=0; n<MAXN; n++) {
		for(int k=0; k<MAXN; k++) {
			if (k > n) pascal[n][k] = 0;
			else if (n == k || k == 0) pascal[n][k] = 1;
			else {
				if (pascal[n-1][k] == -1 || pascal[n-1][k-1] == -1) pascal[n][k] = -1;
				else pascal[n][k] = pascal[n-1][k] + pascal[n-1][k-1];
				if (pascal[n][k] > INF) pascal[n][k] = -1;
				else if (k >= 5 && n-k >= 5) {
					mppas[pascal[n][k]].push_back(ii(n, k));
				}
			}
		}
	}
}

int main() {
	build();
	
	int T;
	scanf("%d", &T);
	while(T --> 0) {
		
		scanf("%I64d", &M);
		vector<ii> ans;
		for(ll k=1; k<5; k++) {
			ll n = get(k);
			if (n == -1) continue;
			ans.push_back(ii(n, k));
			if (n-k > 4) ans.push_back(ii(n, n-k));
		}
		if (mppas.count(M)) {
			ans.insert(ans.end(), mppas[M].begin(), mppas[M].end());
		}
		
		sort(ans.begin(), ans.end());
		
		printf("%u\n", ans.size());
		for(int i=0; i<(int)ans.size(); i++) {
			printf("(%I64d,%I64d) ", ans[i].first, ans[i].second);
		}
		printf("\n");
	}
	return 0;
}
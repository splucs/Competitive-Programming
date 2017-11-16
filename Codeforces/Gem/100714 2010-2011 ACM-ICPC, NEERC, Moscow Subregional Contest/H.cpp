#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, int> ii;

ll legendre(ll n, ll p){
	int ans = 0;
	ll prod = p;
	while(prod <= n){
		ans += n/prod;
		prod *= p;
	}
	return ans;
}

int main() {
	ll N, n;
	scanf("%I64d", &N);
	vector<ii> fac;
	n = N;
	for(ll i=2; i*i<=n; i++) {
		if (n%i == 0) {
			ii cur = ii(i, 0);
			while(n%i == 0) {
				cur.second++;
				n /= i;
			}
			fac.push_back(cur);
		}
	}
	if (n > 1) fac.push_back(ii(n, 1));
	bool possible = true;
	for(int i=0; i<(int)fac.size(); i++) {
		ll p = fac[i].first;
		if (legendre(N-1, p) < fac[i].second) possible = false;
	}
	if (possible) printf("YES\n");
	else printf("NO\n");
	return 0;
}
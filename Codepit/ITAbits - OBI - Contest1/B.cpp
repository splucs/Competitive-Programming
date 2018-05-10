#include <bits/stdc++.h>
using namespace std;
#define MAXN 10009
#define MAXM 309
#define MOD 1000000007
#define INF 1000000009
#define EPS 1e-9
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;
#define EPS 1e-9

map<ll, int> cnt;

int main() {
	int n;
	scanf("%d", &n);
	FOR(i, n) {
		ll x;
		scanf("%lld", &x);
		cnt[x]++;
	}
	ll ans;
	int anscnt = 0;
	for(auto pp : cnt) {
		if (pp.se >= anscnt) {
			anscnt = pp.se;
			ans = pp.fi;
		}
	}
	printf("%lld\n", ans);
	return 0;
}
#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define MAXM ((1e+18) + 100)
#define MOD 1000000007
#define INF 1000000009
#define EPS 1e-9
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;
#define EPS 1e-9

ll X, d;

int main() {
	scanf("%I64d %I64d", &X, &d);
	ll cur = 1;
	vector<ll> ans;
	while(X > 0) {
		int n = 1;
		while((1LL<<n) - 1 <= X) n++;
		n--;
		FOR(i, n) ans.pb(cur);
		X -= (1LL<<n) - 1;
		cur += d;
	}
	printf("%u\n", ans.size());
	for(ll a : ans) {
		printf("%I64d ", a);
	}
	printf("\n");
	return 0;
}
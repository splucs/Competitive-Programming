#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009
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

ll arr[14], aux[14];

int main() {
	FOR(i, 14) {
		scanf("%I64d", &arr[i]);
	}
	ll ans = 0;
	FOR(i, 14) {
		FOR(j, 14) aux[j] = arr[j];
		ll mc = aux[i] / 14;
		ll r = aux[i] % 14;
		aux[i] = 0;
		FOR(j, 14) aux[j] += mc;
		FOR1(j, r) aux[(i+j)%14]++;
		ll cur = 0;
		FOR(j, 14) {
			if (aux[j] % 2 == 0) cur += aux[j];
		}
		ans = max(ans, cur);
	}
	printf("%I64d\n", ans);
	return 0;
}
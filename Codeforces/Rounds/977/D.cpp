#include <bits/stdc++.h>
using namespace std;
#define MAXN 209
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

ll a[MAXN];

int cnt(ll n, ll f) {
	int ans = 0;
	while(n % f == 0) {
		ans++;
		n /= f;
	}
	return ans;
}

bool comp(ll n, ll m) {
	if (cnt(n, 3) > cnt(m, 3)) return true;
	if (cnt(n, 3) < cnt(m, 3)) return false;
	if (cnt(n, 2) > cnt(m, 2)) return false;
	if (cnt(n, 2) < cnt(m, 2)) return true;
	return false;
}

int main() {
	int n;
	scanf("%d", &n);
	FOR(i, n) scanf("%I64d", &a[i]);
	sort(a, a+n, comp);
	FOR(i, n) printf("%I64d " , a[i]);
	printf("\n");
	return 0;
}
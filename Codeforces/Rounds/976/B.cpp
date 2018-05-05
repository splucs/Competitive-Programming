#include <bits/stdc++.h>
using namespace std;
#define MAXN 300009
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

int main() {
	ll n, m, k;
	scanf("%I64d %I64d %I64d", &n, &m, &k);
	ll x = 1, y = 1;
	if (k <= n-1) {
		x += k;
		printf("%I64d %I64d\n", x, y);
		return 0;
	}
	else {
		k -= n;
		x += n-1;
		y++;
	}
	ll d = k / (m-1);
	x -= d;
	k -= d*(m-1);
	if (d % 2 == 0) {
		y = 2;
		y += k;
	}
	else {
		y = m;
		y -= k;
	}
	printf("%I64d %I64d\n", x, y);
	return 0;
}
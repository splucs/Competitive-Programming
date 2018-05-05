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

ll a[MAXN];
int n, q;

int main() {
	scanf("%d %d", &n, &q);
	a[0] = 0;
	FOR1(i, n) {
		scanf("%I64d", &a[i]);
		a[i] += a[i-1];
	}
	ll cur = 0;
	FOR1(i, q) {
		ll k;
		scanf("%I64d", &k);
		cur += k;
		if (cur >= a[n]) cur = 0;
		int lo = 0;
		int hi = n;
		while(hi > lo + 1) {
			int mid = (hi + lo) / 2;
			if (a[mid] <= cur) lo = mid;
			else hi = mid;
		}
		printf("%d\n", n - lo);
	}
	return 0;
}
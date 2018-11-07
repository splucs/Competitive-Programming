#include <bits/stdc++.h>
#define MAXN 200009
#define MAXM 100009
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define fi first
#define se second
#define sz(x) int(x.size())
#define all(x) x.begin(),x.end()
#define mset(x, y) memset(&x, y, sizeof x)
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;

int main() {
	int T;
	scanf("%d", &T);
	FOR1(caseNo, T) {
		ll n, ans = 0;
		scanf("%lld", &n);
		n /= 2;
		for(ll p = 1, s = 1; p <= n; p *= 2, s++) {
			ans += s*p*(n/p);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
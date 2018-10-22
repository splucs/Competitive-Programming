#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define INF 0x3f3f3f3f
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define sz(x) int(x.size())
#define mset(x, y) memset(&x, y, sizeof x)
typedef long long ll;

ll a, b, c, d;
ll z[MAXN];
char ans[MAXN];

int main() {
	while(scanf("%lld %lld %lld %lld", &a, &b, &c, &d) != EOF) {
		if (a == 0 && b == 0 && c == 0) { //0 zeros
			ll m = 1;
			while(m*(m-1)/2 < d) m++;
			if (m*(m-1)/2 == d) {
				FOR(i, m) ans[i] = '1';
				ans[m] = 0;
				printf("%s\n", ans);
				continue;
			}
		}
		if (d == 0 && b == 0 && c == 0) { //0 ones
			ll n = 1;
			while(n*(n-1)/2 < a) n++;
			if (n*(n-1)/2 == a) {
				FOR(i, n) ans[i] = '0';
				ans[n] = 0;
				printf("%s\n", ans);
				continue;
			}
		}
		bool ok = true;
		ll n = 1;
		while(n*(n-1)/2 < a) n++;
		if (n*(n-1)/2 > a) ok = false;
		ll m = 1;
		while(m*(m-1)/2 < d) m++;
		if (m*(m-1)/2 > d) ok = false;
		ll tot = n+m;
		c += n*(n+1)/2;
		b += m*(m+1)/2;
		if (b+c != tot*(tot+1)/2) ok = false;
		ll cur = 0;
		FOR1(i, n) {
			z[i] = i;
			cur += i;
		}
		z[n+1] = tot+1;
		REP1(i, n) {
			if (cur == c) break;
			ll dc = min(c - cur, z[i+1]-z[i]-1);
			z[i] += dc;
			cur += dc;
		}
		if (cur < c) ok = false;
		if (!ok) printf("impossible\n");
		else {
			if (tot == 0) tot++;
			FOR(i, tot) ans[i] = '1';
			ans[tot] = 0;
			FOR1(i, n) ans[z[i]-1] = '0';
			printf("%s\n", ans);
		}
	}
	return 0;
}
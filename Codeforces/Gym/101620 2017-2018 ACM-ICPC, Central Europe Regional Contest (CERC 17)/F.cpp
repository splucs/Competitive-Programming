#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define INF 0x3f3f3f3f
#define MAXN 10000009
#define MAXM 29
#define pb push_back
#define fi first
#define se second
typedef pair<int, int> ii;
typedef long long ll;

void allInv(ll inv[], int p) {
	inv[1] = 1;
	for(int i = 2; i < p; i++) {
		inv[i] = (p - (p/i)*inv[p%i]%p)%p;
	}
}

ll inv[MAXN];
ll p, r;
ll n;

int main() {
	while(scanf("%lld %lld %lld", &n, &p, &r) != EOF) {
		allInv(inv, p);
		if (n == 2) {
			if (r == 1) printf("2 1\n");
			else printf("-1 -1\n");
		}
		else if (n >= 2*p) {
			if (r == 0) printf("2 1\n");
			else printf("-1 -1\n");
		}
		else if (n >= p) {
			if (r == 0) {
				printf("%d 1\n", p == 2 ? 3 : 2);
				continue;
			}
			ll fat = 1;
			FOR1(i, n) {
				if (i == p) continue;
				fat = (i*fat) % p;
			}
			assert(fat > 0);
			ll invf = (inv[fat]*r)%p;
			assert(invf > 0);
			if (invf >= p) printf("-1 -1\n");
			else printf("%lld %lld\n", p, invf);
		}
		else {
			if (r == 0) {
				printf("-1 -1\n");
				continue;
			}
			ll fat = 1;
			FOR1(i, n) {
				fat = (i*fat) % p;
			}
			bool ok = false;
			FOR1(i, n) {
				ll x = ((r*i)%p)*inv[fat]%p;
				assert(x > 0);
				if (x < i) {
					ok = true;
					printf("%d %lld\n", i, x);
					break;
				}
			}
			if (!ok) printf("-1 -1\n");
		}
	}
	return 0;
}
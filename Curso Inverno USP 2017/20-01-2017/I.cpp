#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

ll modpot(ll a, ll e, ll m) {
	if (e == 0) return 1;
	ll k = modpot(a, e/2, m);
	k = (k*k)%m;
	if (e%2 != 0) k = (k*a)%m;
	return k;
}

bool mrtest (ll a, ll s, ll d, ll n){
    ll x = modpot(a, d, n);
    if (x == 1 | x == n-1) return true;
    for (; s > 0 ;s--)
        if ((x = (x * x) % n) == n-1) return true;
    return false;
}

bool millerrabin(ll n){
    ll s, d;
    if (n < 5 || n % 2 == 0 || n % 3 == 0)
        return (n == 2 || n == 3);
    for (s = 0, d = n-1; d % 2 == 0; s++, d /= 2);
    return  mrtest (2, s, d, n) &&
               (n <= 7 || mrtest (7, s, d, n)) &&
               (n <= 61 || mrtest (61, s, d, n));
}


int main() {
	ll a, b;
	while(scanf("%lld %lld", &a, &b) != EOF) {
		if (a == b) {
			printf("%lld\n", a);
			continue;
		}
		if (a == b+2) {
			printf("%lld->%lld\n", b, a);
			continue;
		}
		if (b == a+2) {
			printf("%lld->%lld\n", a, b);
			continue;
		}
		if (a == 3 && b == 7) {
			printf("3->5->7\n");
			continue;
		}
		if (b == 3 && a == 7) {
			printf("7->5->3\n");
			continue;
		}
		bool possible = true;
		vector<ll> ans;
		
		ans.push_back(a);
		if (a != 2) {
			if (millerrabin(a-2)) ans.push_back(2);
			else if (millerrabin(a+2)) ans.push_back(a+2), ans.push_back(2);
			else possible = false;
		}
		
		if (b != 2) {
			if (millerrabin(b-2)) ans.push_back(b);
			else if (millerrabin(b+2)) ans.push_back(b+2), ans.push_back(b);
			else possible = false;
		}
		
		if (!possible) printf("Unlucky Benny\n");
		else {
			for(int i=0; i<(int)ans.size(); i++) {
				if (i>0) printf("->");
				printf("%lld", ans[i]);
			}
			printf("\n");
		}
	}
	return 0;
}
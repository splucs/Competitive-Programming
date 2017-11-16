#include <bits/stdc++.h>
using namespace std;

int di[4] = {1, 0, -1, 0};
int dj[4] = {0, 1, 0, -1};

typedef long long ll;
typedef pair<ll, ll> ii;
ii pos(ll n) {
	ll x = 0, y = 0, cnt = 2, k = 0, nmoves = 1;
	n--;
	while(n > 0) {
		if (cnt == 0) {
			nmoves++;
			cnt = 2;
		}
		
		ll d = min(nmoves, n);
		x += d*di[k];
		y += d*dj[k];
		n -= d;
		
		cnt--;
		k = (k+1)%4;
	}
	
	return ii(x, y);
}

int main() {
	ll a, b;
	
	while(scanf("%I64d %I64d", &a, &b) != EOF) {
		ii p1 = pos(a);
		ii p2 = pos(b);
		printf("%I64d\n", abs(p1.first-p2.first) + abs(p1.second-p2.second));
	}
	
	return 0;
}
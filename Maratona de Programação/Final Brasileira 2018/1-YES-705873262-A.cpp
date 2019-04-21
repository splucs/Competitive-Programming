#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	ll r, s;
	char c;
	scanf("%lld%c%lld", &r, &c, &s);
	r = r * 100 + s;
	ll u = 36000;
	ll g = __gcd(u, r);
	cout<<(u / g)<<'\n';
}

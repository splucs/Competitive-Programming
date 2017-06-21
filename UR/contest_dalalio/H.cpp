#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll gcd(ll a, ll b){
	if (b == 0) return a;
	else return gcd(b, a%b);
}

int main()
{
	ll N;
	while(scanf(" %lld", &N)!=EOF){
		if (N == 0) break;
		ll num = N*N, den = N*N;
		ll sn = sqrt(N);
		for(ll i=1; i<=sn; i++){
			num -= (N/i)*i;
		}
		for(ll j=1; j<=sn; j++){
			ll a = N/(j+1) + 1;
			ll b = N/j;
			if (a <= sn) a = sn+1;
			if (a>b) continue;
			num -= (((a+b)*(b-a+1))/2)*j;
		}
		ll g = gcd(num, den);
		printf("%lld/%lld\n", num/g, den/g);
	}
	return 0;
}
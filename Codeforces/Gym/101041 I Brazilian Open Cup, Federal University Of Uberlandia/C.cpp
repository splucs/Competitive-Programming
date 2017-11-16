#include <iostream>
#define mod 1000000007
using namespace std;
typedef long long ll;

ll extGcd(ll a, ll b, ll &x, ll &y) {
	if (b == 0) {
		x = 1; y = 0;
		return a;
	}
	ll g = extGcd(b, a%b, y, x);
	y -= a / b * x;
	return g;
}

ll modInv(ll a, ll m) {
	ll x, y;
	extGcd(a, m, x, y);
	return (x%m + m)%m;
}

int main() {
	int n, m;
	cin >> n >> m;
	
	ll fat1 = 1, fat2 = 1;
	for (long long i = n+1; i <= n+m; i++) {
		fat1 *= i;
		fat1 %= mod;
	}
	for (long long i = 1; i <= m; i++) {
		fat2 *= i;
		fat2 %= mod;
	}
	
	fat2 = modInv(fat2, mod);
	fat1 = fat1*fat2;
	fat1 %= mod;
	
	cout << fat1 << endl;
}
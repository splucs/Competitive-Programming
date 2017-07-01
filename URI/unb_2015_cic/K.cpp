#include <bits/stdc++.h>
using namespace std;

template <typename T>
T gcd(T a, T b) {
    return b == 0 ? a : gcd(b, a % b);
}

template<typename T>
T modMul(T a, T b, T m){
	T x = 0, y = a % m;
	while (b > 0){
		if (b % 2 == 1) x = (x + y) % m;
		y = (y * 2) % m;
		b /= 2;
	}
	return x % m;
}

template<typename T>
T pollard(T n) {
	int i = 0, k = 2, d;
	T x = 3, y = 3;
	while (true) {
		i++;
		x = (modMul(x, x, n) + n - 1) % n;
		d = gcd(abs(y - x), n);
		if (d != 1 && d != n) return d;
		if (i == k) y = x, k *= 2;
	}
}

typedef long long ll;

ll getfac(ll n){
	if (n > 90000000000000ll){
		return pollard(n);
	}
	for(ll j=2; j*j <= n; j++){
		if (n % j == 0){
			return j;
		}
	}
}

int main()
{
	ll n, f[3];
	while(scanf("%lld", &n), n > 0){
		f[0] = getfac(n);
		n /= f[0]; 
		f[1] = getfac(n);
		n /= f[1];
		f[2] = n;
		sort(f, f+3);
		printf("%lld = %lld x %lld x %lld\n", f[0]*f[1]*f[2], f[0], f[1], f[2]);
	}
	return 0;
}
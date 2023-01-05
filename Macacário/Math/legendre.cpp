#include <cstdio>
#include <cstring>

typedef long long ll;

/*
 * Legendre's formula
 */

ll legendre(ll n, ll p) {
	int ans = 0;
	ll prod = p;
	while(prod <= n) {
		ans += n/prod;
		prod *= p;
	}
	return ans;
}

/*
 * TEST MATRIX
 */

ll fac[30];

int brute(ll n, ll p) {
	int ans = -1;
	ll prod = 1LL;
	while(fac[n]%prod == 0) {
		//printf("%lld%%%lld = 0\n", fac[n], prod);
		ans++;
		prod *= p;
	}
	return ans;
}

bool test(ll p) {
	for(ll n=1; n<=20LL; n++) {
		if (legendre(n, p) != brute(n, p)) {
			//printf("legendre(%lld, %lld) = %d\n", n, p, legendre(n, p));
			//printf("brute(%lld, %lld) = %d\n", n, p, brute(n, p));
			return false;
		}
	}
	return true;
}

int N;
bool prime[200000];

int main() {
	N = 200000;
	fac[0] = 1LL;
	for(ll i=1LL; i<=20LL; i++) {
		fac[i] = i*fac[i-1];
	}
	memset(&prime, true, sizeof prime);
	prime[0] = prime[1] = false;
	for(int i=2; i<N; i++) {
		if (prime[i]) {
			if (!test(i)) printf("failed for prime p = %d\n", i);
			for(int j=2*i; j<N; j+=i) prime[j] = false;
		}
	}
	return 0;
}
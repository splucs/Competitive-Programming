#include <cstdio>
#define MOD 1000000007LL
typedef long long ll;

template <typename T>
T extGcd(T a, T b, T& x, T& y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    else {
        T g = extGcd(b, a % b, y, x);
        y -= a / b * x;
        return g;
    }
}
 
template <typename T>
T modInv(T a, T m) {
    T x, y;
    extGcd(a, m, x, y);
    return (x % m + m) % m;
}
 
template <typename T>
T modDiv(T a, T b, T m) {
    return ((a % m) * modInv(b, m)) % m;
}

template<typename T>
T crt(T* a, T* p, int n, T m) {
    T P = 1;
    for(int i=0; i<n; i++) P = (P * p[i]) % m;
    T x = 0, pp;
    for(int i=0; i<n; i++) {
        pp = modDiv(P, p[i], m);
        x = (x + (((a[i] * pp) % m) * modInv(pp, p[i]))) % m;
    }
    return x;
}

/*TEST MATRIX*/
#include <cstdlib>
#define PRINTTEST 0

int primes[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59};

bool test(int ntests) {
	for(int t=0; t<ntests; t++) {
		int T = 17;
		ll y[20], a[20];
		for(int i=1; i<=T; i++) {
			if (PRINTTEST) printf("test %d:\n", t*T + i);
			for(int j=0; j<i; j++) {
				a[j] = primes[j];
				y[j] = rand()%a[j];
				if (PRINTTEST) printf("x = %lld mod %lld\n", y[j], a[j]);
			}
			ll ans = crt(y, a, i, MOD);
			if (PRINTTEST) printf("answer is x = %lld\n", ans);
			for(int j=0; j<i; j++) {
				ll mans = ans;
				int count = 10000;
				while(mans%a[j] != y[j] && count > 0) {
					mans += MOD;
					count--;
				}
				if (mans%a[j] != y[j]) {
					printf("failed on test %d, ans = %I64d\n", t*T + i, ans);
					return false;
				}
			}
		}
	}
	printf("All tests passed\n");
	return true;
}

int main()
{
	test(10000);
	return 0;
}
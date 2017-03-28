#include <cstdio>
#define MAXN 1009
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

ll chinesert(const int* y, const int* a, int n, ll mod) {
	ll ans = 0;
	ll mult = 1;
	int x[MAXN];
	for (int i = 0; i<n; i++) {
		x[i] = y[i];
		for (int j = 0; j<i; ++j) {
			ll cur = (x[i] - x[j]) * 1ll * modInv(a[j], a[i]);
			x[i] = (int)(cur % a[i]);
			if (x[i] < 0) x[i] += a[i];
		}
		ans = (ans + mult * 1ll * x[i]);
		mult = (mult * 1ll * a[i]);
		if (mod != -1) {
			ans %= mod;
			mult %= mod;
		}
	}
	return ans;
}

/*TEST MATRIX*/
#include <cstdlib>

int primes[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59};

bool test(int ntests){
	for(int t=0; t<ntests; t++){
		int T = 9;
		int y[20], a[20];
		for(int i=1; i<=T; i++){
			for(int j=0; j<i; j++){
				a[j] = primes[j];
				y[j] = rand()%a[j];
			}
			ll ans = chinesert(y, a, i, 1000000007ll);
			for(int j=0; j<i; j++){
				if (ans%a[j] != y[j]){
					printf("failed on test %d, ans = %I64d\n", i, ans);
					return false;
				}
			}
		}
	}
	return true;
}

int main()
{
	if (test(10000)) printf("All tests passed\n");
	return 0;
}
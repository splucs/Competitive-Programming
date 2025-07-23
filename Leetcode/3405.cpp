#define MOD 1000000007LL

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

class Solution {
public:
    int countGoodArrays(int n, int m, int k) {
        int ans = m;
        for (int i = n-1-k; i > 0; i--) {
            ans = (ans * (long long)(m-1)) % MOD;
        }
        if (k == 0 || k == n-1) {
            return ans;
        }
        long long fac = 1;
        for (long long i = 1; i < n; i++) {
            fac = (fac*i) % MOD;
            if (i == k) {
                ans = (ans * modInv(fac, MOD)) % MOD;
            }
            if (i == n-1-k) {
                ans = (ans * modInv(fac, MOD)) % MOD;
            }
        }
        ans = (ans * fac) % MOD;
        return ans;
    }
};

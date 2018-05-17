#include <vector>
#include <cstring>
using namespace std;

/*
 * Modular inverse
 */

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

/*
 * NTT - Number Theoretic Transform O(nlogn)
 */

typedef long long ll;

const ll mod[3] = {1004535809LL, 1092616193LL, 998244353LL};
const ll root[3] = {12289LL, 23747LL, 15311432LL};
const ll root_1[3] = {313564925LL, 642907570LL, 469870224LL};
const ll root_pw[3] = {1LL<<21, 1LL<<21, 1LL<<23};

void ntt(vector<ll> & a, bool invert, int m) {
	ll n = (ll)a.size();
	for(ll i=1, j=0; i<n; ++i) {
		ll bit = n >> 1;
		for (; j>=bit; bit>>=1) j -= bit;
		j += bit;
		if (i < j) swap(a[i], a[j]);
	}
	for(ll len=2, wlen; len<=n; len<<=1) {
		wlen = invert ? root_1[m] : root[m];
		for (ll i=len; i<root_pw[m]; i<<=1)
			wlen = (wlen * wlen % mod[m]);
		for(ll i=0; i<n; i+=len) {
			for(ll j=0, w=1; j<len/2; ++j) {
				ll u = a[i+j],  v = a[i+j+len/2] * w % mod[m];
				a[i+j] = (u+v < mod[m] ? u+v : u+v-mod[m]);
				a[i+j+len/2] = (u-v >= 0 ? u-v : u-v+mod[m]);
				w = w * wlen % mod[m];
			}
		}
	}
	if(invert) {
		ll nrev = modInv(n, mod[m]);
		for (ll i=0; i<n; ++i)
			a[i] = a[i] * nrev % mod[m];
	}
}

void convolution(vector<ll> a, vector<ll> b, vector<ll> & res, int m) {
	ll n = 1;
	while(n < max (a.size(), b.size())) n <<= 1;
	n <<= 1;
	a.resize(n), b.resize(n);
	ntt(a, false, m); ntt(b, false, m);
	res.resize(n);
	for(int i=0; i<n; ++i) res[i] = (a[i]*b[i])%mod[m];
	ntt(res, true, m);
}

/*
 * Stirling numbers
 * Compute s(n, k) for all k in [0, n] in O(nlog^2n) 
 */

void compute(vector<ll> & res, int l, int r, int m) {
	if (l == r) {
		res = vector<ll>({r, 1LL});
		return;
	}
	vector<ll> a, b;
	compute(a, l, (l + r) / 2, m);
	compute(b, (l + r) / 2 + 1, r, m);
	convolution(a, b, res, m);
}

void stirling_first(vector<ll> & res, int n, int m) {
	if (n == 0) {
		res = vector<ll>({1LL});
		return;
	}
	compute(res, 0, n-1, m);
	while(res.back() == 0) res.pop_back();
}

/*
 * TEST MATRIX
 */

#include <cstdio>

void printmatrix(int _n, int m) {
	printf("Stirling matrix of first kind mod %I64d:\n", mod[m]);
	for(int n = 0; n <= _n; n++) {
		vector<ll> row;
		stirling_first(row, n, m);
		for(int i = 0; i < (int)row.size(); i++) {
			printf("%I64d ", row[i]);
		}
		printf("\n");
	}
}

/*
 * Codeforces 960G
 */

#define MAXN 100009
 
template <typename T>
T modDiv(T a, T b, T m) {
    return ((a % m) * modInv(b, m)) % m;
}

ll fat[MAXN];
void preprocessfat(ll m) {
    fat[0] = 1;
    for(ll i=1; i<MAXN; i++) {
        fat[i] = (i*fat[i-1])%m;
    }
}

template<typename T>
T pascal(int n, int k, T m) {
    return modDiv(fat[n], (fat[k]*fat[n-k])%m, m);
}

int N, A, B;

int main() {
	scanf("%d %d %d", &N, &A, &B);
	preprocessfat(mod[2]);
	vector<ll> arr;
	stirling_first(arr, N-1, 2);
	ll ans;
	if (A+B-2 < 0 || A+B-2 >= int(arr.size())) {
		ans = 0;
	}
	else {
		ans = arr[A+B-2];
		ans *= pascal(A+B-2, A-1, mod[2]);
		ans %= mod[2];
	}
	printf("%I64d\n", ans);
	return 0;
}
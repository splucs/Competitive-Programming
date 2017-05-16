#include <bits/stdc++.h>
#define MAXN 100009
using namespace std;

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

const ll mod = 7340033;
const ll root = 5;
const ll root_1 = 4404020;
const ll root_pw = 1<<20;

void ntt (ll* a, ll n, bool invert) {
	for (ll i=1, j=0; i<n; ++i) {
		ll bit = n >> 1;
		for (; j>=bit; bit>>=1) j -= bit;
		j += bit;
		if (i < j) swap (a[i], a[j]);
	}
	for (ll len=2, wlen; len<=n; len<<=1) {
		wlen = invert ? root_1 : root;
		for (ll i=len; i<root_pw; i<<=1)
			wlen = (wlen * wlen % mod);
		for (ll i=0; i<n; i+=len) {
			for (ll j=0, w=1; j<len/2; ++j) {
				ll u = a[i+j],  v = a[i+j+len/2] * w % mod;
				a[i+j] = (u+v < mod ? u+v : u+v-mod);
				a[i+j+len/2] = (u-v >= 0 ? u-v : u-v+mod);
				w = w * wlen % mod;
			}
		}
	}
	if (invert) {
		ll nrev = modInv(n, mod);
		for (ll i=0; i<n; ++i)
			a[i] = a[i] * nrev % mod;
	}
}

void convolution (ll *a, ll *b, ll *res, int as, int bs) {
	ll n = 1;
	while (n < max (as, bs))  n <<= 1;
	n <<= 1;
	ntt (a, n, false);  ntt (b, n, false);
	for (int i=0; i<n; ++i) res[i] = (a[i]*b[i])%mod;
	ntt (res, n, true);
}

ll Aaux[4*MAXN], Baux[4*MAXN];

void circularconvolution(ll* a, ll* b, ll* res, int n) {
	for(int i=0; i<2*n; i++) Aaux[i] = i >= n ? 0 : a[i];
	for(int i=0; i<2*n; i++) Baux[i] = b[i%n];
	convolution(Aaux, Baux, res, 2*n, 2*n);
	for(int i=0; i<n; i++) res[i] = res[i+n];
}

char s1[MAXN], s2[MAXN];
ll A[5][MAXN], B[5][MAXN], M[5][5][MAXN];
int id[5], N;

int main(){
	scanf(" %s %s", s1, s2);
	N = strlen(s1);
	for(int i=0; i<5; i++) {
		for(int j=0; j<N; j++) A[i][j] = B[i][j] = 0;
		id[i] = i;
	}
	for(int i=0; i<N; i++) {
		A[s1[i] - 'A'][i] = 1;
		B[s2[i] - 'a'][N-1-i] = 1;
	}
	for(int i=0; i<5; i++) {
		for(int j=0; j<5; j++) {
			circularconvolution(A[i], B[j], M[i][j], N);
		}
	}
	ll ans = 0;
	do {
		for(int i=0; i<N; i++) {
			ll cur = 0;
			for(int j=0; j<5; j++){
				cur += M[j][id[j]][i];
			}
			ans = max(ans, cur);
		}
	}while(next_permutation(id, id+5));
	printf("%I64d\n", N-ans);
	return 0;
}
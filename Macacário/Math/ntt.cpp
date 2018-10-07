#include <vector>
#include <cstdio>
#include <cstring>
#define MAXN 100009
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
	for(ll i = 1, j = 0; i < n; i++) {
		ll bit = n >> 1;
		for (; j >= bit; bit >>= 1) j -= bit;
		j += bit;
		if (i < j) swap(a[i], a[j]);
	}
	for(ll len = 2, wlen; len <= n; len <<= 1) {
		wlen = invert ? root_1[m] : root[m];
		for (ll i = len; i < root_pw[m]; i <<= 1)
			wlen = (wlen * wlen % mod[m]);
		for(ll i = 0; i < n; i += len) {
			for(ll j = 0, w = 1; j < len/2; j++) {
				ll u = a[i+j],  v = a[i+j+len/2] * w % mod[m];
				a[i+j] = (u+v < mod[m] ? u+v : u+v-mod[m]);
				a[i+j+len/2] = (u-v >= 0 ? u-v : u-v+mod[m]);
				w = w * wlen % mod[m];
			}
		}
	}
	if (invert) {
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

void circularConv(vector<ll> &a, vector<ll> &b, vector<ll> &res, int m) {
	//assert(a.size() == b.size());
	int n = a.size();
	convolution(a, b, res, m);
	for(int i = n; i < (int)res.size(); i++)
		res[i%n] = (res[i%n]+res[i])%mod[m];
	res.resize(n);
}

/*
 * CRT NTT
 */

template<typename T>
T modMul(T a, T b, T m) {
	T x = 0, y = a % m;
	while (b > 0) {
		if (b % 2 == 1) x = (x + y) % m;
		y = (y * 2) % m;
		b /= 2;
	}
	return x % m;
}

//convolution mod 1,097,572,091,361,755,137
void modConv(vector<ll> a, vector<ll> b, vector<ll> & res) {
	vector<ll> r0, r1;
	convolution(a, b, r0, 0);
	convolution(a, b, r1, 1);
	ll x, y, s, r, p = mod[0]*mod[1];
	extGcd(mod[0], mod[1], r, s);
	res.resize(r0.size());
	for(int i=0; i<(int)res.size(); i++) {
		res[i] = (modMul((s*mod[1]+p)%p, r0[i], p)
		+ modMul((r*mod[0]+p)%p, r1[i], p) + p) % p;
	}
}

/*
 * SPOJ MUL
 */

char num1[MAXN], num2[MAXN];

int main()
{
	int n, na, nb, k;
	vector<ll> A, B, C;
	scanf("%d", &n);
	for(int i=0; i<n; i++) {
		scanf(" %s %s", num1, num2);
		na = strlen(num1);
		nb = strlen(num2);
		A.clear();
		B.clear();
		for(int j=na-1; j>=0; j--) {
			A.push_back(num1[j]-'0');
		}
		for(int j=nb-1; j>=0; j--) {
			B.push_back(num2[j]-'0');
		}
		modConv(A, B, C);
		while(C.size()>1 && C.back()==0) C.pop_back();
		na = nb = k = 0;
		for(int j=0; j<(int)C.size() || nb > 0; j++) {
			na = (nb + (j<(int)C.size() ? C[j] : 0))%10;
			nb = (nb + (j<(int)C.size() ? C[j] : 0))/10;
			num1[k++] = ((char)na) + '0';
		}
		for(int i=0; i<k/2; i++) {
			na = num1[i];
			num1[i] = num1[k-i-1];
			num1[k-i-1] = na;
		}
		num1[k] = '\0';
		printf("%s\n", num1);
	}
	return 0;
}
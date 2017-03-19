#include <vector>
#include <cstdio>
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
const ll root_pw = 1 << 20;

void ntt(vector<ll> & a, bool invert) {
	ll n = (ll)a.size();
	for (ll i = 1, j = 0; i<n; ++i) {
		ll bit = n >> 1;
		for (; j >= bit; bit >>= 1) j -= bit;
		j += bit;
		if (i < j) swap(a[i], a[j]);
	}
	for (ll len = 2, wlen; len <= n; len <<= 1) {
		wlen = invert ? root_1 : root;
		for (ll i = len; i<root_pw; i <<= 1)
			wlen = (wlen * wlen % mod);
		for (ll i = 0; i<n; i += len) {
			for (ll j = 0, w = 1; j<len / 2; ++j) {
				ll u = a[i + j], v = a[i + j + len / 2] * w % mod;
				a[i + j] = (u + v < mod ? u + v : u + v - mod);
				a[i + j + len / 2] = (u - v >= 0 ? u - v : u - v + mod);
				w = w * wlen % mod;
			}
		}
	}
	if (invert) {
		ll nrev = modInv(n, mod);
		for (ll i = 0; i<n; ++i)
			a[i] = a[i] * nrev % mod;
	}
}

void multiply(vector<ll> a, vector<ll> b, vector<ll> & res) {
	ll n = 1;
	while (n < max(a.size(), b.size()))  n <<= 1;
	n <<= 1;
	a.resize(n), b.resize(n);
	ntt(a, false);  ntt(b, false);
	res.resize(n);
	for (int i = 0; i<n; ++i) res[i] = (a[i] * b[i]) % mod;
	ntt(res, true);
}
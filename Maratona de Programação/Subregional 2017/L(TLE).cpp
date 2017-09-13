#include <bits/stdc++.h>
using namespace std;
#define MAXN 2600001

struct base {
	double x, y;
	base() : x(0), y(0) {}
	base(double _x, double _y = 0) : x(_x), y(_y) {}
	base operator +(base o) { return base(x+o.x, y+o.y); }
	base operator -(base o) { return base(x-o.x, y-o.y); }
	base operator *(base o) { return base(x*o.x - y*o.y, y*o.x + x*o.y); }
	base operator /(double k) { return base(x/k, y/k); }
	base operator =(double k) { return base(k, 0); }
	void operator *=(base o) {
		double tx = x*o.x - y*o.y;
		double ty = y*o.x + x*o.y;
		x = tx; y = ty;
	}
	void operator /=(double k) { x/=k, y/=k; }
	double real() {return x;}
	double imag() {return y;}
};

//typedef complex<double> base;

void fft(vector<base> & a, bool invert) {
	int n = (int)a.size();
	for(int i=1, j=0; i<n; i++) {
		int bit = n>>1;
		for(; j >= bit; bit>>=1) j -= bit;
		j += bit;
		if (i < j) swap(a[i], a[j]);
	}
		
	for(int len = 2; len <= n; len <<=1) {
		double ang = 2*M_PI/len * (invert ? -1 : 1);
		base wlen (cos(ang), sin(ang));
		for(int i=0; i<n; i+=len) {
			base w(1.0);
			for(int j=0; j<len/2; j++) {
				base u = a[i+j], v = a[i+j+len/2]*w;
				a[i+j] = u+v;
				a[i+j+len/2] = u-v;
				w *= wlen;
			}
		}
	}
	if (invert)
		for(int i=0; i<n; i++)
			a[i] /= (double)n;
}

void convolution(vector<base> a, vector<base> b, vector<base> & c) {
	int n = 1;
	while(n < (int)max(a.size(), b.size())) n <<=1;
	n <<= 1;
	a.resize(n); b.resize(n);
	fft(a, false); fft(b, false);
	c.resize(n);
	for(int i=0; i<n; i++) c[i] = a[i]*b[i];
	fft(c, true);
}

/*
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

const ll mod[2] = {1004535809LL, 1092616193LL};
const ll root[2] = {12289LL, 23747LL};
const ll root_1[2] = {313564925LL, 642907570LL};
const ll root_pw = 1LL<<21;

void ntt(vector<ll> & a, bool invert, int m) {
	ll n = (ll)a.size();
	for (ll i=1, j=0; i<n; ++i) {
		ll bit = n >> 1;
		for (; j>=bit; bit>>=1) j -= bit;
		j += bit;
		if (i < j) swap(a[i], a[j]);
	}
	for (ll len=2, wlen; len<=n; len<<=1) {
		wlen = invert ? root_1[m] : root[m];
		for (ll i=len; i<root_pw; i<<=1)
			wlen = (wlen * wlen % mod[m]);
		for (ll i=0; i<n; i+=len) {
			for (ll j=0, w=1; j<len/2; ++j) {
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
	while (n < max (a.size(), b.size())) n <<= 1;
	n <<= 1;
	a.resize(n), b.resize(n);
	ntt(a, false, m); ntt(b, false, m);
	res.resize(n);
	for(int i=0; i<n; ++i) res[i] = (a[i]*b[i])%mod[m];
	ntt(res, true, m);
}*/

char str[MAXN];
vector<base> f, g, h;

int main() {
	scanf("%s", str);
	int len = strlen(str);
	int sum = 0;
	f.assign(MAXN, 0);
	g.assign(MAXN, 0);
	f[0] = 1;
	g[MAXN-1] = 1;
	for(int i=0; i<len; i++) {
		sum += str[i] - 'a' + 1;
		f[sum] = 1;
		g[MAXN-sum-1] = 1;
	}
	convolution(f, g, h);
	int ans = 0;
	for(int i=MAXN; i<2*MAXN; i++) {
		//if (h[i]) ans++;
		if (fabs(h[i].real()) > 1e-3) ans++;
	}
	printf("%d\n", ans);
	return 0;
}

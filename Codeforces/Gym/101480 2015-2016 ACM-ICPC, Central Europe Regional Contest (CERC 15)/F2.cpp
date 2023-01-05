#include <bits/stdc++.h>
using namespace std;
#define MOD 1000003LL
#define SMOD 1024LL
#define MAXN 1000009

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
T modExp(T a, T b, T m) {
    if (b == 0) return (T)1;
    T c = modExp(a, b / 2, m);
    c = (c * c) % m;
    if (b % 2 != 0) c = (c*a)%MOD;
    return c;
}

typedef long long ll;
ll fat[MAXN];
void preprocessfat(){
    fat[0] = 1;
    for(ll i=1; i<MAXN; i++){
        fat[i] = (i*fat[i-1])%MOD;
    }
}

template<typename T>
T pascal(int n, int k, T m){
    return modDiv(fat[n], (fat[k]*fat[n-k])%m, m);
}

typedef complex<double> base;
 
void fft (vector<base> & a, bool invert) {
	int n = (int)a.size();
	for (int i=1, j=0; i<n; ++i) {
		int bit = n >> 1;
		for (; j>=bit; bit>>=1)
			j -= bit;
		j += bit;
		if (i < j) swap(a[i], a[j]);
	}
 
	for (int len=2; len<=n; len<<=1) {
		double ang = 2*M_PI/len * (invert ? -1 : 1);
		base wlen(cos(ang), sin(ang));
		for (int i=0; i<n; i+=len) {
			base w(1);
			for (int j=0; j<len/2; ++j) {
				base u = a[i+j],  v = a[i+j+len/2] * w;
				a[i+j] = u + v;
				a[i+j+len/2] = u - v;
				w *= wlen;
			}
		}
	}
	if (invert)
		for (int i=0; i<n; ++i)
			a[i] /= n;
}

void convolution (vector<base> a, vector<base> b, vector<base> & res) {
	int n = 1;
	while(n < max(a.size(), b.size())) n <<= 1;
	n <<= 1;
	a.resize(n), b.resize(n);
	fft(a, false);  fft(b, false);
	res.resize(n);
	for(int i=0; i<n; ++i) res[i] = a[i]*b[i];
	fft(res, true);
}

void sqrtConv(vector<ll> a, vector<ll> b, vector<ll> & c) {
	vector<base> ca[2], cb[2], cc[2][2];
	ca[0].resize(a.size());
	ca[1].resize(a.size());
	for(int i=0; i<(int)a.size(); i++) {
		ca[0][i] = base(a[i] % SMOD, 0);
		ca[1][i] = base(a[i] / SMOD, 0);
	}
	cb[0].resize(b.size());
	cb[1].resize(b.size());
	for(int i=0; i<(int)b.size(); i++) {
		cb[0][i] = base(b[i] % SMOD, 0);
		cb[1][i] = base(b[i] / SMOD, 0);
	}
	for(int l=0; l<2; l++) for(int r=0; r<2; r++)
		convolution(ca[l], cb[r], cc[l][r]);
	c.resize(cc[0][0].size());
	for(int i=0; i<(int)c.size(); i++) {
		c[i] =
		(((ll)round(cc[1][1][i].real()))%MOD*(SMOD*SMOD)%MOD)%MOD +
		((ll)round(cc[0][1][i].real()))%MOD*SMOD%MOD +
		((ll)round(cc[1][0][i].real()))%MOD*SMOD%MOD + 
		((ll)round(cc[0][0][i].real()))%MOD;
		c[i] %= MOD;
	}
}

int main() {
	preprocessfat();
	int N;
	ll a, b, c, l, t;
	while(scanf("%d %I64d %I64d %I64d", &N, &a, &b, &c) != EOF) {
		ll ans = 0;
		//first column
		for(int j=0; j<N; j++) {
			scanf("%I64d", &l);
			l %= MOD;
			if (j == 0) continue;
			ll k = (pascal(2*N-3-j, N-2, MOD)*l)%MOD;
			k = (k*modExp(a, N-1LL, MOD))%MOD;
			k = (k*modExp(b, N-1LL-j, MOD))%MOD;
			ans = (ans+k)%MOD;
		}
		//first line
		for(int i=0; i<N; i++) {
			scanf("%I64d", &l);
			l %= MOD;
			if (i == 0) continue;
			ll k = (pascal(2*N-3-i, N-2, MOD)*l)%MOD;
			k = (k*modExp(a, N-1LL-i, MOD))%MOD;
			k = (k*modExp(b, N-1LL, MOD))%MOD;
			ans = (ans+k)%MOD;
		}
		//all c
		vector<ll> va(N-1), vb(N-1), vab;
		ll pa = 1, pb = 1;
		for(int i=0; i<N-1; i++) {
			va[i] = modDiv(pa, fat[i], MOD);
			vb[i] = modDiv(pb, fat[i], MOD);
			pa = (pa*a)%MOD;
			pb = (pb*b)%MOD;
		}
		sqrtConv(va, vb, vab);
		for(int i=0; i<2*(N-1)-1; i++) {
			ans = (ans + ((fat[i]*c%MOD)*(vab[i]%MOD))%MOD)%MOD;
		}
		printf("%I64d\n", ans);
	}
	return 0;
}
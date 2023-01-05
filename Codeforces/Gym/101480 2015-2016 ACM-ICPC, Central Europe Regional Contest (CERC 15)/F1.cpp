#include <bits/stdc++.h>
using namespace std;
#define MOD 1000003LL
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
		modConv(va, vb, vab);
		for(int i=0; i<2*(N-1)-1; i++) {
			ans = (ans + ((fat[i]*c%MOD)*(vab[i]%MOD))%MOD)%MOD;
		}
		printf("%I64d\n", ans);
	}
	return 0;
}
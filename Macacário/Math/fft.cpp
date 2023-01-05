#include <vector>
#include <cstdio>
#include <complex>
using namespace std;

/*
 * Fast complex
 */

struct base { // faster than complex<double>
	double x, y;
	base() : x(0), y(0) {}
	base(double a, double b=0) : x(a), y(b) {}
	base operator/=(double k) { x/=k; y/=k; return (*this); }
	base operator*(base a) const { return base(x*a.x - y*a.y, x*a.y + y*a.x); }
	base operator*=(base a) {
		double tx = x*a.x - y*a.y;
		double ty = x*a.y + y*a.x;
		x = tx; y = ty;
		return (*this);
	}
	base operator=(double a) { x=a; y=0; return (*this); }
	base operator+(base a) const { return base(x+a.x, y+a.y); }
	base operator+=(base a) { x+=a.x; y+=a.y; return (*this); }
	base operator-(base a) const { return base(x-a.x, y-a.y); }
	base operator-=(base a) { x-=a.x; y-=a.y; return (*this); }
	double& real() { return x; }
	double& imag() { return y; }
};

/*
 * FFT - Fast Fourier Transform O(nlogn)
 */

//typedef complex<double> base;
 
void fft(vector<base> &a, bool invert) {
	int n = (int)a.size();
	for(int i = 1, j = 0; i < n; i++) {
		int bit = n >> 1;
		for(; j >= bit; bit >>= 1) j -= bit;
		j += bit;
		if (i < j) swap(a[i], a[j]);
	}
	for(int len = 2; len <= n; len <<= 1) {
		double ang = 2*acos(-1.0)/len * (invert ? -1 : 1);
		base wlen(cos(ang), sin(ang));
		for(int i = 0; i < n; i += len) {
			base w(1);
			for(int j = 0; j < len/2; j++) {
				base u = a[i+j], v = a[i+j+len/2] * w;
				a[i + j] = u + v;
				a[i + j + len/2] = u - v;
				w *= wlen;
			}
		}
	}
	for (int i = 0; invert && i < n; i++) a[i] /= n;
}

void convolution(vector<base> a, vector<base> b, vector<base> &res) {
	int n = 1;
	while(n < max(a.size(), b.size())) n <<= 1;
	n <<= 1;
	a.resize(n), b.resize(n);
	fft(a, false); fft(b, false);
	res.resize(n);
	for(int i=0; i<n; ++i) res[i] = a[i]*b[i];
	fft(res, true);
}

void circularConv(vector<base> &a, vector<base> &b, vector<base> &res) {
	//assert(a.size() == b.size());
	int n = a.size();
	convolution(a, b, res);
	for(int i = n; i < (int)res.size(); i++)
		res[i%n] += res[i];
	res.resize(n);
}

/*
 * SQRT DECOMPOSITION FOR FFT
 */

#include <cmath>
#define MOD 1000003LL
#define SMOD 1024LL // ~ sqrt(MOD)
typedef long long ll;

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

/*
 * TEST MATRIX
 */

int main()
{
	base a (1);
	base b (2);
	base c (3);
	base d (4);
	base e (5);
	base f (6);
	vector<base> A, B, C;
	A.push_back(c);
	A.push_back(b);
	A.push_back(a);
	B.push_back(f);
	B.push_back(e);
	B.push_back(d);
	B.push_back(c);
	convolution(A, B, C);
	for(int i=0; i<(int)C.size(); i++) {
		printf(" %.2f", C[i].real());
	}
	return 0;
}
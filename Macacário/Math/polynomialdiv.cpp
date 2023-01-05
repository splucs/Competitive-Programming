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
 * Polynomial Division
 */

#include <algorithm>

void inverse(vector<base> &a, int t) {
	if (t == 1) {
		a.resize(1); a[0].real() = 1.0/a[0].real();
		return;
	}
	vector<base> a0 = a;
	inverse(a0, (t/2) + (t%2));
	convolution(a0, a, a);
	a0.resize(t), a.resize(t);
	a[0] -= base(1.0);
	convolution(a0, a, a);
	a0.resize(t), a.resize(t);
	for(int i = 0; i < t; i++) a[i] = a0[i] - a[i];
}

void divide(vector<base> &a, vector<base> &b, vector<base> &d) {
	int n = a.size(), m = b.size();
	if (n < m) {
		d.clear(); d.push_back(0);
		return;
	}
	vector<base> ar = a, br = b;
	reverse(ar.begin(), ar.end());
	reverse(br.begin(), br.end());
	inverse(br, n - m + 1);
	convolution(ar, br, d);
	d.resize(n - m + 1);
	reverse(d.begin(), d.end());
}

void remainder(vector<base> &a, vector<base> &b, vector<base> &r) {
	int n = a.size(), m = b.size();
	if (n < m) { r = a; return; }
	vector<base> d, aux;
	divide(a, b, d);
	r = a;
	convolution(d, b, aux);
	r.resize(m-1); aux.resize(m-1);
	for(int i = 0; i < m-1; i++) r[i] -= aux[i];
}

/*
 * Multi-point evaluation in O((n+m) logn logm)
 */

#define MAXN 10000

vector<base> rp[4*MAXN];
void roots(int u, double x[], int i, int j) {
	if (i == j) {
		rp[u].resize(2); rp[u][0] = -x[i];
		rp[u][1] = 1.0; return;
	}
	int m = (i + j) / 2;
	roots(2*u, x, i, m); roots(2*u+1, x, m+1, j);
	convolution(rp[2*u], rp[2*u+1], rp[u]);
	rp[u].resize(j-i+2);
}

void roots(vector<base> &a, double x[], int n) {
	roots(1, x, 0, n-1); a = rp[1];
}

vector<base> ep[4*MAXN];
void multievaluate(int u, double x[], double y[], int i, int j) {
	if (i == j) {
		y[i] = 0;
		double p = 1;
		for(int k = 0; k < (int)ep[u].size(); k++)
			y[i] += ep[u][k].real()*p, p *= x[i];
		return;
	}
	remainder(ep[u], rp[2*u], ep[2*u]);
	remainder(ep[u], rp[2*u+1], ep[2*u+1]);
	int m = (i + j) / 2;
	multievaluate(2*u, x, y, i, m);
	multievaluate(2*u+1, x, y, m+1, j);
}

void multievaluate(vector<base> &a, double x[], double y[], int n) {
	roots(1, x, 0, n-1); ep[1] = a;
	multievaluate(1, x, y, 0, n-1);
}

/*
 * Polynomial interpolation O(n log^3 n)
 * horrible constant and time
 */

vector<double> y[MAXN];
double ya0[MAXN], yp[MAXN];
void interpolate(vector<base> &a, int u, double x[], int n) {
	if (n == 1) {
		a.resize(1); a[0] = y[u][0];
		return;
	}
	y[2*u] = y[u]; y[2*u].resize(n/2);
	vector<base> a0, a1, p;
	interpolate(a0, 2*u, x, n/2);
	roots(p, x, n/2);
	int m = n-(n/2);
	multievaluate(a0, x+(n/2), ya0, m);
	multievaluate(p,  x+(n/2), yp, m);
	y[2*u+1].resize(m);
	for(int i = 0; i < m; i++)
		y[2*u+1][i] = (y[u][n/2 + i] - ya0[i]) / yp[i];
	interpolate(a1, 2*u+1, x+(n/2), m);
	convolution(p, a1, a);
	int sz = max(a.size(), a0.size());
	a.resize(sz);
	for(int i = 0; i < sz && i < n/2; i++)
		a[i] += a0[i];
	a.resize(n);
}

void interpolate(vector<base> &a, double x[], double ry[], int n) {
	y[1].resize(n);
	for(int i = 0; i < n; i++) y[1][i] = ry[i];
	interpolate(a, 1, x, n);
}

/*
 * TEST MATRIX
 */

int main() {
	int n, m;
	vector<base> P, Q, D, R;
	
	scanf("%d", &n);
	P.resize(n);
	for(int i = 0; i < n; i++) scanf("%lf", &P[i].real());
	
	scanf("%d", &m);
	Q.resize(m);
	for(int i = 0; i < m; i++) scanf("%lf", &Q[i].real());

	vector<base> invP = P, invQ = Q;
	inverse(invP, 10);
	printf("first 10 terms of inverse of P:");
	for(int i = 0; i < 10; i++) printf(" %.0f", invP[i].real());
	printf("\n");
	
	inverse(invQ, 10);
	printf("first 10 terms of inverse of Q:");
	for(int i = 0; i < 10; i++) printf(" %.0f", invQ[i].real());
	printf("\n");

	divide(P, Q, D);
	printf("P/Q:");
	for(int i = 0; i < (int)D.size(); i++) printf(" %.3f", D[i].real());
	printf("\n");
	
	remainder(P, Q, R);
	printf("P%%Q:");
	for(int i = 0; i < (int)R.size(); i++) printf(" %.3f", R[i].real());
	printf("\n");

	scanf("%d", &n);
	double x[100];
	for(int i = 0; i < n; i++) scanf("%lf", &x[i]);
	vector<base> a;
	roots(a, x, n);
	printf("from roots:");
	for(int i = 0; i < (int)a.size(); i++) printf(" %.3f", a[i].real());
	printf("\n");

	double y[100];
	multievaluate(P, x, y, n);
	printf("y[i]:");
	for(int i = 0; i < n; i++) printf(" %.3f", y[i]);
	printf("\n");

	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%lf %lf", &x[i], &y[i]);
	interpolate(a, x, y, n);
	printf("interpolated a:");
	for(int i = 0; i < n; i++) printf(" %.3f", a[i]);
	printf("\n");

	return 0;
}
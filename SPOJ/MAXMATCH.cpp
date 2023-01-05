#include <vector>
#include <complex>
using namespace std;
#define MAXN 200009

/*
 * FFT
 */

struct base {
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
	base operator+(base a) const { return base(x+a.x, y+a.y); }
	base operator-(base a) const { return base(x-a.x, y-a.y); }
	double real() { return x; }
	double imag() { return y; }
};
 
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

void convolution(vector<base> a, vector<base> b, vector<base> & res) {
	int n = 1;
	while(n < max(a.size(), b.size())) n <<= 1;
	n <<= 1;
	a.resize(n), b.resize(n);
	fft(a, false); fft(b, false);
	res.resize(n);
	for(int i=0; i<n; ++i) res[i] = a[i]*b[i];
	fft(res, true);
}

template <typename T>
void circularconvolution(vector<T> a, vector<T> b, vector<T> & res) {
	int n = a.size();
	b.insert(b.end(), b.begin(), b.end());
	convolution(a, b, res);
	res = vector<T>(res.begin()+n, res.begin()+(2*n));
}

/*
 * String matching with FFT
 */

#include <cstring>
#include <algorithm>
#define ALFA 5

int reduce(char c) {
	if (c >= 'a' && c <= 'z') return c-'a';
	if (c >= 'A' && c <= 'Z') return c-'A'+'z';
	return -1;
}

void matchfft(const char *T, const char *P, int *match) {
	int n = strlen(T), m = strlen(P);
	memset(match, 0, n*sizeof(int));
	if (m > n) return;
	vector<base> Sa[ALFA], Sb[ALFA], M[ALFA];
	for(int c = 0; c<ALFA; c++) {
		Sa[c].resize(n); Sa[c].assign(n, 0);
		Sb[c].resize(n); Sb[c].assign(n, 0);
	}
	for(int i=0; i<n; i++) Sa[reduce(T[i])][i] = 1;
	for(int i=0; i<m; i++) Sb[reduce(P[i])][i] = 1;
	for(int c = 0; c<ALFA; c++) {
		reverse(Sb[c].begin(), Sb[c].end());
		circularconvolution(Sa[c], Sb[c], M[c]);
	}
	for(int i=0; i<n; i++) {
		for(int c=0; c<ALFA; c++) {
			match[(i+1)%n] += int(M[c][i].real() + 0.5);
		}
	}
}

/*
 * SPOJ MAXMATCH
 */

#include <cstdio>

int match[MAXN], K;
char T[MAXN], P[MAXN];

int main() {	
	while(scanf(" %s", T) != EOF) {
		
		int n = strlen(T);
		strcpy(P, T);
		for(int i=n; i<2*n; i++) T[i] = 'd';
		for(int i=n; i<2*n; i++) P[i] = 'e';
		T[2*n] = P[2*n] = 0;
		
		matchfft(P, T, match);
		int ans = 0;
		for(int i=1; i<n; i++) {
			if (ans < match[i]) ans = match[i];
		}
		printf("%d\n", ans);
		for(int i=1; i<n; i++) {
			if (ans == match[i]) printf("%d ", i);
		}
		printf("\n");
		
	}
	return 0;
}
#include <bits/stdc++.h>
using namespace std;
#define MAXN 2600001

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
		if (fabs(h[i].real()) > 1e-3) ans++;
	}
	printf("%d\n", ans);
	return 0;
}

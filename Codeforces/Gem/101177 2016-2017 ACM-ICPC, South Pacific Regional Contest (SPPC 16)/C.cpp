#include <bits/stdc++.h>
using namespace std;
#define MAXN 500009

typedef complex<double> base;
 
void fft(vector<base> & a, bool invert) {
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

char str[MAXN];
vector<base> dir[3], inv[3], circ[3];
int match[MAXN], adj[MAXN];

int main() {
	int N, P;
	
	while(scanf("%d %d", &N, &P) != EOF) {
		scanf(" %s", str);
		
		for(int k=0; k<3; k++) dir[k].assign(N, 0), inv[k].assign(N, 0);
		for(int i=0; i<N; i++) {
			adj[i] = -1;
			if (str[i] == 'R') dir[0][i] = inv[0][N-i-1] = 1;
			if (str[i] == 'B') dir[1][i] = inv[1][N-i-1] = 1;
			if (str[i] == 'Y') dir[2][i] = inv[2][N-i-1] = 1;
		}
		adj[N] = -1;
		
		circularconvolution(dir[0], inv[0], circ[0]);
		circularconvolution(dir[1], inv[1], circ[1]);
		circularconvolution(dir[2], inv[2], circ[2]);
		
		for(int i=0; i<N; i++) {
			match[i] = int(circ[0][i].real()+0.5) + int(circ[1][i].real()+0.5) + int(circ[2][i].real()+0.5);
			match[i] = N - match[i];
			if (adj[match[i]] == -1) adj[match[i]] = i+1;
		}
		
		sort(match, match+N);
		printf("%d\n", adj[match[P]]);
	}
	
	return 0;
}
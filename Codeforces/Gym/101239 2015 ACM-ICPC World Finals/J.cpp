#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define fi first
#define se second
#define MAXN 500009
#define MAXM 59
#define INF 0x3f3f3f3f
#define sz(x) int(x.size())
typedef long long ll;
typedef pair<int, int> ii;

typedef complex<double> base;

void fft(vector<base> &a, bool invert) {
	int n = a.size();
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
				base u = a[i+j], v = a[i+j+len/2]*w;
				a[i+j] = u+v;
				a[i+j+len/2] = u-v;
				w *= wlen;
			}
		}
	}
	for(int i = 0; invert && i < n; i++) a[i] /= n;
}

void convolution(vector<base> a, vector<base> b, vector<base> &res) {
	int n = 1;
	while(n < max(sz(a), sz(b))) n <<= 1;
	n <<= 1;
	a.resize(n), b.resize(n);
	fft(a, false); fft(b, false);
	res.resize(n);
	FOR(i, n) res[i] = a[i]*b[i];
	fft(res, true);
}

int main() {
	vector<base> A(MAXN), B;
	FOR1(i, MAXN) FOR1(j, MAXN) {
		if (i*1ll*j >= MAXN) break;
		A[i*j] = base(A[i*j].real()+1, A[i*j].imag());
	}
	convolution(A, A, B);
	vector<int> ans(sz(B));
	FOR(i, sz(ans)) {
		ans[i] = int(B[i].real() + 0.5);
	}
	int T;
	scanf("%d", &T);
	FOR1(caseNo, T) {
		int lo, hi;
		scanf("%d %d", &lo, &hi);
		int j = lo;
		for(int i = lo; i <= hi; i++) {
			if(ans[i] > ans[j]) j = i;
		}
		printf("%d %d\n", j, ans[j]);
	}
	return 0;
}
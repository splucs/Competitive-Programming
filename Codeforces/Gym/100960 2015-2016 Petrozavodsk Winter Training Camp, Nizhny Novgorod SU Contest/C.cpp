#include <bits/stdc++.h>
#define MAXN 140009
using namespace std;

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
	for(int i=0; i<n; i++) {
		res[i] = res[i+n];
	}
	res.resize(n);
}

char s1[MAXN], s2[MAXN];
vector<base> A[5], B[5], M[5][5];
int id[5], N;

int main(){
	scanf(" %s %s", s1, s2);
	
	N = strlen(s1);
	for(int i=0; i<5; i++) {
		A[i].assign(N, base(0, 0));
		B[i].assign(N, base(0, 0));
		id[i] = i;
	}
	for(int i=0; i<N; i++) {
		A[s1[i] - 'A'][i] = 1;
		B[s2[i] - 'a'][N-1-i] = 1;
	}
	
	for(int i=0; i<5; i++) {
		for(int j=0; j<5; j++) {
			circularconvolution(A[i], B[j], M[i][j]);
			/*printf("%c and %c:", i+'A', j+'a');
			for(int k=0; k<N; k++) {
				printf(" %I64d", M[i][j][k]);
			}
			printf("\n");*/
		}
	}
	
	int ans = 0;
	do {
		for(int i=0; i<N; i++) {
			int cur = 0;
			for(int j=0; j<5; j++){
				cur += int(M[j][id[j]][i].real() + 0.5);
			}
			ans = max(ans, cur);
		}
	}while(next_permutation(id, id+5));
	
	printf("%d\n", N-ans);
	return 0;
}
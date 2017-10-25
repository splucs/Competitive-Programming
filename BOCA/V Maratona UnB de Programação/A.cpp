#include <bits/stdc++.h>
using namespace std;
#define INF 1e+9
#define EPS 1e-9

typedef vector<vector<double> > matrix;

matrix operator *(const matrix & a, const matrix & b) {
	int n = a.size();
	int m = a[0].size();
	int p = b[0].size();
	matrix c;
	c.assign(n, vector<double>(p));
	for(int i=0; i<n; i++) {
		for(int j=0; j<p; j++) {
			c[i][j] = 0.0;
			for(int k=0; k<m; k++) {
				c[i][j] += a[i][k]*b[k][j];
				c[i][j] = min(c[i][j], INF+1000);
			}
		}
	}
	return c;
}

matrix id(int n) {
	matrix c;
	c.assign(n, vector<double>(n));
	for(int i=0; i<n; i++) c[i][i] = 1;
	return c;
}

matrix exp(matrix a, int n) {
	if (n == 0) return id(a.size());
	matrix b = exp(a, n/2);
	b = b*b;
	if (n % 2 != 0) b = a*b;
	return b;
}

int main() {
	
	double k, r, s, u;
	while(scanf("%lf %lf %lf %lf", &k, &r, &s, &u) != EOF) {
		matrix A = id(2);
		A[0][0] = k;
		A[0][1] = r;
		A[1][0] = s;
		A[1][1] = u;
		A = exp(A, 1000000000);
		bool boom = false;
		bool ext = true;
		for(int i=0; i<2; i++) {
			for(int j=0; j<2; j++) {
				if (fabs(A[i][j]) > INF) boom = true;
				if (fabs(A[i][j]) > EPS) ext = false;
			}
		}
		
		if (boom) printf("Explosao populacional\n");
		else if (ext) printf("Extincao\n");
		else printf("Estabilidade\n");
	}
	
	return 0;
	
	return 0;
}
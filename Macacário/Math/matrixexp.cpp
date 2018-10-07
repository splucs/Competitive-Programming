#include <cstdio>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cmath>
#define EPS 1e-5
using namespace std;

typedef long long ll;
typedef vector< vector< double > > matrix;

matrix operator +(matrix a, matrix b) {
	int n = (int)a.size();
	int m = (int)a[0].size();
	matrix c;
	c.resize(n);
	for(int i=0; i<n; i++) {
		c[i].resize(m);
		for(int j=0; j<m; j++) {
			c[i][j] = a[i][j] + b[i][j];
		}
	}
	return c;
}

matrix operator *(matrix a, matrix b) {
	int n = (int)a.size();
	if (a[0].size() != b.size()) printf("fail\n");
	int m = (int)b.size();
	int p = (int)b[0].size();
	matrix c;
	c.resize(n);
	for(int i=0; i<n; i++) {
		c[i].assign(p, 0);
		for(int j=0; j<p; j++) {
			for(int k=0; k<m; k++) {
				c[i][j] += a[i][k]*b[k][j];
			}
		}
	}
	return c;
}

matrix operator *(double k, matrix a) {
	int n = (int)a.size();
	int m = (int)a[0].size();
	for(int i=0; i<n; i++) {
		for(int j=0; j<m; j++) {
			a[i][j] *= k;
		}
	}
	return a;
}

matrix operator -(matrix a, matrix b) {
	return a + ((-1.0) * b);
}

void printmatrix(matrix & a) {
	int n = (int)a.size();
	int m = (int)a[0].size();
	for(int i=0; i<n; i++) {
		for(int j=0; j<m; j++) {
			printf("%c%.2f%c ", (i==0 && j==0 ? '[' : ' '), a[i][j], (j < m-1 ? ',' : i == n-1? ']' : ';'));
		}
		printf("\n");
	}
}

/*
 * Matrix Exp and fast Fibonacci
 */

matrix id(int n) {
	matrix c(n, vector<double>(n));
	for(int i = 0; i < n; i++) c[i][i] = 1;
	return c;
}

matrix matrixExp(matrix a, int n) {
	if (n == 0) return id(a.size());
	matrix c = matrixExp(a, n/2);
	c = c*c;
	if (n%2 != 0) c = c*a;
	return c;
}

matrix fibo() {
	matrix c(2, vector<double>(2, 1));
	c[1][1] = 0;
	return c;
}

double fibo(int n) {
	matrix f = matrixExp(fibo(), n);
	return f[0][1];
}

/*
 * TEST MATRIX
 */

int main() {
	int n;
	while(scanf("%d", &n) != EOF) {
		printf("%f\n", fibo(n));
	}
	return 0;
}
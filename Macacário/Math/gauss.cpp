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

matrix id(int n) {
	matrix c; c.resize(n);
	for(int i=0; i<n; i++) {
		c[i].assign(n, 0);
		c[i][i] = 1;
	}
	return c;
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
 * Gauss elimination
 */

void switchLines(matrix & a, int i, int j) {
	int m = (int)a[i].size();
	for(int k = 0; k < m; k++) swap(a[i][k], a[j][k]);
}

void lineSumTo(matrix & a, int i, int j, double c) {
	int m = (int)a[0].size();
	for(int k = 0; k < m; k++) a[j][k] += c*a[i][k];
}

bool gauss(matrix & a, matrix & b, int & switches) {
	switches = 0;
	int n = (int)a.size();
	int m = (int)a[0].size();
	for(int i = 0, l; i < min(n, m); i++) {
		l = i;
		while(l < n && fabs(a[l][i]) < EPS) l++;
		if (l == n) return false;
		switchLines(a, i, l);
		switchLines(b, i, l);
		switches++;
		for(int j=0; j<n; j++) {
			if (i == j) continue;
			double p = -a[j][i] / a[i][i];
			lineSumTo(a, i, j, p);
			lineSumTo(b, i, j, p);
		}
	}
	return true;
}

double det(matrix a) {
	int n = a.size();
	matrix b(n);
	for(int i=0; i<n; i++) b[i].resize(1);
	int sw = 0;
	if (gauss(a, b, sw)) {
		double ans = 1;
		for(int i=0; i<n; i++) ans *= a[i][i];
		return sw % 2 == 0 ? ans : -ans;
	}
	return 0.0;
}

/*
 * TEST MATRIX
 */

bool testgauss(int ntest) {
	srand(time(NULL));
	for(int n=1; n<ntest; n++) {
		double d;
		matrix A = id(n), B, X;
		B.resize(n);
		X.resize(n);
		for(int i=0; i<n; i++) {
			X[i].push_back(rand()%10);
			for(int j=0; j<n; j++) {
				A[i][j] = -2 + rand()%10;
			}
		}
		B = A*X;
		d = det(A);
		int sw;
		if (gauss(A, B, sw)) {
			for(int i=0; i<n; i++) {
				if (fabs(X[i][0] - B[i][0]/A[i][i]) > EPS) {
					printf("failed test %d\n", n);
					return false;
				}
			}
		}
	}
	printf("all gauss tests passed\n");
	return true;
}

bool testdet(int ntest) {
	matrix a;
	for(int n=1; n<=ntest; n++) {
		a = id(2);
		a[0][0] = rand()%100;
		a[1][0] = rand()%100;
		a[0][1] = rand()%100;
		a[1][1] = rand()%100;
		if (fabs(det(a)-(a[0][0]*a[1][1] - a[0][1]*a[1][0])) > EPS) {
			printf("falied test  %d\n", n);
			return false;
		}
	}
	
	printf("all gauss tests passed\n");
	return true;
}

int main() {
	testgauss(100);
	testdet(100);
	return 0;
}


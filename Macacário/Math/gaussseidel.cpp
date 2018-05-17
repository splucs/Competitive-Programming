#include <cstdio>
#include <algorithm>
#include <vector>
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

/*
 * Gauss-Seidel method
 */

matrix gaussSeidel(matrix & a, matrix & b, double PREC) {
	int n = (int)a.size();
	matrix x = b, xp = b;
	double error;
	do {
		error = 0.0;
		for(int i=0; i<n; i++) {
			xp[i][0] = b[i][0];
			for(int j=0; j<n; j++) {
				if (i < j) xp[i][0] -= a[i][j]*xp[j][0];
				if (i > j) xp[i][0] -= a[i][j]*x[j][0];
			}
			xp[i][0] /= a[i][i];
			error = max(error, fabs(xp[i][0]-x[i][0]));
		}
		x = xp;
	} while(error > PREC);
	return xp;
}

/*
 * TEST MATRIX
 */
#include <ctime>

bool test(int nTests) {
	srand(time(NULL));
	for(int n=1; n<=nTests; n++) {
		double PREC = 1e-4;
		matrix A, B, X, Xp;
		A.resize(n);
		B.resize(n);
		X.resize(n);
		for(int i=0; i<n; i++) {
			X[i].push_back((rand()%10)/10.0);
			A[i].resize(n);
			for(int j=0; j<n; j++) {
				A[i][j] = -(rand()%10)/100000.0;
			}
			A[i][i] = 1.0;
		}
		B = A*X;
		Xp = gaussSeidel(A, B, PREC);
		for(int i=0; i<n; i++) {
			if (fabs(X[i][0] - Xp[i][0]) > PREC) {
				printf("failed test n = %d\n", n);
				return false;
			}
		}
	}
	printf("all tests passed\n");
	return true;
}

int main() {
	test(500);
	return 0;
}


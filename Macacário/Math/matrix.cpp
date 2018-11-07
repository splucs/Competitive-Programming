#include <vector>
using namespace std;

/*
 * Matrix operations
 */

typedef long long ll;
typedef vector< vector< double > > matrix;

matrix operator +(matrix a, matrix b) {
	int n = (int)a.size();
	int m = (int)a[0].size();
	matrix c;
	c.resize(n);
	for(int i=0; i<n; i++) {
		c[i].resize(m);
		for(int j=0; j<m; j++)
			c[i][j] = a[i][j] + b[i][j];
	}
	return c;
}

matrix operator *(matrix a, matrix b) {
	int n = (int)a.size();
	//assert(a[0].size() == b.size());
	int m = (int)b.size();
	int p = (int)b[0].size();
	matrix c(n, vector<double>(p));
	vector<double> col(m);
	for (int j = 0; j < p; j++) {
		for (int k = 0; k < m; k++)
			col[k] = b[k][j];
		for (int i = 0; i < n; i++) {
			double s = 0;
			for (int k = 0; k < m; k++)
				s += a[i][k] * col[k];
			c[i][j] = s;
		}
	}
	return c;
}

matrix operator *(double k, matrix a) {
	int n = (int)a.size();
	int m = (int)a[0].size();
	for(int i=0; i<n; i++) for(int j=0; j<m; j++)
		a[i][j] *= k;
	return a;
}

matrix operator -(matrix a, matrix b) {
	return a + ((-1.0) * b);
}

matrix id(int n) {
	matrix c(n, vector<double>(n));
	for(int i = 0; i < n; i++) c[i][i] = 1;
	return c;
}

#include <cstdio>
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
 * COMPILATION TEST
 */

int main() {}
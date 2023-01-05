#include <vector>
#include <math.h>
#include <stdio.h>
#define mod 1000000007
using namespace std;

typedef long long ll;
typedef vector< vector<long long > > matrix;

matrix operator *(matrix a, matrix b) {
	int n = (int) a.size();
	int m = (int) b.size();
	int p = (int) b[0].size();
	
	matrix c;
	c.resize(n);
	for (int i = 0; i < n; i++) {
		c[i].assign(p, 0);
		for (int j = 0; j < p; j++) {
			for (int k = 0; k < m; k++) {
				c[i][j] += a[i][k] * b[k][j];
				c[i][j] %= mod;
			}
		}
	}
	return c;
}

matrix id(int n) {
	matrix c;
	c.resize(n);
	for (int i = 0; i < n; i++) {
		c[i].assign(n, 0);
		c[i][i] = 1;
	}
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
	matrix c;
	c.resize(2);
	c[0].assign(2, 1);
	c[1].assign(2, 1);
	c[1][1] = 0;
	return c;
}

long long fibo(int n) {
	matrix f = matrixExp(fibo(), n);
	return f[0][1];
}

int main() {
	int n;
	scanf("%d", &n);
	while(n--) {
		int k;
		scanf("%d", &k);
		printf("%I64d\n", fibo(k));
	}
	return 0;
}
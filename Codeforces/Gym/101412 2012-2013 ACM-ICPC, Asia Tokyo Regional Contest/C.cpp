#include <bits/stdc++.h>
using namespace std;
#define EPS 1e-5

typedef long long ll;
typedef vector< vector< int > > matrix;
int M;

matrix operator +(matrix a, matrix b){
	int n = (int)a.size();
	int m = (int)a[0].size();
	matrix c;
	c.resize(n);
	for(int i=0; i<n; i++){
		c[i].resize(m);
		for(int j=0; j<m; j++){
			c[i][j] = a[i][j] + b[i][j];
			c[i][j] %= M;
		}
	}
	return c;
}

matrix operator *(matrix a, matrix b){
	int n = (int)a.size();
	if (a[0].size() != b.size()) printf("fail\n");
	int m = (int)b.size();
	int p = (int)b[0].size();
	matrix c;
	c.resize(n);
	for(int i=0; i<n; i++){
		c[i].assign(p, 0);
		for(int j=0; j<p; j++){
			for(int k=0; k<m; k++){
				c[i][j] += a[i][k]*b[k][j];
				c[i][j] %= M;
			}
		}
	}
	return c;
}

matrix operator *(int k, matrix a){
	int n = (int)a.size();
	int m = (int)a[0].size();
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			a[i][j] *= k;
			a[i][j] %= M;
		}
	}
	return a;
}

matrix operator -(matrix a, matrix b){
	return a + ((-1.0) * b);
}

void printmatrix(matrix & a){
	int n = (int)a.size();
	int m = (int)a[0].size();
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			printf("%c%.2f%c ", (i==0 && j==0 ? '[' : ' '), a[i][j], (j < m-1 ? ',' : i == n-1? ']' : ';'));
		}
		printf("\n");
	}
}

/*
 * Matrix Exp and fast Fibonacci
 */
matrix id(int n) {
	matrix c;
	c.resize(n);
	for (int i = 0; i < n; i++) {
		c[i].assign(n, 0);
		c[i][i] = 1;
	}
	return c;
}
 
matrix matrixExp(matrix a, int n){
	if (n == 0) return id(a.size());
	matrix c = matrixExp(a, n/2);
	c = c*c;
	if (n%2 != 0) c = c*a;
	return c;
}

int main() {
	int N, A, B, C, T, val;
	while(scanf("%d %d %d %d %d %d", &N, &M, &A, &B, &C, &T) != EOF && (N != 0)) {
		matrix c;
		c.resize(N);
		for (int i = 0; i < N; i++) {
			c[i].assign(N, 0);
			c[i][i] = B;
			if (i > 0) c[i][i-1] = A;
			if (i < N-1) c[i][i+1] = C;
		}
		matrix exponencial = matrixExp(c, T);
		vector<int> fs, ans;
		
		for (int i = 0; i < N; i++) {
			scanf("%d", &val); fs.push_back(val);
		}
		for (int i = 0; i < N; i++) {
			val = 0;
			for (int j = 0; j < N; j++) {
				val += fs[j]*exponencial[i][j];
				val %= M;
			}
			ans.push_back(val);
		}
		for (int i = 0; i < N; i++) {
			if (i > 0) printf(" ");
			printf("%d", ans[i]);
		}
		printf("\n");
	}
}
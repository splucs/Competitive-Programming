#include <bits/stdc++.h>
#define EPS 1e-9
using namespace std;

typedef vector< vector< double > > matrix;

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
			}
		}
	}
	return c;
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

matrix id(int n){
	matrix c; c.resize(n);
	for(int i=0; i<n; i++){
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
	int N, Q, s, t, L;
	while(scanf("%d", &N) != EOF) {
		matrix m = id(N);
		for(int i=0; i<N; i++) {
			for(int j=0; j<N; j++) {
				scanf("%lf", &m[j][i]);
			}
		}
		scanf("%d", &Q);
		while(Q-->0) {
			scanf("%d %d %d", &s, &t, &L);
			printf("%.6f\n", matrixExp(m, L)[s-1][t-1]);
		}
	}
	return 0;
}
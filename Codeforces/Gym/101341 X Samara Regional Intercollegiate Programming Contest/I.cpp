#include <bits/stdc++.h>
using namespace std;
#define MOD 1000000007LL
#define NITER 3

typedef long long ll;
typedef vector< vector<long long> > matrix;

bool operator ==(matrix a, matrix b){
	int n = (int)a.size();
	if (b.size() != n) return false;
	int m = (int)a[0].size();
	if (b[0].size() != m) return false;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if (a[i][j] != b[i][j]) return false;
		}
	}
	return true;
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
				c[i][j] %= MOD;
			}
		}
	}
	return c;
}

matrix randmat(int n, int m){
	matrix c;
	c.resize(n);
	for(int i=0; i<n; i++){
		c[i].resize(m);
		for(int j=0; j<m; j++){
			c[i][j] = rand()%MOD;
		}
	}
	return c;
}

void read(matrix & a){
	int n = (int)a.size();
	int m = (int)a[0].size();
	for(int i=0; i<n; i++) {
		for(int j=0; j<m; j++){
			scanf("%I64d", &a[i][j]);
		}
	}
}

void printmat(matrix a){
	int n = (int)a.size();
	int m = (int)a[0].size();
	for(int i=0; i<n; i++) {
		for(int j=0; j<m; j++){
			printf("%I64d ", a[i][j]);
		}
		printf("\n");
	}
}

int main(){
	int N;
	scanf("%d", &N);
	matrix A = randmat(N, N);
	matrix B = randmat(N, N);
	matrix C = randmat(N, N);
	matrix R = randmat(N, 1);
	read(A);
	read(B);
	read(C);
	srand(time(NULL));
	bool possible = true;
	for(int it=0; it<NITER; it++){
		R = randmat(N, 1);
		if (!((C*R) == (A*(B*R)))){
			possible = false;
		}
	}
	if (possible) printf("YES\n");
	else printf("NO\n");
	return 0;
}
#include <bits/stdc++.h>
using namespace std;
#define MOD 1000000009LL

int M;
bool board[4][3];

bool possible(int mask1, int mask2) {
	//if (mask2 % (1<<4) != mask1 / (1<<4)) return false;
	memset(&board, 0, sizeof board);
	for(int i=0; i<M; i++){
		board[i][0] = (mask1 & (1 << i)) > 0;
		board[i][1] = (mask1 & (1 << (M + i))) > 0;
		board[i][2] = (mask2 & (1 << (M + i))) > 0;
		if (board[i][1] != ((mask2 & (1 << i)) > 0)) {
			return false;
		}
	}
	for(int i=0; i<M; i++){
		for(int j=0; j<3; j++) {
			for(int il=0; il<M; il++) {
				for(int jl=0; jl<3; jl++) {
					if (abs(i-il) + abs(j-jl) == 3 && abs(i-il) < 3 && abs(j-jl) < 3 && board[i][j] && board[il][jl]) return false;
				}
			}
		}
	}
	return true;
}

typedef long long ll;
typedef vector< vector< ll > > matrix;

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

vector< vector<int> > adjA, adjB;

matrix sparsemult(matrix a, matrix b){
	int n = (int)a.size();
	if (a[0].size() != b.size()) printf("fail\n");
	int m = (int)b.size();
	int p = (int)b[0].size();
	adjA.resize(n);
	for(int i=0; i<n; i++) {
		adjA[i].clear();
		for(int k=0; k<m; k++) {
			if (a[i][k] != 0) adjA[i].push_back(k);
		}
	}
	adjB.resize(p);
	for(int j=0; j<p; j++) {
		adjB[j].clear();
		for(int k=0; k<m; k++) {
			if (b[k][j] != 0) adjB[j].push_back(k);
		}
	}
	matrix c;
	c.resize(n);
	for(int i=0; i<n; i++){
		c[i].assign(p, 0);
		for(int j=0; j<p; j++){
			for(int u=0, v=0, k; u<(int)adjA[i].size() && v<(int)adjB[j].size();){
				if (adjA[i][u] > adjB[j][v]) v++;
				else if (adjA[i][u] < adjB[j][v]) u++;
				else {
					k = adjA[i][u];
					c[i][j] += a[i][k]*b[k][j];
					c[i][j] %= MOD;
					u++; v++;
				}
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
			printf("%c%lld%c ", (i==0 && j==0 ? '[' : ' '), a[i][j], (j < m-1 ? ',' : i == n-1? ']' : ';'));
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
	c = sparsemult(c, c);
	if (n%2 != 0) c = sparsemult(c, a);
	return c;
}

matrix A, B;
	
int main() {
	int T, N, M2;
	scanf("%d", &T);
	while(T-->0) {
		scanf("%d %d", &M, &N);
		M2 = 1 << (2*M);
		A = id(M2);
		B.resize(M2);
		//printf("computing A:\n");
		for(int i=0; i < M2; i++) {
			B[i].resize(1);
			B[i][0] = 0;
			for(int j=0; j < M2; j++) {
				A[i][j] = possible(j, i);
				//printf("%lld ", A[i][j]);
			}
			//printf("\n");
		}
		//printf("preparing to calculate\n");
		B[0][0] = 1;
		A = matrixExp(A, N);
		A = A*B;
		//printmatrix(A);
		ll ans = 0;
		for(int i=0; i<M2; i++) {
			ans = (ans + A[i][0]) % MOD;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
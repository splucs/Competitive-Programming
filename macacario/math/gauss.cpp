#include <cstdio>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cmath>
#define EPS 1e-5
using namespace std;

typedef long long ll;
typedef vector< vector< double > > matrix;

matrix operator +(matrix a, matrix b){
	int n = (int)a.size();
	int m = (int)a[0].size();
	matrix c;
	c.resize(n);
	for(int i=0; i<n; i++){
		c[i].resize(m);
		for(int j=0; j<m; j++){
			c[i][j] = a[i][j] + b[i][j];
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
			}
		}
	}
	return c;
}

matrix operator *(double k, matrix a){
	int n = (int)a.size();
	int m = (int)a[0].size();
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			a[i][j] *= k;
		}
	}
	return a;
}

matrix operator -(matrix a, matrix b){
	return a + ((-1.0) * b);
}

matrix id(int n){
	matrix c; c.resize(n);
	for(int i=0; i<n; i++){
		c[i].assign(n, 0);
		c[i][i] = 1;
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

/*
 * Gauss elimination
 */

bool comlumnHasNonZero(matrix & a, int j){
	int n = (int)a.size();
	for(int i = 0; i < n; i++){
		if (fabs(a[i][j]) > EPS) return true;
	}
	return false;
}

bool lineHasNonZero(matrix & a, int i){
	int m = (int)a[0].size();
	for(int j = 0; j < m; j++){
		if (fabs(a[i][j]) > EPS) return true;
	}
	return false;
}

bool hasNonZero(matrix & a){
	int n = (int)a.size();
	for(int i = 0; i < n; i++){
		if (lineHasNonZero(a, i)) return true;
	}
	return false;
}

void switchColumns(matrix & a, int i, int j){
	double tmp;
	int n = (int)a.size();
	for(int k=0; k<n; k++){
		tmp = a[k][i];
		a[k][i] = a[k][j];
		a[k][j] = tmp;
	}
}

void switchLines(matrix & a, int i, int j){
	double tmp;
	int m = (int)a[i].size();
	for(int k=0; k<m; k++){
		tmp = a[i][k];
		a[i][k] = a[j][k];
		a[j][k] = tmp;
	}
}

bool fix(matrix & a, int i, int j){
	int n = (int)a.size();
	int m = (int)a[0].size();
	int l = i, c = j;
	bool switched = false;
	while (l < n && !lineHasNonZero(a, l)) l++;
	if (l == n) return false;
	if (i!=l){
		switched = !switched;
		switchLines(a, i, l);
	}
	while (c < m && fabs(a[i][c])<EPS) c++;
	if (j!=c){
		switched = !switched;
		switchColumns(a, j, c);
	}
	return switched;
}

double det(matrix a){
	int n = a.size();
    if(n == 1) return a[0][0];
	double sig = (fix(a, 0, 0) ? -1 : 1);
    matrix b = id(n-1);
    for (int i=0; i<n-1; i++){
        for (int j=0; j<n-1; j++){
            b[i][j] = a[i+1][j+1]*a[0][0] - a[i+1][0]*a[0][j+1];
        }
    }
    double d = det(b)/pow(a[0][0], n-2);
    return sig*d;
}

void lineSumTo(matrix & a, int i, int j, double c){
	int m = (int)a[0].size();
	for(int k=0; k<m; k++){
		a[j][k] += c*a[i][k];
	}
}

void columnSumTo(matrix & a, int i, int j, double c){
	int n = (int)a.size();
	for(int k=0; k<n; k++){
		a[k][j] += c*a[k][i];
	}
}

bool gauss(matrix & a, matrix & b){
	int n = (int)a.size();
	int m = (int)a[0].size();
	double p;
	for(int i = 0, l; i < min(n, m); i++){
		l = i;
		while(l < n && fabs(a[l][i])<EPS) l++;
		if (l == n) return false;
		switchLines(a, i, l);
		switchLines(b, i, l);
		for(int j=i+1; j<n; j++){
			p = -a[j][i]/a[i][i];
			lineSumTo(a, i, j, p);
			lineSumTo(b, i, j, p);
		}
	}
	for(int i=min(n, m)-1; i>=0; i--){
		for(int j=0; j<i; j++){
			p = -a[j][i]/a[i][i];
			lineSumTo(a, i, j, p);
			lineSumTo(b, i, j, p);
		}
	}
	return true;
}

int main(){
	srand(time(NULL));
	for(int n=1; n<1000; n++){
		printf("n = %d\n", n);
		double d;
		matrix A = id(n), B, X;
		B.resize(n);
		X.resize(n);
		for(int i=0; i<n; i++){
			X[i].push_back(rand()%10);
			for(int j=0; j<n; j++){
				A[i][j] = -2 + rand()%10;
			}
		}
		B = A*X;
		d = det(A);
		if (gauss(A, B)){
			for(int i=0; i<n; i++){
				if (fabs(X[i][0] - B[i][0]/A[i][i]) > EPS){
					printf("falied test n = %d\n", n);
					break;
				}
			}
		}
	}
	return 0;
}


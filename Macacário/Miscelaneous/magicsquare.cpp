#include <cstdio>
#include <cstring>
#define MAXN 1009

/*
 * Magic Square
 */

int mat[MAXN][MAXN], n;	//0-indexed

void magicsquare() {
	int i=n-1, j=n/2;
	memset(&mat, 0, sizeof mat);
	for(int k = 1; k <= n*n; k++) {
		mat[i][j] = k;
		if (mat[(i+1)%n][(j+1)%n] > 0) {
			i = (i-1+n)%n;
		}
		else {
			i = (i+1)%n;
			j = (j+1)%n;
		}
	}
}

/*
 * TEST MATRIX
 */

int main() {
	scanf("%d", &n);
	magicsquare();
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			if (j > 0) printf(" ");
			printf("%d", mat[i][j]);
		}
		printf("\n");
	}
	return 0;
}
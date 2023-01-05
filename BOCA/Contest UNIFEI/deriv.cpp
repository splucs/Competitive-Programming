#include <bits/stdc++.h>
using namespace std;
#define EPS 0.04999

int mat[3][3], X[3][3], Y[3][3];

int main() {
	for(int i=2; i>=0; i--) {
		for(int j=0; j<3; j++) {
			scanf("%d", &mat[i][j]);
		}
	}
	//X
	for(int i=0; i<3; i++) {
		X[i][0] = (-3*mat[i][0] + 4*mat[i][1] - mat[i][2]);
		X[i][1] = (-mat[i][0] + mat[i][2]);
		X[i][2] = (mat[i][0] - 4*mat[i][1] + 3*mat[i][2]);
	}
	//Y
	for(int i=0; i<3; i++) {
		Y[0][i] = (-3*mat[0][i] + 4*mat[1][i]- mat[2][i]);
		Y[1][i] = (-mat[0][i] + mat[2][i]);
		Y[2][i] = (mat[0][i] - 4*mat[1][i] + 3*mat[2][i]);
	}
	printf("Derivacao em X:\n");
	for(int i=2; i>=0; i--) {
		for(int j=0; j<3; j++) {
			printf("%8d", X[i][j]/2);
			if (X[i][j]%2 == 0) printf(".0");
			else printf(".5");
		}
		printf("\n");
	}
	printf("Derivacao em Y:\n");
	for(int i=2; i>=0; i--) {
		for(int j=0; j<3; j++){
			printf("%8d", Y[i][j]/2);
			if (Y[i][j]%2 == 0) printf(".0");
			else printf(".5");
		}
		printf("\n");
	}
}
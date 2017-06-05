#include <cstdio>
#define MAXN 1009;
int n, mat[MAXN][MAXN], aux[MAXN][MAXN];
//clockwise
void rotateclockwise(){
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j){
			aux[j][n-i-1]=mat[i][j];
		}
	}
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j){
			mat[i][j]=aux[i][j];
		}
	}
}
//counter-clockwise
void rotatecounterclockwise(){
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j){
			aux[i][j]=mat[j][n-i-1];
		}
	}
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j){
			mat[i][j]=aux[i][j];
		}
	}
}
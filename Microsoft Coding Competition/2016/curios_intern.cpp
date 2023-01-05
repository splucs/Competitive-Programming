#include <cstdio>
#define max(a,b) (a>b?a:b)

int main(){
	int n, mat[60][60], dp[60][60];
	scanf(" %d", &n);
	for(int i=0; i<n; i++){
		for(int j=0; j<=i; j++){
			scanf(" %d", &mat[i][j]);
		}
	}
	for(int i=0; i<n; i++) dp[n-1][i]=mat[n-1][i];
	for(int i=n-2; i>=0; i--){
		for(int j=0; j<=i; j++){
			dp[i][j] = mat[i][j] + max(dp[i+1][j], dp[i+1][j+1]);
		}
	}
	printf("%d", dp[0][0]);
	return 0;
}
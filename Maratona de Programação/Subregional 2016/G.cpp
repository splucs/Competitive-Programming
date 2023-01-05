#include <cstdio>
#include <cstring>
#define MAXN 509

int dp1[MAXN][MAXN], mat1[MAXN][MAXN],
dp2[MAXN][MAXN], mat2[MAXN][MAXN];

int main(){
	int N, P, x, y;
	memset(&mat1, 0, sizeof mat1);
	memset(&mat2, 0, sizeof mat2);
	scanf("%d %d", &N, &P);
	for(int i=0; i<P; i++){
		scanf("%d %d", &x, &y);
		mat1[x][y] = 1;
	}
	for(int i=0; i<P; i++){
		scanf("%d %d", &x, &y);
		mat2[x][y] = 1;
	}
	for(int i=0; i<=N; i++){
		dp1[i][0] = 0;
		dp1[0][i] = 0;
		dp2[i][0] = 0;
		dp2[0][i] = 0;
	}
	for(int i=1; i<=N; i++){
		for(int j=1; j<=N; j++){
			dp1[i][j] = mat1[i][j] + dp1[i-1][j]
			+ dp1[i][j-1] - dp1[i-1][j-1];
			dp2[i][j] = mat2[i][j] + dp2[i-1][j]
			+ dp2[i][j-1] - dp2[i-1][j-1];
		}
	}
	int sum1, sum2, n1 = 0, n2 = 0;
	for(int s=1; s<=N; s++){
		for(int i=s; i<=N; i++){
			for(int j=s; j<=N; j++){
				sum1 = dp1[i][j] - dp1[i-s][j]
				- dp1[i][j-s] + dp1[i-s][j-s];
				sum2 = dp2[i][j] - dp2[i-s][j]
				- dp2[i][j-s] + dp2[i-s][j-s];
				if (sum1 > 0 && sum2 == 0) n1++;
				if (sum2 > 0 && sum1 == 0) n2++;
			}
		}
	}
	printf("%d %d\n", n1, n2);
	return 0;
}

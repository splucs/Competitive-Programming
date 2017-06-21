#include <cstdio>

int main()
{
	int R;
	scanf("%d", &R);

	long long int mat[R+1][3*(R+1)], soma[R+1];
	for(int i=0; i<=R; i++){
		for(int j=0; j<3*(R+1); j++) mat[i][j]=0;
	}
	mat[0][0]=soma[0]=1;
	for(int i=1; i<=R; i++){
		soma[i]=0;
		for(int j=0; j<2*i+1; j++){
			mat[i][j] = mat[i-1][j];
			if(j>0) mat[i][j] += mat[i-1][j-1];
			if(j>1) mat[i][j] += mat[i-1][j-2];
			soma[i]+=mat[i][j];
		}
	}
	printf("%lld\n", soma[R]);
	return 0;
}
#include <cstdio>

int pd[2009][1009], C[1009], V[1009], N;

int PD(int n, int k){
	if (k==N || n<0) return 0;
	if(pd[n][k]>=0) return pd[n][k];
	if(n-C[k]<0){
		pd[n][k]=PD(n, k+1);
		return pd[n][k];
	}
	pd[n][k] = PD(n-C[k], k+1) + V[k];
	int y = PD(n, k+1), z = PD(n-C[k], k) + V[k];
	z = (z>y?z:y);
	pd[n][k] = (pd[n][k]>z?pd[n][k]:z);
	return pd[n][k];
}

int main()
{
	int T;
	scanf("%d %d", &N, &T);
	for(int i=0; i<N; i++){
		scanf("%d %d", C+i, V+i);
		for(int j=0; j<=T; j++){
			pd[j][i]=-1;
		}
	}
	printf("%d\n", PD(T,0));
	return 0;
}
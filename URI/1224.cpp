#include <cstdio>

long long int win[20009][2], lose[20009][2], vet[20009];

long long int max(long long int a, long long int b){
	return (a>b?a:b);
}

long long int min(long long int a, long long int b){
	return (a<b?a:b);
}

int main(){
	int N;
	while(scanf("%d", &N)!=EOF){
		for (int i = 0; i < N; ++i)
		{
			scanf("%lld", vet+i);
			win[i][0]=win[i][1]=0;
			lose[i][0]=lose[i][1]=0;
		}
		win[N][0]=win[N][1]=lose[N][0]=lose[N][1]=0;
		for(int size = 1; size<=N; size++){
			for(int a=0; a+size-1<N; a++){
				win[a][size%2] = max(vet[a]+lose[a+1][(size%2+1)%2], vet[a+size-1]+lose[a][(size%2+1)%2]);
				lose[a][size%2] = min(win[a+1][(size%2+1)%2], win[a][(size%2+1)%2]);
			}
		}
		printf("%lld\n", win[0][N%2]);
	}
	return 0;
}


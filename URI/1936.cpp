#include <cstdio>

int main()
{
	int fat[10], N, res=0, k=9;
	fat[0]=1;
	for(int i=1; i<10; i++){
		fat[i]=i*fat[i-1];
	}
	scanf("%d", &N);
	while(N>0){
		while(fat[k]>N) k--;
		while(N>=fat[k]){
			N-=fat[k];
			res++;
		}
	}
	printf("%d\n", res);
	return 0;
}
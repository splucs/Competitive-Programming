#include <cstdio>

int N, vet[100009], sum[100009];

int update(int pos, int valor){
	while(pos<=N){
		sum[pos]+=valor;
		pos+=(pos & -pos);
	}
}

int read(int pos){
	int res=0;
	while(pos>0){
		res+=sum[pos];
		pos-=(pos & -pos);
	}
	return res;
}

int main()
{
	scanf("%d", &N);
	for(int i=1; i<=N; i++){
		scanf("%d", vet+i);
		sum[i]=0;
	}
	for(int i=1; i<=N; i++){
		update(i,vet[i]);
	}
	char c;
	int x;
	while(scanf(" %c %d", &c, &x)!=EOF){
		if(c=='a') {
			update(x, -vet[x]);
			vet[x]=0;
		}
		else{
			printf("%d\n", read(x-1));
		}
	}
	return 0;
}
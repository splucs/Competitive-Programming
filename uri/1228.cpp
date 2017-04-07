#include <cstdio>

int main()
{
	int N, ini[29], fim[29], pos[29], res, aux, x, y;
	while(scanf("%d", &N)!=EOF){
		for(int i=0; i<N; i++){
			scanf("%d", ini+i);
			pos[ini[i]]=i;
		}
		for(int i=0; i<N; i++){
			scanf("%d", fim+i);
		}
		res=0;
		for(int i=0; i<N; i++){
			while(ini[i]!=fim[i]){
				x = pos[fim[i]];
				y = x-1;
				aux=ini[x];
				ini[x]=ini[y];
				ini[y]=aux;
				pos[ini[x]]=x;
				pos[ini[y]]=y;
				res++;
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
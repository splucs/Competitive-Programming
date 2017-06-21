#include <cstdio>
#include <queue>
using namespace std;

int pd[1000002];

int main()
{
	int O, D, K, x;
	while(true){
		queue<int> fila;
		scanf("%d %d %d", &O, &D, &K);
		if (O==0 && D==0 && K==0) break;
		for (int i=1; i<100001; i++) pd[i]=-1;
		for (int i=100001; i<1000001; i++) pd[i]=-2;
		for (int i=0; i<K; i++){
			scanf("%d", &x);
			pd[x]=-2;
		}
		if (pd[O]==-2){
			printf("-1\n");
			continue;
		}
		pd[O]=0;
		fila.push(O);
		while(!fila.empty() && pd[D]==-1){
			x = fila.front();
			fila.pop();
			if (x+1<1000001 && pd[x+1]==-1){
				pd[x+1]=pd[x]+1;
				fila.push(x+1);
			}
			if (x-1>0 && pd[x-1]==-1){
				pd[x-1]=pd[x]+1;
				fila.push(x-1);
			}
			if (2*x < 1000001 && pd[2*x]==-1 ){
				pd[2*x]=pd[x]+1;
				fila.push(2*x);
			}
			if (3*x < 1000001 && pd[3*x]==-1){
				pd[3*x]=pd[x]+1;
				fila.push(3*x);
			}
			if (x/2 >0 && x%2==0 && pd[x/2]==-1){
				pd[x/2]=pd[x]+1;
				fila.push(x/2);
			}
		}
		if (pd[D]==-2) pd[D]=-1;
		printf("%d\n", pd[D]);
	}
	return 0;
}
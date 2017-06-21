#include <cstdio>
#include <cstring>

typedef struct score{
	int size;
	int esp;
}score;

score pd[2009][2009];
bool special[2009];
char vet[2009];

score PD(int a, int b){
	if(pd[a][b].esp>=0) return pd[a][b];
	score x;
	if(a==b){
		pd[a][b].size=1;
		pd[a][b].esp = special[a];
		return pd[a][b];
	}
	if(a==b+1){
		pd[a][b].size=0;
		pd[a][b].esp = false;
		return pd[a][b];
	}
	pd[a][b] = PD(a+1,b);
	x = PD(a,b-1);
	if(x.esp>pd[a][b].esp) pd[a][b]=x;
	if(x.esp==pd[a][b].esp && x.size>pd[a][b].size) pd[a][b]=x;
	if(vet[a]==vet[b]){
		x = PD(a+1,b-1);
		x.size+=2;
		if(special[a]) x.esp++;
		if(special[b]) x.esp++;
	}
	if(x.esp>pd[a][b].esp) pd[a][b]=x;
	if(x.esp==pd[a][b].esp && x.size>pd[a][b].size) pd[a][b]=x;
	return pd[a][b];
}

int main()
{
	scanf(" %s ", vet);
	int L = strlen(vet), N, x;
	for(int i=0; i<L; i++){
		special[i]=false;
		for(int j=0; j<L; j++){
			pd[i][j].esp=-1;
		}
	}
	scanf("%d", &N);
	for(int i=0; i<N; i++){
		scanf("%d", &x);
		special[x-1]=true;
	}
	printf("%d\n", PD(0,L-1).size);
	return 0;
}
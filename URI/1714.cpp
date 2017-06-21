#include <cstdio>
#include <queue>
using namespace std;

int vet[10];
bool isvalid(char c){
	if(c>='a' && c<='z'){
		if(vet[c-'a']==1) return false;
		else return true;
	}
	else{
		if(vet[c-'A']==1) return true;
		else return false;
	}
}

int main()
{
	queue<int> filax, filay;
	int N, aux, dist[109][109], mindist=-1, x, y;
	char field[109][109];
	scanf("%d", &N);
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			scanf(" %c", &field[i][j]);
		}
	}
	for(int pos=0; pos<1024; pos++){
		aux=pos;
		for(int i=0; i<10; i++){
			vet[i]=aux%2;
			aux/=2;
		}
		if(!isvalid(field[0][0])) continue;
		for(int i=0; i<N; i++){
			for(int j=0; j<N; j++){
				dist[i][j]=-1;
			}
		}
		filax.push(0);
		filay.push(0);
		dist[0][0]=1;
		while(!filax.empty()){
			x = filax.front();
			filax.pop();
			y = filay.front();
			filay.pop();
			if(x>0 && dist[x-1][y]<0 && isvalid(field[x-1][y])){
				dist[x-1][y]=dist[x][y]+1;
				filax.push(x-1);
				filay.push(y);
			}
			if(x+1<N && dist[x+1][y]<0 && isvalid(field[x+1][y])){
				dist[x+1][y]=dist[x][y]+1;
				filax.push(x+1);
				filay.push(y);
				if(x+1==N-1 && y==N-1) break;
			}
			if(y>0 && dist[x][y-1]<0 && isvalid(field[x][y-1])){
				dist[x][y-1]=dist[x][y]+1;
				filax.push(x);
				filay.push(y-1);
			}
			if(y+1<N && dist[x][y+1]<0 && isvalid(field[x][y+1])){
				dist[x][y+1]=dist[x][y]+1;
				filax.push(x);
				filay.push(y+1);
				if(x==N-1 && y+1==N-1) break;
			}
		}
		while(!filax.empty()){
			filax.pop();
			filay.pop();
		}
		if(dist[N-1][N-1]>=0 && (mindist>dist[N-1][N-1] || mindist<0)) mindist=dist[N-1][N-1];
	}
	printf("%d\n", mindist);
	return 0;
}
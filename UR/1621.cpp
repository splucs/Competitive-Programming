#include <cstdio>

int N, M, maxDist;
char carac[509][509];
bool visited[509][509];

int dfs(int x, int y, int h){
	visited[x][y]=true;
	if (carac[x][y]=='#') return 0;
	int first=0, second=0, aux;
	if(x>0 && !visited[x-1][y]){
		aux = dfs(x-1,y,h+1);
		if(aux>=first){
			second=first;
			first=aux;
		}
		else if(aux>second){
			second = aux;
		}
	}
	if(y>0 && !visited[x][y-1]){
		aux = dfs(x,y-1,h+1);
		if(aux>=first){
			second=first;
			first=aux;
		}
		else if(aux>second){
			second = aux;
		}
	}
	if(x<N-1 && !visited[x+1][y]){
		aux = dfs(x+1,y,h+1);
		if(aux>=first){
			second=first;
			first=aux;
		}
		else if(aux>second){
			second = aux;
		}
	}
	if(y<M-1 && !visited[x][y+1]){
		aux = dfs(x,y+1,h+1);
		if(aux>=first){
			second=first;
			first=aux;
		}
		else if(aux>second){
			second = aux;
		}
	}
	maxDist = (maxDist>h+first+1?maxDist:h+first+1);
	maxDist = (maxDist>second+first+1?maxDist:second+first+1);
	return first+1;
}

int main()
{
	while(true){
		scanf("%d %d", &N, &M);
		if(N==0 && M==0) break;
		for(int i=0; i<N; i++){
			for(int j=0; j<M; j++){
				scanf(" %c", &carac[i][j]);
				visited[i][j]=false;
			}
		}
		maxDist=0;
		for(int i=0; i<N; i++){
			for(int j=0; j<M; j++){
				if(!visited[i][j]) dfs(i,j,0);
			}
		}
		printf("%d\n", maxDist-1);
	}
	return 0;
}
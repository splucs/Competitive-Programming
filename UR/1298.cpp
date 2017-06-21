#include <cstdio>

bool dir[609][609], esq[609][609], cima[609][609], baixo[609][609];
bool visited[609][609];
int N;

void dfs(int i, int j){
	visited[i][j]=true;
	if(i>1 && !visited[i-1][j] && cima[i][j]) dfs(i-1,j);
	if(i<2*N && !visited[i+1][j] && baixo[i][j]) dfs(i+1,j);
	if(j>1 && !visited[i][j-1] && esq[i][j]) dfs(i,j-1);
	if(j<2*N+1 && !visited[i][j+1] && dir[i][j]) dfs(i,j+1);
}

int main()
{
	int x, y, res;
	char c;
	while(scanf("%d", &N)!=EOF){
		for(int i=1; i<=2*N; i++){
			for(int j=1; j<=2*N+1; j++){
				dir[i][j]=(j<2*N+1);
				esq[i][j]=(j>1);
				cima[i][j]=(i>1);
				baixo[i][j]=(i<2*N);
				visited[i][j]=false;
			}
		}
		for(int i=1; i<=2*N-1; i++){
			for(int j=1; j<=N; j++){
				scanf(" %c", &c);
				x=i;
				if(i%2==0) y=2*j;
				else y=2*j-1;
				dir[x][y]=dir[x+1][y]=esq[x][y+1]=esq[x+1][y+1]=(c=='H');
				cima[x+1][y]=cima[x+1][y+1]=baixo[x][y]=baixo[x][y+1]=(c=='V');
			}
		}
		res=-1;
		for(int i=1; i<=2*N; i++){
			for(int j=1; j<=2*N+1; j++){
				if(visited[i][j]) continue;
				res++;
				dfs(i,j);
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
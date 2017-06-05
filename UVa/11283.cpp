#include <cstdio>
#include <cstring>

char table[5][5], str[20];
bool visited[5][5];
int len;

bool dfs(int n, int x, int y){
	if (n==len) return true;
	if (x<0 || y<0 || x>3 || y>3 || visited[x][y] || str[n]!=table[x][y]) return false;
	visited[x][y]=true;
	bool found = false;
	if(!found && dfs(n+1, x+1, y)) found = true;
	if(!found && dfs(n+1, x-1, y)) found = true;
	if(!found && dfs(n+1, x, y+1)) found = true;
	if(!found && dfs(n+1, x, y-1)) found = true;
	if(!found && dfs(n+1, x+1, y+1)) found = true;
	if(!found && dfs(n+1, x+1, y-1)) found = true;
	if(!found && dfs(n+1, x-1, y+1)) found = true;
	if(!found && dfs(n+1, x-1, y-1)) found = true;
	visited[x][y]=false;
	return found;
}

int main(){
	int N, M, res;
	bool found;
	scanf("%d", &N);
	for(int caseNo=1; caseNo<=N; caseNo++){
		for(int i=0; i<4; i++){
			for(int j=0; j<4; j++){
				scanf(" %c", &table[i][j]);
				visited[i][j]=false;
			}
		}
		res=0;
		scanf("%d", &M);
		while(M-->0){
			scanf(" %s", str);
			found = false;
			len = strlen(str);
			for(int i=0; i<4 && !found; i++){
				for(int j=0; j<4 && !found; j++){
					found = dfs(0, i, j);
				}
			}
			if (found){
				if (len==3 || len==4) res+=1;
				else if (len==5) res+=2;
				else if (len==6) res+=3;
				else if (len==7) res+=5;
				else if (len>7) res+=11;
			}
		}
		printf("Score for Boggle game #%d: %d\n", caseNo, res);
	}
	return 0;
}
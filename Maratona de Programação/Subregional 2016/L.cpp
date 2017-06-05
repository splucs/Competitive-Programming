#include <cstdio>
#include <algorithm>

using namespace std;

int m[201][201];
bool visited[201][201]={};
int movx[4] = {0,1,-1,0};
int movy[4] = {1,0,0,-1};
int h,l;

int recurs(int x,int y,int val){
	visited[x][y] = true;
	int nx,ny,ans=1;
	for (int i=0;i<4;i++){
		nx = x+movx[i];
		ny = y+movy[i];
		if (nx>=0&&nx<h&&ny>=0&&ny<l&&m[nx][ny]==val
		&&!visited[nx][ny]){
			ans += recurs(nx,ny,val);
		}
	}
	return ans;
}

int main(){
	int ans;
	scanf("%d%d",&h,&l);
	for (int i=0;i<h;i++){
		for(int j=0;j<l;j++){
			scanf("%d",&m[i][j]);
		}
	}
	ans = 1000000000;
	for (int i=0;i<h;i++){
		for (int j=0;j<l;j++){
			if (!visited[i][j])ans = min(recurs(i,j,m[i][j]),ans);
		}
	}printf("%d\n",ans);
	return 0;
}

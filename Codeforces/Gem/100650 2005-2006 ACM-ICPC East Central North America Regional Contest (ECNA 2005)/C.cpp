#include <bits/stdc++.h>
using namespace std;

int mp[16][16]={};
int ans,n,m;
int grid[16][16];
int movx[8] = {1,1,1,-1,-1,-1,0,0};
int movy[8] = {0,1,-1,0,1,-1,1,-1};

int modx(int x){
	if (x<0)return n-1;
	return x%n;
}

int mody(int y){
	if (y<0)return m-1;
	return y%m;
}

void calculate(){
	int qtt,res;
	/*for (int i=0;i<n;i++){
		for (int j=0;j<m;j++){
			printf("%d",grid[i][j]);
		}
		printf("\n");
	}*/
	
	for (int i=0;i<n;i++){
		for (int j=0;j<m;j++){
			res = grid[i][j];
			qtt = 0;
			for (int k=0;k<8;k++){
				qtt+=grid[modx(i+movx[k])][mody(j+movy[k])];
			}
			if (grid[i][j]==1&&(qtt<=1||qtt>=4))res = 0;
			else if (qtt==3)res=1;
			if (res!=mp[i][j])return;
		}
	}
	ans++;
	
}

void generate(int i,int j){
	if (i==n){
		calculate();
		return;
	}grid[i][j] =0 ;
	generate(i+(j+1)/m,(j+1)%m);
	grid[i][j] =1;
	generate(i+(j+1)/m,(j+1)%m);
}

int main(){
	int k,x,y,t=1;
	while(cin>>n>>m &&n!=0){
		cin>>k;
		ans=0;
		for (int i=0;i<n;i++)for(int j=0;j<m;j++)mp[i][j]=0;
		for (int i=0;i<k;i++){
			cin>>x>>y;
			mp[x][y] = 1;
		}
		generate(0,0);
		if (ans==0)printf("Case %d: Garden of Eden.\n",t++);
		else printf("Case %d: %d possible ancestors.\n",t++,ans);
	}
}
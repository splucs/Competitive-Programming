#include <bits/stdc++.h>
using namespace std;

int movx[8] = {1,1,1,-1,-1,-1,0,0};
int movy[8] = {0,1,-1,0,1,-1,1,-1};
char mp[11][11];
int n;

int numAdj(int posx,int posy){
	int ans = 0,x,y;
	if (mp[posx][posy]=='*')return -1;
	for (int i=0;i<8;i++){
		x = movx[i]+posx, y = movy[i]+posy;
		//cout<<x<<" "<<y<<endl;
		if (x>=0&&y>=0&&x<n&&y<n&&mp[x][y]=='*')ans++;
	}
	return ans;
}

int main(){
	int val;
	char sol[11][11];
	bool mined = false;
	cin>>n;
	for (int i=0;i<n;i++){
		cin>>mp[i];
	}for (int i=0;i<n;i++){
		cin>>sol[i];
		for (int j=0;j<n;j++){
			if (sol[i][j]=='x'){
				val = numAdj(i,j);
				if (val==-1)mined = true;
				else sol[i][j] = val+'0';
			}
		}
	}
	if (mined){
		for (int i=0;i<n;i++){
			for (int j=0;j<n;j++)if (mp[i][j]=='*')sol[i][j]='*';
			cout<<sol[i]<<endl;
		}
	}else{
		for (int i=0;i<n;i++){
			cout<<sol[i]<<endl;
		}
	}
}
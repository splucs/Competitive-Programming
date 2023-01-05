#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;

ii p[2];
char d[2];
char arr[4] = {'N','E','S','O'};
vector<int> ans;
int dir;

int getDir(char c){
	if (c=='N')return 0;
	if (c=='E')return 1;
	if (c=='S')return 2;
	return 3;
}

void solve(int idx){
	int a = p[idx].first, b = p[idx].second;
	if (a==b)return;
	
	while (arr[dir]!=d[idx]){
		ans.push_back(-1);
		dir = (dir+1)%4;
	}
	ans.push_back(abs(b-a));
}

int main(){
	int x0,y0,x1,y1;
	char c;
	int dir1,dir2;
	int first;
	
	cin>>y0>>x0>>c>>y1>>x1;
	p[0] = ii(x0,x1);
	p[1] = ii(y0,y1);
	dir1 = x1>x0?1:(x1==x0?0:-1);
	dir2 = y1>y0?1:(y1==y0?0:-1);
	
	d[0] = dir1>0?'N':'S';
	d[1] = dir2>0?'E':'O';
	
	if (dir1==0)first = 0;
	else if (dir2==0)first = 1;
	else{
		if (c=='N')first = dir1>0?0:(dir2<0?0:1);
		else if (c=='E')first = dir2>0?1:(dir1>0?1:0);
		else if (c=='S')first = dir1<0?0:(dir2>0?0:1);
		else if (c=='O')first = dir2<0?1:(dir1<0?1:0);
	}
	dir = getDir(c);
	solve(first);
	solve((first+1)%2);
	cout<<ans.size()<<endl;
	for (int i=0;i<(int)ans.size();i++){
		if (ans[i]==-1)cout<<'D'<<endl;
		else cout<<"A "<<ans[i]<<endl;
	}
	return 0;
}
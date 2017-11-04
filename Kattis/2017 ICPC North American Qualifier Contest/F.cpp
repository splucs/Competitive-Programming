#include <bits/stdc++.h>
using namespace std;
#define MAXN 59

string names[3] = {"Forward","Right","Left"};
int instr[MAXN];
int x,y,n;

bool solve(){
	int x0 = 0,y0 = 0,dir = 0;
	for (int i=0;i<n;i++){
		if (instr[i]==0){
			if (dir==0)y0++;
			else if (dir==1)x0++;
			else if (dir==2)y0--;
			else if (dir==3)x0--;
		}
		else if (instr[i]==1)dir = (dir+1)%4;
		else dir = (dir+3)%4;
	}
	return x0==x&&y0==y;
}

int main(){
	string s;
	bool solved = false;
	cin>>x>>y>>n;
	for (int i=0;i<n;i++){
		cin>>s;
		if (s=="Forward")instr[i] = 0;
		else if (s=="Right")instr[i] = 1;
		else if (s=="Left")instr[i] = 2;
	}
	for (int i=0;i<n&&!solved;i++){
		int aux = instr[i];
		for (int j=0;j<3&&!solved;j++){
			if (aux==j)continue;
			instr[i] = j;
			if (solve()){
				cout<<i+1<<" "<<names[j]<<endl;
				solved = true;
			}
			instr[i] = aux;
		}
	}
}
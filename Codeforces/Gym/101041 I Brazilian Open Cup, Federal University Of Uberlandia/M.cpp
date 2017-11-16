#include <bits/stdc++.h>
using namespace std;

vector<char> num;
vector<string> val;
vector<bool> used;

int n;

void recurse(int index,string acum){
	if (index==n){
		val.push_back(acum);
		return;
	}
	for (int i=0;i<n;i++){
		if (!used[i]){
			acum.push_back(num[i]);
			used[i]= true;
			recurse(index+1,acum);
			acum.pop_back();
			used[i]= false;
		}
	}
}

int main(){
	char a;
	cin>>n;
	for (int i=0;i<n;i++){
		cin>>a;
		num.push_back(a);
	}
	used.assign(n,false);
	recurse(0,"");
	sort(val.begin(),val.end());
	for (int i=0;i<val.size();i++){
		if (i>0&&val[i]==val[i-1])continue;
		cout<<val[i]<<endl;
	}
}
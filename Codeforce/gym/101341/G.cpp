#include <bits/stdc++.h>
using namespace std;

int love[200000],cnt[200000];
string names[200000];

int main(){
	int n,q,a,b;
	cin>>n;
	for (int i=0;i<n;i++){
		cin>>names[i];
		love[i] = i;
		cnt[i] = 0;
	}
	cin>>q;
	for (int i=0;i<q;i++){
		cin>>a>>b;
		a--,b--;
		cnt[a] = cnt[b]+1;
		love[a] = love[b];
	}
	string ans = "";
	for (int i=0;i<cnt[0];i++)ans+="I_love_";
	ans+=names[love[0]];
	cout<<ans<<endl;
}
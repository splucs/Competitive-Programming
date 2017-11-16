#include <bits/stdc++.h>
using namespace std;

int main(){
	int n;
	cin>>n;
	string s;
	map<string,int> qtt;
	int ans = 0;
	for (int i=0;i<n;i++){cin>>s;qtt[s]++;}
	for (int i=0;i<n;i++){
		cin>>s;
		if (qtt[s]>0){ans++;qtt[s]--;}
	}
	cout<<ans<<endl;
}
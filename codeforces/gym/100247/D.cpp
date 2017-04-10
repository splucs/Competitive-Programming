#include <bits/stdc++.h>
using namespace std;

int main(){
	int n;
	char car;
	string ans = "",a,b,c; 
	cin>>n>>a>>b>>c;
	for (int i=0;i<n;i++){
		if (b[i]==c[i])car = b[i];
		else car = a[i];
		ans.push_back(car);
	}
	cout<<ans<<endl;
}
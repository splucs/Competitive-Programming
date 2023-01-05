#include <bits/stdc++.h>

using namespace std;

int main(){
	int a, b, c, m, n;
	cin>>a>>b>>c>>m>>n;
	a+=c;
	b+=c;
	int ans;
	if(m>=a){
		if(n>=b){
			ans = a+b-c;
		}else{
			ans = n;
		}
	}else{
		if(n>=b){
			ans = m;
		}else{
			ans = min(n, m);
		}	
	}
	cout<<ans<<endl;
}
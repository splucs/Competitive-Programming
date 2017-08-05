#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

int main(){
	map<ll,int> qtt;
	ll ans=0,n,s,d,acum = 0;
	
	cin>>n>>s;
	qtt[s]++;
	for (int i=0;i<n;i++){
		cin>>d;
		acum+=d;
		ans+=qtt[acum];
		qtt[acum+s]++;
	}
	cout<<ans<<endl;
}
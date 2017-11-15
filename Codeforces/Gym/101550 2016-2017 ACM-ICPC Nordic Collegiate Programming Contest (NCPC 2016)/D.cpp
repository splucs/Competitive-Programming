#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
	int d,p[400],i;
	ll qtt;
	
	cin>>d;
	for (i=0;i<d;i++){
		cin>>p[i];
	}
	ll s = 100;
	i = 0;
	while (i<d-1){
		while (i<d-1 && p[i+1]<=p[i]) i++;
		qtt = min((ll)100000, s/p[i]);
		s-=qtt*p[i];
		while (i<d-1 &&p[i+1]>=p[i])i++;
		s+=qtt*p[i];
	}
	cout<<s<<endl;
}
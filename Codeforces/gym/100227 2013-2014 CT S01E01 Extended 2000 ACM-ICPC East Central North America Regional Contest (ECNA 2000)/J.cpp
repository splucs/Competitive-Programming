#include <bits/stdc++.h>
using namespace std;

int main(){
	long long int n,k,ans;
	while (cin>>n>>k){
		ans = n;
		while (n>=k){
			ans+=n/k;
			n = n%k+n/k;
		}
		cout<<ans<<endl;
	}
}
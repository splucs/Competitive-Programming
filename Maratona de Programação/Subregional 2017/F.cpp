#include <bits/stdc++.h>
using namespace std;

int main(){
	int n,k,a[1009],ans,p;
	cin>>n>>k;
	for (int i=0;i<n;i++){
		cin>>a[i];
	}
	sort(a,a+n);
	p = a[n-k];
	ans = k;
	for (int i=n-k-1;i>=0;i--){
		if (a[i]!=p)break;
		ans++;
	}cout<<ans<<endl;
}

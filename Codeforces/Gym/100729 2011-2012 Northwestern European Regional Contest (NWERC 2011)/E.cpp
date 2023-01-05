#include <bits/stdc++.h>
using namespace std;
#define MAXN 256

int main(){
	int t,n, last[MAXN], qtt[MAXN];
	string str;
	
	cin>>t;
	while (t-->0){
		cin>>n;
		memset(last,-1,sizeof(last));
		memset(qtt,0,sizeof(qtt));
		cin>>str;
		for (int i=str.size()-1;i>=0;i--){
			char u = str[i];
			if (last[u]==-1){
				last[u] = i;
			}
			qtt[u]++;
		}int ans,acum;
		ans = acum = 0;
		for (int i=0;i<str.size();i++){
			char u = str[i];
			if (last[u]==i){
				ans+=(i-acum-qtt[u]+1)*qtt[u];
				acum+=qtt[u];
			}
		}cout<<ans*5<<endl;
	}
}
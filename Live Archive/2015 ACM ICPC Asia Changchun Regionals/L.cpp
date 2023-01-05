#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define MAXN 109

int c[MAXN][MAXN];

int main(){
	int t,n,m;
	ll ans;
	cin>>t;
	while (t-->0){
		cin>>n>>m;
		ans = 0;
		memset(c,0,sizeof(c));
		for (int i=1;i<=n+1;i++){
			for (int j=1;j<=m+1;j++){
				if (i<=n&&j<=m)cin>>c[i][j];
				if (c[i][j]>0)ans++;
				ans+=abs(c[i][j]-c[i][j-1]);
				ans+=abs(c[i][j]-c[i-1][j]);
			}
		}
		cout<<ans<<endl;
	}
}
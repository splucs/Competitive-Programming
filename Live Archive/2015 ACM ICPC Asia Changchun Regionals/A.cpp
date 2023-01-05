#include <bits/stdc++.h>
using namespace std;
#define MAXN 10
typedef long long int ll;

ll val[MAXN] = {1,5,10,20,50,100,200,500,1000,2000};
ll multiple[2][MAXN] = {{5,10,20,100,100,200,1000,1000,2000,2000},
						{0,0,50,0,0,500,0,0,0,0}};
ll num[MAXN];
bool found;					


ll verify(int i,ll p){
	if (p==0){found = true;return 0;}
	if (i==MAXN)return 0;
	
	ll ans = -1;
	for (int j=0;j<2;j++){
		ll mult = multiple[j][i];
		if (mult==0)continue;
		ll n = p - val[i]*num[i];
		cout<<p<<" "<<n<<endl;
		if (n<=0){ans = max(ans,p/val[i]),found = true;}
		else if (n%mult==0)ans = max(ans,num[i]+verify(i+1,n));
		else{
			n = min(p,(n/mult+1)*mult);
			ans = max(ans,(p-n)/val[i]+verify(i+1,n));
		}
	}
	return ans;
}
					
int main(){
	int T,p;
	cin>>T;
	while (T-->0){
		cin>>p;
		found = false;
		for (int i=0;i<MAXN;i++)cin>>num[i];
		ll ans = verify(0,p);
		if (found)cout<<ans<<endl;
		else cout<<-1<<endl;
	}
}
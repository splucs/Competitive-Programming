#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000009
#define INF 1000000007
typedef long long int ll;

int main() {
	int t,a,n;
	ll odd,even,aux;
	
	freopen("azerah.in","r",stdin);
	freopen("azerah.out","w",stdout);
	
	cin>>t;
	
	while (t-->0)
	{
		cin>>n;
		odd = even = 0;
		for (int i=0;i<n;i++){
			cin>>a;
			if (a%2==0){
				even = (even*2+1)%INF; 
				odd = (odd*2)%INF;
			}
			else {
				aux = even;
				even = (odd+even)%INF;
				odd = (aux+odd+1)%INF;
			}
		}
		cout<<even<<endl;
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
#define MAXN 4909

ull INF;
map<int,int> prime;
int value[MAXN];
bool poss[MAXN];
ull pd[140][1<<20];
int K;

void crive(){
	bool isPrime[70] = {};
	int cnt = 0;
	for (int i=2;i<70;i++){
		if (isPrime[i])continue;
		prime[i] = cnt++;
		for (int j=i*i;j<70;j=j+i){
			isPrime[j] = true;
		}
	}
}

ull solve(int a,int mask,int b,bool c){
	if (a==b+1)return (mask==0&&c)?1:INF;
	
	//cout<<a<<" "<<mask<<endl;
	
	int u = K+a;
	if (pd[u][mask]!=-1)return pd[u][mask];
	
	ull ans = solve(a+1,mask,b,c);
	if (poss[a]){
		ull v = solve(a+1,mask^value[a],b,true);
		if (INF/v>a)ans = min(ans,v*a);
	}
	return pd[u][mask] = ans;
}

int main(){
	INF = 1;
	INF <<= 63;
	
	int a,b,n;
	
	crive();
	for (int i=1;i<=MAXN;i++){
		n = i;
		poss[i] = true;
		value[i] = 0;
		for (int j=2;j<=sqrt(i);j++){
			while (n%j==0)value[i]^=(1<<prime[j]), n/=j;
		}
		//cout<<i<<" "<<value[i]<<endl;
		if (n!=1 && !prime.count(i))poss[i] = false;
	}
	ull ans;
	while (scanf("%d%d",&a,&b)!=EOF){
		ans = INF;
		memset(pd,-1,sizeof(pd));
		for (int i=a;i<=b;i++){
			n = sqrt(i);
			if (n*n==i){
				ans = n;
				b = i-1;
				break;
			}
		}
		K = -a;
		//cout<<ans<<endl;
		ans = min(ans,solve(a,0,b,false));
		if (ans<INF)cout<<ans<<endl;
		else printf("none\n");
	}
}
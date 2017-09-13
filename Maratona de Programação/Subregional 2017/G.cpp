#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000000007
typedef long long int ll;

int N,M,T;
ll dp[2][100009];

int main(){
	cin>>T>>M>>N;
	ll ans = 0;
	for (int i=M;i<=N;i++)dp[0][i] = dp[1][i] = 1;
	for (int i=1;i<T;i++){
		for (int j=M;j<=N;j++)
			dp[(i+1)%2][j] = ((j>M?dp[i%2][j-1]:0)+(j<N?dp[i%2][j+1]:0))%MAXN;
	}for (int j=M;j<=N;j++){
		ans=(ans+dp[T%2][j])%MAXN;
	}cout<<ans<<endl;
}

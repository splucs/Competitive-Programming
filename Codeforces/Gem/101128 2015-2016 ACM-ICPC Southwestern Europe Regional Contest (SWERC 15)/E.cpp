#include <bits/stdc++.h>
using namespace std;
#define WMAX 2147483647
typedef long long int lld;

int perm[2001],N;
lld dp[2010][2010];

lld getans(int index,int outer){
	if (index>N)return 1;
	if (dp[index][outer]!=-1)return dp[index][outer];
	
	int left = min(outer,perm[index-1]);
	int right = max(outer,perm[index-1]);
	
	lld ans = 0;
	if (left<perm[index])ans+=getans(index+1,left);
	if (right>perm[index])ans+=getans(index+1,right);
	
	return dp[index][outer] = ans%WMAX;
}

int main(){
	scanf("%d",&N);
	for (int i=0;i<=N;i++){
		scanf("%d",&perm[i]);
	}for (int i=0;i<=N;i++)for (int j=0;j<=N+1;j++)dp[i][j]=-1;
	printf("%I64d\n",getans(2,perm[0]));
}
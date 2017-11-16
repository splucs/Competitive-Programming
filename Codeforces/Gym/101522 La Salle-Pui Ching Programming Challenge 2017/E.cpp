#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
typedef long long int ll;

int main(){
	int N,R,x,y,u,v;
	ll score,K;
	int arr[MAXN];
	bool used[MAXN];
	double ans,p;

	scanf("%d%d",&N,&R);
	K = 2*N;
	memset(arr,0,sizeof(arr));
	memset(arr,false,sizeof(arr));
	score = 0;

	for (int i=0;i<R-1;i++){
		scanf("%d%d%d%d",&x,&y,&u,&v);
		if (!used[x])arr[u]++,K--;
		if (!used[y])arr[v]++,K--;
		if (x!=y&&u==v)score = max(score,(ll)u);
		used[x] = used[y] = true;
	}
	if (K<=1){
		printf("%d\n",N);
		return 0;
	}
	ans = score;
	double s;
	ll cnt,qtt,den;
	cnt = qtt = 0;
	p = 0;
	//cout<<prob1<<" "<<prob2<<endl;
	for (ll i=score+1;i<=N;i++){
		if (arr[i]==2)s = i;
		else if (arr[i]==1)s = (double)(i+(K-1)*score)/K;
		else cnt+=i, qtt++;
		ans = max(ans,s);
	}
	//cout<<cnt<<" "<<prob1<<" "<<prob2<<endl;
	ans = max(ans,(double)(cnt*2+(K*(K-1)-qtt*2)*score)/(K*(K-1)));
	printf("%.10lf\n",ans);
	return 0;
}
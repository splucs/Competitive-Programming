#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
typedef pair<int,int> ii;

int n,k;
ii qtt[MAXN]={};

bool isValid(){
	int q = qtt[1].first;
	for (int i=2;i<=k;i++)if (qtt[i].first!=q)return false;
	return true;
}

int main(){
	int a,ans1,ans2;
	
	scanf("%d%d",&k,&n);
	bool poss = true;
	for (int i=0;i<n;i++){
		scanf("%d",&a);
		qtt[a] = ii(qtt[a].first+1,a);
	}
	sort(qtt+1,qtt+k+1);
	
	ans1 = ans2 = -1;
	int u = n/k;
	if (n==k*u){
		if (!isValid()){
			ans1 = qtt[1].second, ans2 = qtt[k].second;
			qtt[1] = ii(qtt[1].first+1,1);
			qtt[k] = ii(qtt[k].first-1,k);
			poss = isValid();
		}
	}else if (n==k*u+1){
		ans2 = qtt[k].second;
		qtt[k] = ii(qtt[k].first-1,k);
		poss = isValid();
	}else if (n==k*(u+1)-1){
		ans1 = qtt[1].second;
		qtt[1] = ii(qtt[1].first+1,k);
		poss = isValid();
	}else poss = false;
	
	if (!poss)printf("*\n");
	else {
		if (ans1!=-1&&ans2!=-1)printf("-%d +%d\n",ans2,ans1);
		else if (ans1!=-1)printf("+%d\n",ans1);
		else if (ans2!=-1)printf("-%d\n",ans2);
	}
	
}

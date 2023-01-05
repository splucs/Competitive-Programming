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
	int a;
	
	scanf("%d%d",&k,&n);
	for (int i=0;i<n;i++){
		scanf("%d",&a);
		qtt[a] = ii(qtt[a].first+1,a);
	}
	sort(qtt+1,qtt+k+1);
	
	
	qtt[1] = ii(qtt[1].first+1,qtt[1].second);
	qtt[k] = ii(qtt[k].first-1,qtt[k].second);
	if (isValid()){
		printf("-%d +%d\n",qtt[k].second,qtt[1].second);
		return 0;
	}
	qtt[1] = ii(qtt[1].first-1,qtt[1].second);
	if (isValid()){
		printf("-%d\n",qtt[k].second);
		return 0;
	}
	qtt[1] = ii(qtt[1].first+1,qtt[1].second);
	qtt[k] = ii(qtt[k].first+1,qtt[k].second);
		
	if (isValid()){
		printf("+%d\n",qtt[1].second);
		return 0;
	}
	printf("*\n");
	return 0;
}

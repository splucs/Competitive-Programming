#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;

int main(){
	int n,m,k,val;
	vector<ii> sum;
	scanf("%d%d",&n,&m);
	sum.resize(n+m+1);
	for (int i=1;i<=n+m;i++)sum[i] = ii(0,-i);
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++){
			k = i+j;
			sum[k] = ii(sum[k].first+1,-k);
		}
	}
	k = n+m;
	sort(sum.begin(),sum.end());
	val = sum[k].first;
	while (k>=1&&val==sum[k].first){
		printf("%d\n",-sum[k].second);
		k--;
	}
}
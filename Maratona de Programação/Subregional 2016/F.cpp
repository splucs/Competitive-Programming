
#include <cstdio>
#include <algorithm>
using namespace std;

int c[10001],s[10001];
int best;

void recurs(int v,int qtt){
	int ans=1;
	if (c[v]!=0)recurs(c[v],1);
	if (s[v]!=0)recurs(s[v],qtt+1);
	best = max(qtt,best);
	//printf("%d %d\n",v,qtt);
}

int main(){
	int n[2],v,a[2],ans=1000000000,p[2]={},val[2];
	for (int j=0;j<2;j++){
		scanf("%d",&n[j]);
		for (int i=0;i<n[j];i++){
			scanf("%d%d%d",&v,&a[j],&a[(j+1)%2]);
			c[v]=a[0],s[v]=a[1];
		}
		int k=1;
		while (k!=0){
			p[j]++;
			k = s[k];
		}
		best=-1;
		recurs(1,1);
		val[j]=best;
		//printf("%d %d\n",best,p[j]);
	}
	printf("%d\n",n[0]+n[1]-max(min(p[0],val[1]),min(p[1],val[0])));
}

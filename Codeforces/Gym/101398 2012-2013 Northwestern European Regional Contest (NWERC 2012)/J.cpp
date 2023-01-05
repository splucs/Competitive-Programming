#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000009

int arr[MAXN];

int main(){
	int n,x,i;
	map<int,int> cont;
	
	while(scanf("%d%d",&x,&n)!=EOF){
		x*=10000000;
		cont.clear();
		for (i=0;i<n;i++){
			scanf("%d",&arr[i]);
			cont[arr[i]]++;
		}
		sort(arr,arr+n);
		for (i=0;i<n;i++){
			int y = x-arr[i];
			if ((y==arr[i]&&cont[y]>1)||(y!=arr[i]&&cont[y]))break;
		}
		if (i==n)printf("danger\n");
		else printf("yes %d %d\n",arr[i],x-arr[i]);
	}
}
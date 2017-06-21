#include <cstdio>
#include <algorithm>
using namespace std;

int main(){
	int a[4],ans=1000000,sum=0;
	for (int i=0;i<4;i++){
		scanf("%d",&a[i]);
		sum+=a[i];
	}
	for (int i=0;i<4;i++){
		for (int j=i+1;j<4;j++)
			ans = min(ans,abs(sum-2*(a[i]+a[j])));
	}printf("%d\n",ans);
}

#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

char in[MAXN], out[MAXN];
int cap[MAXN];
int pd[MAXN];

int main() {
	int N,ans;
	while(scanf("%d", &N)&&N!=0){
		for (int i=0;i<N;i++){
			cin>>cap[i]>>in[i]>>out[i];
		}
		ans = 0;
		for (int i=N-1;i>=0;i--){
			pd[i] = 1;
			for (int j=i+1;j<N;j++){
				if (out[i]==in[j] && cap[i]>=cap[j])
					pd[i] = max(pd[i],pd[j]+1);
			}
			//cout<<pd[i]<<" ";
			ans = max(ans,pd[i]);
		}
		printf("%d\n",ans);
	}
	
}
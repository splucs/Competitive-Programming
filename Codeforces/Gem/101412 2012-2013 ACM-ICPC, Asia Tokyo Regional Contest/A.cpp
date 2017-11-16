#include <bits/stdc++.h>
using namespace std;
#define MAXN 142

int mod(int a,int n){
	return ((a%n)+n)%n;
}

int main(){
	int N,m,n,p,ans;
	scanf("%d",&N);
	
	while (N-->0){
		scanf("%d%d",&m,&n);
		p = m*m+n*n;
		ans = 0;
		
		for (int i=-MAXN;i<=MAXN;i++){
			if (i*i>p)continue;
			for (int j=-MAXN;j<=MAXN;j++){
				int q = i*i+j*j;
				if (q>p)continue;
				if (q>0&&mod(i*m+j*n,q)==0&&mod(i*n-j*m,q)==0){
					ans++;
					//cout<<i<<" "<<j<<endl;
				}
			}
		}
		//cout<<ans<<endl;
		if (ans==8)printf("P\n");
		else printf("C\n");
	}
}
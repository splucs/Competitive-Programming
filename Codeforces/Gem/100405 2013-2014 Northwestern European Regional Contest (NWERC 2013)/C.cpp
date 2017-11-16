#include <bits/stdc++.h>
using namespace std;
#define MAXN 10009
#define EPS 1e-9

double prob[MAXN];

int getVal(char n){
	if (n>='0'&&n<='9')return n-'0';
	if (n=='A')return 11;
	return 10;
}

int main(){
	int n,m,a;
	char c,c1;
	double ans;
	
	while (scanf("%d%d ",&n,&m)!=EOF){
		memset(prob,0,sizeof(prob));
		
		for (int i=0;i<n;i++){
			prob[m] = 1;
			scanf("%c%c",&c,&c1);
			//cout<<c<<endl;
			if (c=='1'){
				m+=10;
				scanf("%c",&c);
			}
			else m+=getVal(c);
			//cout<<m<<endl;
			
		}
		for (int i=m;i>0;i--){
			if (prob[i]>EPS){
				//cout<<prob[i]<<" ";
				continue;
			}
			double cnt = 0;
			for (int j=2;j<=11;j++){
				cnt+=prob[j+i];
			}cnt+=3*prob[i+10];
			prob[i] = cnt/13;
			//cout<<prob[i]<<" ";
		}//cout<<endl;
		ans = 0;
		for (int i=1;i<=10;i++)ans+=prob[i]/10;
		printf("%.25lf\n",ans);
	}
}
#include <bits/stdc++.h>
using namespace std;

int a[200000],b[200000],c[200000];

int main(){
	int n,u,p[3],ans = 0,wmax,cmax=-1,index,bmax=-1;
	cin>>n;
	queue<int> val;
	for (int i=0;i<n;i++){
		cin>>p[0]>>p[1]>>p[2];
		for (int k=0;k<3;k++){
			wmax=-1;
			for (int j=k;j<3;j++){
				if (p[j]>wmax){
					wmax = p[j];
					index = j;
				}
			}
			wmax = p[k];
			p[k] = p[index];
			p[index] = wmax;
		}
		a[i] = p[0];
		b[i] = p[1];
		c[i] = p[2];
		
		cmax = max(c[i],cmax);
		bmax = max(b[i],bmax);
	}//cout<<bmax<<endl<<cmax<<endl;
	for (int i=0;i<n;i++){
		if (a[i]>=bmax&&b[i]>=cmax){
			ans++,val.push(i+1);
		}
	}cout<<ans<<endl;
	while (true){
		cout<<val.front();
		val.pop();
		if (val.empty())break;
		cout<<" ";
	}
	cout<<endl;
}
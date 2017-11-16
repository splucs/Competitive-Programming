#include <bits/stdc++.h>
using namespace std;
#define WMIN 1E-9
#define WMAX 1E+9
typedef pair<double,double> dd;

bool sorte(dd line1,dd line2){
	if (fabs(line1.first-line2.first)<WMIN)
		return line1.second<line2.second;
	return line1.first<line2.first;
}

dd val[1000000];

int main(){
	int n,x[1000],y[1000],inuse,ans,qtt,photo=1;
	dd now,prev;
	while(cin>>n&&n!=0){
		qtt=0;
		for (int i=0;i<n;i++){
			cin>>x[i]>>y[i];
			for (int j=0;j<i;j++){
				val[qtt++] = x[i]!=x[j]?dd((double)(y[i]-y[j])/(x[i]-x[j]),(double)(x[i]*y[j]-x[j]*y[i])/(x[i]-x[j])):
				dd(x[i],WMAX);
			}
		}sort(val,val+qtt,sorte);
		prev = val[0],inuse=1;
		ans = 0;
		for (int i=1;i<qtt;i++){
			now = val[i];
			//cout<<now.first<<" "<<now.second<<endl;
			if (fabs(now.first-prev.first)<WMIN && fabs(now.second-prev.second)<WMIN){
				inuse++;
			}else{
				n = round((1+sqrt((double)1+8*inuse))/2);
				ans = max(n,ans);
				inuse = 1;
			}
			prev=now;
		}
		
		n = round((1+sqrt((double)1+8*inuse))/2);
		ans = max(n,ans);
		if (ans<4)cout<<"Photo "<<photo++<<": 0 points eliminated"<<endl;
		else cout<<"Photo "<<photo++<<": "<<ans<<" points eliminated"<<endl;
	}
}
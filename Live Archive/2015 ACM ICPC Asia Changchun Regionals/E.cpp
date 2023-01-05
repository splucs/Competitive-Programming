#include <bits/stdc++.h>
using namespace std;
#define MAXN 10009
#define INF 1e9
#define EPS 1e-9
#define _USE_MATH_DEFINES

double a, b, c;

double cdist(double x1,double y1,double x2,double y2){
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

double f(double x){
	return a*x*x+b*x+c;
}

int main(){
	int t,n,x[MAXN],y[MAXN];
	double s[MAXN], rmin, rmax, r,d[MAXN],xv;
	cin>>t;
	while (t-->0){
		cin>>n;
		for (int i=0;i<n;i++)cin>>x[i]>>y[i];
		for (int i=0;i<n;i++)d[i] = cdist(x[i],y[i],x[(i+1)%n],y[(i+1)%n]);

		rmax = INF;
		rmin = 0;
		a = b = c = 0;
		s[0] = 0;

		for (int i=1;i<=n;i++){
			s[i] = -s[i-1]+d[i-1];
			//cout<<s[i]<<endl;
		}
		for (int i=1;i<n;i++){
			if (i%2==0){
				rmin = max(rmin,-s[i]);
				b+=2*s[i];
			}
			else {
				rmax = min(rmax,s[i]);
				b-=2*s[i];
			}
			c+=s[i]*s[i];
		}a = n;
		//cout<<rmin<<" "<<rmax<<" "<<a<<" "<<b<<" "<<c<<endl;
		if ((n%2==0 && abs(s[n])>EPS)||(n%2==1 && s[n]<0)||rmax<rmin){
			cout<<"IMPOSSIBLE"<<endl;
			continue;
		}
		if (n%2==1)r = s[n]/2;
		else{
			xv = -b/(2*a);
			if (xv<=rmax&&xv>=rmin)r = xv;
			else if (xv<rmin)r = rmin;
			else r = rmax;
		}
		printf("%.2lf\n",f(r)*M_PI);
		for (int i=0;i<n;i++){
			if (i%2==1)printf("%.2lf\n",s[i]-r);
			else printf("%.2lf\n",s[i]+r);
		}
	}

}

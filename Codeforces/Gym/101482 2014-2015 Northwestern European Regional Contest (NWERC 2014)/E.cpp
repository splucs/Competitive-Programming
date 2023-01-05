#include <bits/stdc++.h>
using namespace std;
#define EPS 1e-9

double t,u,k;

double func(double c){
	return c*c*pow(k,c) - t/(u*log(k));
}

int main(){
	double n,p,s,v;
	cin>>n>>p>>s>>v;
	t = s/v;
	k = pow(log2(n),sqrt(2));
	u = (n/p)/1000000000;
	
	double l = 0.000000001, r = sqrt(t/(u*log(k))),mid;
	while (fabs(r-l)>1e-9){
		mid = (l+r)/2;
		if (func(mid)>0)r = mid;
		else l = mid;
	}
	printf("%.9lf %.9lf\n",u*pow(k,mid)+t*(1+1/mid),mid);
	
}
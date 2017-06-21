#include <cstdio>
#include <cmath>

double norm(double a, double b) {
	return sqrt(a*a+b*b);
}

int main()
{
	int N, AAH;
	double Xc, Yc, L, x[4], y[4], xa[4], ya[4];
	bool possible=true;
	scanf("%d %d", &N, &AAH);
	scanf("%lf %lf %lf", &Xc, &Yc, &L);
	xa[0]=Xc+L/2.0;
	ya[0]=Yc+L/2.0;
	xa[1]=Xc-L/2.0;
	ya[1]=Yc+L/2.0;
	xa[2]=Xc+L/2.0;
	ya[2]=Yc-L/2.0;
	xa[3]=Xc-L/2.0;
	ya[3]=Yc-L/2.0;
	for(int i=1; i<N && possible; i++){
		scanf("%lf %lf %lf", &Xc, &Yc, &L);
		x[0]=Xc+L/2.0;
		y[0]=Yc+L/2.0;
		x[1]=Xc-L/2.0;
		y[1]=Yc+L/2.0;
		x[2]=Xc+L/2.0;
		y[2]=Yc-L/2.0;
		x[3]=Xc-L/2.0;
		y[3]=Yc-L/2.0;
		possible=false;
		for(int i=0; i<4; i++){
			if(norm(xa[i]-Xc, ya[i]-Yc)<=AAH) possible=true;
			for(int j=0; j<4; j++){
				if(norm(xa[i]-x[j], ya[i]-y[j])<=AAH) possible=true;
			}
			if(xa[i]<=x[0] && xa[i]>=x[1]){
				if(norm(ya[i]-y[0], 0)<=AAH || norm(ya[i]-y[2], 0)<=AAH || (ya[i]<=y[0] && ya[i]>=y[2])) possible=true;
			}
			if(ya[i]<=y[0] && ya[i]>=y[2]){
				if(norm(xa[i]-x[0], 0)<=AAH || norm(xa[i]-x[1], 0)<=AAH || (xa[i]<=x[0] && xa[i]>=x[1])) possible=true;
			}
			if(x[i]<=xa[0] && x[i]>=xa[1]){
				if(norm(y[i]-ya[0], 0)<=AAH || norm(y[i]-ya[2], 0)<=AAH || (y[i]<=ya[0] && y[i]>=ya[2])) possible=true;
			}
			if(y[i]<=ya[0] && y[i]>=ya[2]){
				if(norm(x[i]-xa[0], 0)<=AAH || norm(x[i]-xa[1], 0)<=AAH || (x[i]<=xa[0] && x[i]>=xa[1])) possible=true;
			}
		}
		for(int i=0; i<4; i++){
			xa[i]=x[i];
			ya[i]=y[i];
		}
	}
	if(possible) printf("YEAH\n");
	else printf("OUCH\n");
	return 0;
}
#include <bits/stdc++.h>
using namespace std;
#define MAXN 109
#define EPS 1e-9

struct point {
	double x, y;
	point() { x = y = 0.0; }
	point(double _x, double _y) : x(_x), y(_y) {}
	double norm(){
		return hypot(x, y);
	}
	point normalized(){
		return point(x,y)*(1.0/norm());
	}
	double angle(){ return atan2(y, x);	}
	double polarAngle(){
		double a = atan2(y, x);
		return a < 0 ? a + 2*M_PI : a;
	}
	bool operator < (point other) const {
		if (fabs(x - other.x) > EPS) return x < other.x;
		else return y < other.y;
	}
	bool operator == (point other) const {
		return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS));
	}
	point operator +(point other) const{
		return point(x + other.x, y + other.y);
	}
	point operator -(point other) const{
		return point(x - other.x, y - other.y);
	}
	point operator *(double k) const{
		return point(x*k, y*k);
	}
};

double dist(point p1, point p2) {
	return hypot(p1.x - p2.x, p1.y - p2.y);
}

point p[MAXN];
int t[MAXN];

int main(){
	int n,t0,x,y;
	double d1,d2;
	point prev;
	scanf("%d%d",&n,&t0);
	for (int i=0;i<n;i++){
		scanf("%d%d%d",&x,&y,&t[i]);
		p[i] = point(x,y);
	}
	int tr = t0;
	d1=d2=0;
	prev = p[0];
	for (int i=1;i<n;i++){
		while (tr<=t[i]){
			point p3 = p[i]-p[i-1];
			point p2 = p[i-1]+p3*((double)(tr-t[i-1])/(double)(t[i]-t[i-1]));
			d2+=dist(prev,p2);
			tr+=t0;
			prev = p2;
		}
		d1+=dist(p[i],p[i-1]);
	}d2+=dist(p[n-1],prev);
	printf("%.14lf\n",100*(d1-d2)/d1);
}
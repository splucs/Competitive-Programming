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

int main(){
	int T,n,k,x,y;
	double d[6];
	cin>>T;
	while (T-->0){
		cin>>n;
		for (int i=0;i<n;i++){
			cin>>x>>y;
			p[i] = point(x,y);
		}
		if (n!=4){
			cout<<"NO"<<endl;
			continue;
		}k = 0;
		for (int i=0;i<4;i++){
			for (int j=i+1;j<4;j++){
				d[k++] = dist(p[i],p[j]);
				//cout<<d[k-1]<<endl;
			}
		}
		sort(d,d+k);
		bool ok = true;
		for (int i=1;i<4;i++){
			if (abs(d[i]-d[i-1])>EPS){
				ok = false;
				break;
			}
		}
		if (abs(d[5]-d[4])>EPS)ok = false;
		if (abs(d[0]*sqrt(2)-d[5])>EPS)ok = false;
		if (ok)cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
}
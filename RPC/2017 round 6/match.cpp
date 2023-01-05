#include <bits/stdc++.h>
using namespace std;
#define EPS 1e-9

int x2,y2,x3,y3;

struct point {
    double x,y;
    point() { x = y = 0.0; }
	point(double _x, double _y) : x(_x), y(_y) {}
	point operator +(point other) const{
		return point(x + other.x, y + other.y);
	}
	point operator -(point other) const{
		return point(x - other.x, y - other.y);
	}
	bool operator == (point other) const {
		return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS));
	}
};

vector<point> P;

double cross(point p1, point p2) {
	return p1.x*p2.y - p1.y*p2.x;
}

point lineIntersectSeg(point p, point q, point A, point B) {
	double a = B.y - A.y;
	double b = A.x - B.x;
	double c = B.x * A.y - A.x * B.y;
	double u = fabs(a * p.x + b * p.y + c);
	double v = fabs(a * q.x + b * q.y + c);
	return point((p.x * v + q.x * u) / (u+v), (p.y * v + q.y * u) / (u+v));
}

void initialize(){
    P.clear();
    P.push_back(point(x2,y2));
    P.push_back(point(x2,y3));
    P.push_back(point(x3,y3));
    P.push_back(point(x3,y2));
    P.push_back(point(x2,y2));
}

double area(){
    double result = 0.0;
    for (int i = 0; i < (int)P.size()-1; i++) {
        result += cross(P[i], P[i+1]);
    }
    return fabs(result/2.0);
}

vector<point> cutPolygon(point a, point b) {
    vector<point> R;
    double left1, left2;
    for (int i = 0; i < (int)P.size(); i++) {
        left1 = cross(b-a, P[i]-a);
        if (i != (int)P.size()-1) left2 = cross(b-a, P[i+1]-a);
        else left2 = 0;
        if (left1 > -EPS) R.push_back(P[i]);
        if (left1 * left2 < -EPS)
            R.push_back(lineIntersectSeg(P[i], P[i+1], a, b));
    }
    if (!R.empty()&&!(R.back()==R.front()))R.push_back(R[0]);
    return R;
}

int main(){
    int t,n,x[21],y[21];
    double a[2];
    cin>>t;
    while(t-->0){
        cin>>x2>>y2>>x3>>y3;
        cin>>n;
        a[0] = a[1]=0;
        for (int i=0;i<2*n;i++)cin>>x[i]>>y[i];

        for (int i=0;i<2*n;i++){
            initialize();
            for (int j=0;j<2*n;j++){
                if (i==j)continue;
                point q = point(((double)x[i]+x[j])/2,((double)y[i]+y[j])/2);
                point r;
                if (y[i]==y[j])r = q+point(0,1);
                else{
                    double m = ((double)(x[i]-x[j]))/(y[j]-y[i]);
                    r = q+point(1,m);
                }
                //cout<<q.x<<" "<<q.y<<" "<<r.x<<" "<<r.y<<endl;
                if (cross(r-q,point(x[i],y[i])-q)>-EPS)P=cutPolygon(q,r);
                else P=cutPolygon(r,q);
            }
            double val = area();
            a[i/n]+=val;
            //cout<<val<<" ";
        }
        if (a[0]>a[1])cout<<"Gryffindor"<<endl;
        else cout<<"Slytherin"<<endl;
    }
}

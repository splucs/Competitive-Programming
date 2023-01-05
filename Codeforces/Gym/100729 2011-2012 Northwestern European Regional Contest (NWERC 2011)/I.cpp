#include <bits/stdc++.h>
using namespace std;
#define EPS 1e-9
#define MAXN 100009
typedef pair<int,int> ii;


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

double inner(point p1, point p2) {
	return p1.x*p2.x + p1.y*p2.y;
}

double cross(point p1, point p2) {
	return p1.x*p2.y - p1.y*p2.x;
}

bool ccw(point p, point q, point r) {
	return cross(q-p, r-p) > 0;
}

bool collinear(point p, point q, point r) {
	return fabs(cross(p-q, r-p)) < EPS;
}

point rotate(point p, double rad) {
	return point(p.x * cos(rad) - p.y * sin(rad),
	p.x * sin(rad) + p.y * cos(rad));
}

double angle(point a, point o, point b) {
	return acos(inner(a-o, b-o) / (dist(o,a)*dist(o,b)));
}

point proj(point u, point v){
	return v*(inner(u,v)/inner(v,v));
}

bool between(point p, point q, point r) {
    return collinear(p, q, r) && inner(p - q, r - q) <= EPS;
}

bool lineIntersectSeg(point p, point q, point A, point B) {
	if (fabs(cross(p-q, B-A)) < EPS) {
		if (between(p, A, q) && between(p, B, q)) return true;
		return false;
	}
	double a = B.y - A.y;
	double b = A.x - B.x;
	double c = B.x * A.y - A.x * B.y;
	double u = fabs(a * p.x + b * p.y + c);
	double v = fabs(a * q.x + b * q.y + c);
	point inter = point((p.x * v + q.x * u) / (u+v), (p.y * v + q.y * u) / (u+v));
	return between(A, inter, B) && between(p, inter, q);
}

typedef pair<point,point> line;

map<ii,bool> isCircle;
line lines[11];
int w;
double r;

bool canJoin(int x,int y,int x1,int y1){
	point p1 = point(x,y), p2 = point(x1,y1);
	
	double d = r-dist(p1,p2);
	bool intersected = false;
	
	for (int i=0;i<w;i++){
		if (lineIntersectSeg(p1,p2,lines[i].first,lines[i].second))d = d - 1.0, intersected = true;
	}
	
	return d>=-EPS;
}

int main(){
	int t,s,p,x,y,x1,y1;
	vector<ii> ans;
	
	cin>>t;
	while(t-->0){
		isCircle.clear();
		cin>>s>>r>>w>>p;
		for (int i=0;i<s;i++){
			cin>>x>>y;
			isCircle[ii(x,y)] = true;
		}
		for (int i=0;i<w;i++){
			cin>>x>>y>>x1>>y1;
			lines[i] = line(point(x,y),point(x1,y1));
		}for (int i=0;i<p;i++){
			cin>>x>>y;
			ans.clear();
			for (int j=x-r;j<=x+r;j++){
				for (int k=y-r;k<=y+r;k++){
					if (isCircle.count(ii(j,k))&&canJoin(x,y,j,k))ans.push_back(ii(j,k));
				}
			}
			sort(ans.begin(),ans.end());
			printf("%d",ans.size());
			for (int j=0;j<ans.size();j++){
				printf(" (%d,%d)",ans[j].first,ans[j].second);
			}
			printf("\n");
		}
		
	}
}
#include <cstdio>
#include <cmath>
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
    return collinear(p, q, r) && inner(p - q, r - q) <= 0;
}

/*
 * POLYGON 2D
 */

#include <vector>
#include <algorithm>
using namespace std;

point lineIntersectSeg(point p, point q, point A, point B) {
	double a = B.y - A.y;
	double b = A.x - B.x;
	double c = B.x * A.y - A.x * B.y;
	double u = fabs(a * p.x + b * p.y + c);
	double v = fabs(a * q.x + b * q.y + c);
	return point((p.x * v + q.x * u) / (u+v), (p.y * v + q.y * u) / (u+v));
}

struct polygon{
	vector<point> P;
	polygon(){ }
	polygon(vector<point> _P) : P(_P) {
		if (!P.empty() && !(P.back() == P.front()))
			P.push_back(P[0]);
		if (signedArea() < 0.0){
			for(int i = 0; 2*i < (int)P.size(); i++){
				swap(P[i], P[P.size()-i-1]);
			}
		}
	}
	double perimeter(){
		double result = 0.0;
		for (int i = 0; i < (int)P.size()-1; i++) result += dist(P[i], P[i+1]);
		return result;
	}
	double signedArea(){
		double result = 0.0;
		for (int i = 0; i < (int)P.size()-1; i++) {
			result += cross(P[i], P[i+1]);
		}
		return result/2.0;
	}
	double area() { return fabs(signedArea()); }
	bool isConvex() {
		int sz = (int)P.size();
		if (sz <= 3) return false;
		bool isLeft = ccw(P[0], P[1], P[2]);
		for (int i = 1; i < sz-1; i++){
			if (ccw(P[i], P[i+1], P[(i+2) == sz ? 1 : i+2]) != isLeft)
				return false;
		}
		return true;
	}
	bool inPolygon(point p) {
		if (P.size() == 0u) return false;
		double sum = 0.0;
		for (int i = 0; i < (int)P.size()-1; i++) {
			if (ccw(p, P[i], P[i+1])) sum += angle(P[i], p, P[i+1]);
			else sum -= angle(P[i], p, P[i+1]);
		}
		return fabs(fabs(sum) - 2*M_PI) < EPS;
	}
	polygon cutPolygon(point a, point b) {
		vector<point> R;
		double left1, left2;
		for (int i = 0; i < (int)P.size(); i++) {
			left1 = cross(b-a, P[i]-a);
			if (i != (int)P.size()-1) left2 = cross(b-a, P[i+1]-a);
			else left2 = 0;
			if (left1 > -EPS) P.push_back(P[i]);
			if (left1 * left2 < -EPS)
				R.push_back(lineIntersectSeg(P[i], P[i+1], a, b));
		}
		return polygon(R);
	}
};

polygon polyintersect(polygon& PP, polygon& PQ) {
	vector<point> P = PP.P; Q = PQ.P;
	P.pop_back(); Q.pop_back();
    int m = Q.size(), n = P.size();
    int a = 0, b = 0, aa = 0, ba = 0, inflag = 0;
    polygon R;
    while ((aa < n || ba < m) && aa < 2*n && ba < 2*m) {
        point p1= P[a], p2= P[(a+1) % n], q1= Q[b], q2=Q[(b+1)%m];
        point A = p2 - p1, B = q2 - q1;
        int cross = cmp(A % B), ha = ccw(p2, q2, p1), hb = ccw(q2, p2, q1);
        if (cross == 0 && ccw(p1, q1, p2) == 0 && cmp(A * B) < 0) {
            if (between(p1, q1, p2)) R.push_back(q1);
            if (between(p1, q2, p2)) R.push_back(q2);
            if (between(q1, p1, q2)) R.push_back(p1);
            if (between(q1, p2, q2)) R.push_back(p2);
            if (R.size() < 2) return polygon();
            inflag = 1; break;
        } else if (cross != 0 && seg_intersect(p1, p2, q1, q2)) {
            if (inflag == 0) aa = ba = 0;
            R.push_back(line_intersect(p1, p2, q1, q2));
            inflag = (hb > 0) ? 1 : -1;
        }
        if (cross == 0 && hb < 0 && ha < 0) return R;
        bool t = cross == 0 && hb == 0 && ha == 0;
        if (t ? (inflag == 1) : (cross >= 0) ? (ha <= 0) : (hb > 0)) {
            if (inflag == -1) R.push_back(q2);
            ba++; b++; b %= m;
        } else {
            if (inflag == 1) R.push_back(p2);
            aa++; a++; a %= n;
        }
    }
    if (inflag == 0) {
        if (in_poly(P[0], Q)) return P;
        if (in_poly(Q[0], P)) return Q;
    }
    R.erase(unique(all(R)), R.end());
    if (R.size() > 1 && R.front() == R.back()) R.pop_back();
    return R;
}

/*
 * TEST MATRIX
 */
 
bool test(){
	int n;
	double x, y;
	vector<point> p1, p2, m;
	printf("insert polygon 1:\n");
	scanf("%d", &n);
	while(n--) {
		scanf("%lf %lf", &x, &y);
		p1.push_back(point(x, y));
	}
	printf("insert polygon 2:\n");
	scanf("%d", &n);
	while(n--) {
		scanf("%lf %lf", &x, &y);
		p2.push_back(point(x, y));
	}
	printf("intersection:\n");
	m = polyintersect(polygon(p1), polygon(p2)).P;
	for(int i=0; i<(int)m.size(); i++){
		printf("%.2f %.2f\n", m[i].x, m[i].y);
	}
	return true;
}

int main()
{
	test();
	return 0;
}
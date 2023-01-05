#include <bits/stdc++.h>
using namespace std;
#define EPS 1e-9
#define MAXN 69
#define INF 1e+18

bool equal(double a, double b) {
	return fabs(a-b) < EPS;
}

struct point {
	double x, y, z;
	point() { x = y = z = 0.0; }
	point(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
	double norm2(){
		return x*x + y*y + z*z;
	}
	double norm(){
		return sqrt(norm2());
	}
	bool operator == (point other) const {
		return equal(x, other.x) && equal(y, other.y) && equal(z, other.z);
	}
	point operator +(point other) const{
		return point(x + other.x, y + other.y, z + other.z);
	}
	point operator -(point other) const{
		return point(x - other.x, y - other.y, z - other.z);
	}
	point operator *(double k) const{
		return point(x*k, y*k, z*k);
	}
};

double inner(point p1, point p2) {
	return p1.x*p2.x + p1.y*p2.y + p1.z*p2.z;
}

double dist(point p1, point p2) {
	return sqrt(inner(p1-p2, p1-p2));
}

point cross(point p1, point p2) {
	point ans;
	ans.x = p1.y*p2.z - p1.z*p2.y;
	ans.y = p1.z*p2.x - p1.x*p2.z;
	ans.z = p1.x*p2.y - p1.y*p2.x;
	return ans;
}

bool collinear(point p, point q, point r) {
	return cross(p-q, r-p).norm() < EPS;
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

bool coplanar(point a, point b, point A, point B) {
	return equal(inner(b-a, cross(A-a, B-a)), 0);
}

bool intersection(point a, point b, point A, point B, point & ip) {
	if (!coplanar(a, b, A, B)) return false;
	point da = b - a;
	point db = B - A;
	point dc = A - a;
	double s = inner(cross(dc, db), cross(da, db)) / cross(da, db).norm2();
	if (s >= -EPS && s <= 1.0+EPS) {
		ip = a + cross(da, point(s, s, s));
		return true;
	}
	return false;
}

point arr[MAXN];
typedef pair<point, point> pp;
vector<pp> seg;

double cubedist(point p1, point p2) {
	if (p1 == p2) return 0;
	point v = p2 - p1;
	bool plane = false;
	
	//plane normal to z
	if (equal(v.z, 0)) {
		bool ok1 = false, ok2 = false;
		for(int i=0; i<(int)seg.size(); i++) {
			point vs = seg[i].second - seg[i].first;
			if (between(seg[i].second, p1, seg[i].first) && equal(vs.z, 0)) ok1 = true;
			if (between(seg[i].second, p2, seg[i].first) && equal(vs.z, 0)) ok2 = true;
		}
		plane = plane || (ok1 && ok2);
	}
	
	//plane normal to y
	if (equal(v.y, 0)) {
		bool ok1 = false, ok2 = false;
		for(int i=0; i<(int)seg.size(); i++) {
			point vs = seg[i].second - seg[i].first;
			if (between(seg[i].second, p1, seg[i].first) && equal(vs.y, 0)) ok1 = true;
			if (between(seg[i].second, p2, seg[i].first) && equal(vs.y, 0)) ok2 = true;
		}
		plane = plane || (ok1 && ok2);
	}
	
	//plane normal to x
	if (equal(v.x, 0)) {
		bool ok1 = false, ok2 = false;
		for(int i=0; i<(int)seg.size(); i++) {
			point vs = seg[i].second - seg[i].first;
			if (between(seg[i].second, p1, seg[i].first) && equal(vs.x, 0)) ok1 = true;
			if (between(seg[i].second, p2, seg[i].first) && equal(vs.x, 0)) ok2 = true;
		}
		plane = plane || (ok1 && ok2);
	}
	
	if (!plane) return INF;
	
	point ip;
	for(int i=0; i<(int)seg.size(); i++) {
		if (between(seg[i].second, p1, seg[i].first) || between(seg[i].second, p2, seg[i].first)) continue;
		if (between(p1, seg[i].second, p2) && between(p1, seg[i].first, p2)) continue;
		if (intersection(p1, p2, seg[i].first, seg[i].second, ip)) return INF;
	}
	
	return dist(p1, p2);
}

const int idx1[6] = {0, 0, 1, 0, 0, 1};
const int idy1[6] = {0, 1, 0, 0, 1, 0};
const int idz1[6] = {1, 0, 0, 1, 0, 0};
const int idx2[6] = {0, 1, 1, 1, 0, 1};
const int idy2[6] = {1, 1, 0, 0, 1, 1};
const int idz2[6] = {1, 0, 1, 1, 1, 0};

double arrdist(int u, int v) {
	point pit[2];
	pit[0] = arr[u], pit[1] = arr[v];
	if (equal(pit[0].x, pit[1].x) || equal(pit[0].y, pit[1].y) || equal(pit[0].z, pit[1].z)) {
		return cubedist(pit[0], pit[1]);
	}
	
	double ans = INF;
	for(int k=0; k<6; k++) {
		point a = point(pit[idx1[k]].x, pit[idy1[k]].y, pit[idz1[k]].z);
		point b = point(pit[idx2[k]].x, pit[idy2[k]].y, pit[idz2[k]].z);
		double d1 = dist(pit[0], a);
		double d2 = dist(pit[1], b);
		point inter = a + ((b-a)*(d1/(d1+d2)));
		ans = min(ans, cubedist(pit[0], inter) + cubedist(inter, pit[1]));
		printf("inter = (%.1f,%.1f,%.1f)\n", inter.x, inter.y, inter.z);
	}
	return ans;
}

int main() {
	double x = 1, y = 1, z = 2;
	seg.push_back(pp(point(0, 0, 0), point(0, 0, z)));
	seg.push_back(pp(point(0, 0, 0), point(0, y, 0)));
	seg.push_back(pp(point(0, 0, 0), point(x, 0, 0)));
	
	seg.push_back(pp(point(0, 0, z), point(0, y, z)));
	seg.push_back(pp(point(0, 0, z), point(x, 0, z)));
	seg.push_back(pp(point(0, y, 0), point(x, y, 0)));
	seg.push_back(pp(point(0, y, 0), point(0, y, z)));
	seg.push_back(pp(point(x, 0, 0), point(x, y, 0)));
	seg.push_back(pp(point(x, 0, 0), point(x, 0, z)));
	
	seg.push_back(pp(point(x, 0, z), point(x, y, z)));
	seg.push_back(pp(point(0, y, z), point(x, y, z)));
	seg.push_back(pp(point(x, y, 0), point(x, y, z)));
	arr[0] = point(0, 0, 0);
	arr[1] = point(x, y, z);
	printf("dist = %.3f\n", arrdist(0, 1));
	return 0;
}
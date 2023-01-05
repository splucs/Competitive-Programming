#include <bits/stdc++.h>
using namespace std;
#define MAXN 2009
#define EPS 1e-9

struct point {
	double x, y, z;
	point() { x = y = z = 0.0; }
	point(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
	double norm(){
		return sqrt(x*x+y*y+z*z);
	}
	point normalized(){
		return point(x,y,z)*(1.0/norm());
	}
	bool operator < (point other) const {
		if (fabs(x - other.x) > EPS) return x < other.x;
		else if (fabs(y - other.y) > EPS) return y < other.y;
		else return z < other.z;
	}
	bool operator == (point other) const {
		return (fabs(x - other.x) < EPS && fabs(y - other.y) < EPS && fabs(z - other.z) < EPS);
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

double dist(point p1, point p2) {
	return (p1-p2).norm();
}

double inner(point p1, point p2) {
	return p1.x*p2.x + p1.y*p2.y + p1.z*p2.z;
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

int N, M, R;
point T[20], S[MAXN], E;
double r[MAXN], Tb[20];
bool elim[MAXN];
vector<int> belim[20];

bool intersects(point a, point b, point c, double rd) {
	if (dist(a, c) <= rd + EPS && dist(b, c) <= rd + EPS) return false;
	double k = inner(c-a, b-a);
	point p;
	if (k < EPS) p = a;
	else if (k > inner(b-a, b-a)-EPS) p = b;
	else p = a + proj(c-a, b-a);
	return dist(p, c) <= rd + EPS;
}

int main() {
	while(scanf("%d %d %d", &N, &M, &R), N || M || R) {
		
		for(int i=0; i<N; i++) {
			scanf("%lf %lf %lf %lf", &S[i].x, &S[i].y, &S[i].z, &r[i]);
		}
		for(int j=0; j<M; j++) {
			scanf("%lf %lf %lf %lf", &T[j].x, &T[j].y, &T[j].z, &Tb[j]);
			belim[j].clear();
		}
		scanf("%lf %lf %lf", &E.x, &E.y, &E.z);
		
		for(int j=0; j<M; j++) {
			for(int i=0; i<N; i++) {
				if(intersects(E, T[j], S[i], r[i])) {
					belim[j].push_back(i);
				}
			}
			Tb[j] /= inner(T[j]-E, T[j]-E);
		}
		
		double ans = 0, cur;
		for(int mask=0; mask < (1<<M); mask++) {
			
			memset(&elim, false, sizeof elim);
			cur = 0;
			
			for(int j=0; j<M; j++) {
				if (!(mask & (1<<j))) continue;
				for(int it=0; it<(int)belim[j].size(); it++) {
					elim[belim[j][it]] = true;
				}
				cur += Tb[j];
			}
			
			int toelim = 0;
			for(int i=0; i<N; i++) if (elim[i]) toelim++;
			if (toelim > R) continue;
			ans = max(ans, cur);
		}
		
		printf("%.16f\n", ans);
	}
	
	return 0;
}
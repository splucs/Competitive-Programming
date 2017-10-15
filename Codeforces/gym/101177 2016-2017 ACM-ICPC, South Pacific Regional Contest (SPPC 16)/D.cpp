#include <bits/stdc++.h>
using namespace std;
#define MAXN 109
#define EPS 1e-9

struct point {
	double x, y;
	bool infected;
	point() { x = y = 0.0; }
	point(double _x, double _y) : x(_x), y(_y) {}
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
double cross(point p1, point p2) {
	return p1.x*p2.y - p1.y*p2.x;
}
double inner(point p1, point p2) {
	return p1.x*p2.x + p1.y*p2.y;
}
double collinear(point p, point q, point r) {
	return fabs(cross(p-r, q-r)) < EPS;
}

struct circle{
	point c;
	double r;
	circle(){ c = point(); r = 0; }
	circle(point _c, double _r) : c(_c), r(_r) {}
	bool inside(point p) { return dist(c, p) < r - EPS; }
	bool outside(point p) { return dist(c, p) > r + EPS; }
};

circle circumcircle(point a, point b, point c){
	circle ans;
	point u = point((b-a).y, -(b-a).x);
	point v = point((c-a).y, -(c-a).x);
	point n = (c-b)*0.5;
	double t = cross(u,n)/cross(v,u);
	ans.c = ((a+c)*0.5) + (v*t);
	ans.r = dist(ans.c, a);
	return ans;
}

point trees[MAXN];
int N;

bool checkCircle(circle c) {
	for(int i=0; i<N; i++) {
		if (trees[i].infected && c.outside(trees[i])) return false;
		if (!trees[i].infected && c.inside(trees[i])) return false;
	}
	return true;
}

int main(){
	while(scanf("%d", &N) != EOF) {
		char op;
		for(int i=0; i<N; i++) {
			scanf("%lf %lf %c", &trees[i].x, &trees[i].y, &op);
			if (op == 'I') trees[i].infected = true;
			else trees[i].infected = false;
		}
		
		random_shuffle(trees, trees+N);
		
		bool ok = false;
		if (N <= 2) ok = true;
		for(int i=0; i<N && !ok; i++) {
			for(int j=0; j<i && !ok; j++) {
				
				point c = (trees[i] + trees[j]) * 0.5;
				if (checkCircle(circle(c, dist(c, trees[i])))) ok = true;
				
				for(int k=0; k<j && !ok; k++) {
					if (collinear(trees[i], trees[j], trees[k])) continue;
					if (checkCircle(circumcircle(trees[i], trees[j], trees[k]))) ok = true;
				}
			}
		}
		
		if (!ok) printf("Yes\n");
		else printf("No\n");
	}
	
	return 0;
}
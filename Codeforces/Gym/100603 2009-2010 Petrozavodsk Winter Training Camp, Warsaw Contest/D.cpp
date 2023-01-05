#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

#define EPS 1e-9

struct point {
	double x, y;
	point() { x = y = 0.0; }
	point(double _x, double _y) : x(_x), y(_y) {}
	double norm(){
		return hypot(x, y);
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

double cross(point p1, point p2) {
	return p1.x*p2.y - p1.y*p2.x;
}

bool ccw(point p, point q, point r) {
	return cross(q-p, r-p) > 0;
}

point lineIntersectSeg(point p, point q, point A, point B) {
	double a = B.y - A.y;
	double b = A.x - B.x;
	double c = B.x * A.y - A.x * B.y;
	double u = fabs(a * p.x + b * p.y + c);
	double v = fabs(a * q.x + b * q.y + c);
	return point((p.x * v + q.x * u) / (u+v), (p.y * v + q.y * u) / (u+v));
}

vector<int> adjList[MAXN];
point p[MAXN];

int main() {
	int N, M, a, b;
	scanf("%d %d", &N, &M);
	for(int i=0; i<N; i++) {
		scanf("%lf %lf", &p[i].x, &p[i].y);
	}
	for(int j=0; j<M; j++) {
		scanf("%d %d", &a, &b);
		a--; b--;
		adjList[a].push_back(b);
	}
	vector<point> ch;
	vector<int> li, lj;
	int lastcnt = -1;
	for(int i=0; i<N; i++) {
		sort(adjList[i].begin(), adjList[i].end());
		int cnt = N-1;
		for(int j = ((int)adjList[i].size())-1; j>=0; j--) {
			if (adjList[i][j] == cnt) cnt--;
			else break;
		}
		if (!lj.empty() && cnt <= lj.back()) continue;
		
		if (ch.size() == 0u) {
			ch.push_back(p[i]);
		}
		else if (ch.size() == 1u) {
			ch.push_back(lineIntersectSeg(p[li.back()], p[lj.back()], p[i], p[cnt]));
		}
		else {
			int n = ch.size();
			point cur;
			while(n > 1 && ccw(ch[n-2], ch[n-1], lineIntersectSeg(p[li.back()], p[lj.back()], p[i], p[cnt]))) {
				ch.pop_back();
				li.pop_back();
				lj.pop_back();
				n = ch.size();
			}
			
			ch.push_back(lineIntersectSeg(p[li.back()], p[lj.back()], p[i], p[cnt]));
		}
		
		li.push_back(i);
		lj.push_back(cnt);
		//printf("line %d %d\n", i+1, cnt+1);
	}
	ch.push_back(p[N-1]);
	double ans = 0.0;
	for(int i=1; i<(int)ch.size(); i++) {
		ans += dist(ch[i], ch[i-1]);
	}
	printf("%.10f\n", ans);
	return 0;
}
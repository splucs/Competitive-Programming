#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define MAXS 509
#define EPS 1e-5

struct point {
	double x, y;
	point() { x = y = 0.0; }
	point(double _x, double _y) : x(_x), y(_y) {}
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

point closestToLineSegment(point p, point a, point b) {
	double u = inner(p-a, b-a) / inner(b-a, b-a);
	if (u < 0.0) return a;
	if (u > 1.0) return b;
	return a + ((b-a)*u);
}

double distToLineSegment(point p, point a, point b) {
	return dist(p, closestToLineSegment(p, a, b));
}

double r[MAXN];
point c[MAXN];
map<int, vector<int> > red[MAXN];

int main() {
	int N, Q;
	while(scanf("%d", &N)!=EOF) {
		for(int i=0; i<N; i++) {
			int x, y;
			scanf("%d %d %lf", &x, &y, &r[i]);
			red[x][y].push_back(i);
			red[x-1][y].push_back(i);
			red[x][y-1].push_back(i);
			red[x-1][y-1].push_back(i);
			c[i] = point(x, y);
		}
		scanf("%d", &Q);
		while(Q-->0) {
			int x1, x2, y1, y2;
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			point a, b;
			a = point(x1, y1);
			b = point(x2, y2);
			vector<int> inter;
			if (x1 == x2) {
				for(int y=min(y1, y2), x; y<=max(y1, y2); y++) {
					x = x1;
					for(int dx=-1, dy=0; dx<=0; dx++) {
						vector<int> & v = red[x+dx][y+dy];
						for(int i=0; i<(int)v.size(); i++) {
							if (distToLineSegment(c[v[i]], a, b) <= r[v[i]] + EPS)
								inter.push_back(v[i]);
						}
					}
				}
			}
			else {
				double m = (y1-y2)*1.0/(x1-x2);
				double n = (y2*x1 - y1*x2)*1.0/(x1-x2);
				for(int x=min(x1, x2), y, yn; x<=max(x1, x2); x++) {
					y = m*x + n;
					yn = m*(x+1) + n;
					for(int dy=0, dx=0; dy<=yn; dy++) {
						vector<int> & v = red[x+dx][y+dy];
						for(int i=0; i<(int)v.size(); i++) {
							if (distToLineSegment(c[v[i]], a, b) <= r[v[i]] + EPS)
								inter.push_back(v[i]);
						}
					}
				}
			}
			sort(inter.begin(), inter.end());
			int ans = inter.empty() ? 0 : 1;
			for(int i=1; i<(int)inter.size(); i++) {
				if (inter[i] != inter[i-1]) ans++;
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}
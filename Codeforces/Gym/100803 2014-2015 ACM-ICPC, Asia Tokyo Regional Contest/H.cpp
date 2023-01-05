#include <bits/stdc++.h>
using namespace std;
#define MAXN 5009
#define INF 1e33
#define EPS 1e-9
#define PI (acos(-1.0))
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define fi first
#define se second
#define sz(x) ((int)x.size())
typedef long long ll;

double r;

struct point {
	double x, y;
	point(double _x=0, double _y=0) : x(_x), y(_y) {}
	double norm() {
		return hypot(x, y);
	}
	point operator -(point o) const {
		return point(x - o.x, y - o.y);
	}
	point operator +(point o) const {
		return point(x + o.x, y + o.y);
	}
	point operator *(double k) const {
		return point(x*k, y*k);
	}
	bool operator == (point o) const {
		return fabs(x-o.x) < EPS && fabs(y-o.y) < EPS;
	}
	point normalized() {
		return point{x,y}*(1.0/norm());
	}
	double polarAngle() {
		double a = atan2(y, x);
		return a < 0 ? a + 2*acos(-1.0) : a;
	}
};

double dist(point a, point b) {
	return hypot(a.x-b.x, a.y-b.y);
}

double cross(point a, point b) {
	return a.x*b.y - a.y*b.x;
}

double inner(point a, point b) {
	return a.x*b.x + a.y*b.y;
}

point rotate(point p, double rad) {
	return point(p.x*cos(rad) - p.y*sin(rad), p.x*sin(rad) + p.y*cos(rad));
}

bool parallel(point a, point b) {
	return fabs(cross(a, b)) < EPS;
}

bool collinear(point a, point b, point c) {
	return parallel(b-a, c-a);
}

bool between(point p, point q, point r) {
	return collinear(p, q, r) && inner(p-q, r-q) <= EPS;
}

double angle(point a, point o, point b) {
	double ac = inner(a-o, b-o) / (dist(o,a)*dist(o,b));
	if (ac > 1.0) ac = 1.0;
	if (ac < -1.0) ac = -1.0; 
	return acos(ac);
}

point closestToLineSeg(point p, point a, point b) {
	if (a == b) return a;
	double u = inner(p-a, b-a) / inner(b-a, b-a);
	if (u < 0) u = 0;
	if (u > 1) u = 1;
	return a + ((b-a)*u);
}

double distToLineSeg(point p, point a, point b) {
	return dist(p, closestToLineSeg(p, a, b));
}

struct circle {
	point c;
	double r;

	bool intersects(circle other) {
		double d = dist(c, other.c);
		return d < r + other.r && d > abs(r - other.r);
	}
	pair<point, point> getTangentPoint(point p) {
		double d1 = dist(p, c), theta = asin(r/d1);
		point p1 = rotate(c-p,-theta);
		point p2 = rotate(c-p,theta);
		p1 = p1*(sqrt(d1*d1-r*r)/d1)+p;
		p2 = p2*(sqrt(d1*d1-r*r)/d1)+p;
		return make_pair(p1,p2);
	}
	vector< pair<point,point> > getTangentSegs(circle other) {
		vector<pair<point, point> > ans;
		double d = dist(other.c, c);
		double dr = abs(r - other.r), sr = r + other.r;
		if (dr >= d) return ans;
		double u = acos(dr / d);
		point dc1 = ((other.c - c).normalized())*r;
		point dc2 = ((other.c - c).normalized())*other.r;
		ans.push_back(make_pair(c + rotate(dc1, u), other.c + rotate(dc2, u)));
		ans.push_back(make_pair(c + rotate(dc1, -u), other.c + rotate(dc2, -u)));
		if (sr >= d) return ans;
		double v = acos(sr / d);
		dc2 = ((c - other.c).normalized()) * other.r;
		ans.push_back({c + rotate(dc1, v), other.c + rotate(dc2, v)});
		ans.push_back({c + rotate(dc1, -v), other.c + rotate(dc2, -v)});
		return ans;
	}
	pair<point, point> getIntersectionPoints(circle other){
		assert(intersects(other));
		double d = dist(c, other.c);
		double u = acos((other.r*other.r + d*d - r*r) / (2*other.r*d));
		point dc = ((other.c - c).normalized()) * r;
		return make_pair(c + rotate(dc, u), c + rotate(dc, -u));
	}
};

int n;
vector<circle> poles;
vector<point> P;
vector<int> pid;

double circdist(point u, point v, point o) {
	double rad = angle(u, o, v), d[2];
	double theta1 = (u-o).polarAngle();
	double theta2 = (v-o).polarAngle();
	if (theta1 > theta2) swap(theta1, theta2);
	d[0] = theta2 - theta1;
	d[1] = theta1 - theta2 + 2*PI;
	double cro = cross(v-u, o-u);
	for(circle c : poles) {
		if (dist(c.c, o) >= 2*r - EPS) continue;
		if (c.c == o) continue;
		double theta = (c.c - o).polarAngle();
		if (fabs(theta1-theta) < EPS) return INF;
		else if (fabs(theta2-theta) < EPS) return INF;
		else if (theta1 < theta && theta < theta2) d[0] = INF;
		else if (theta1 > theta || theta > theta2) d[1] = INF;
		else assert(false);
	}
	return r*min(d[0], d[1]);
}

double segdist(point u, point v) {
	for(circle c : poles) {
		if (distToLineSeg(c.c, u, v) < r - EPS) return INF;
	}
	return dist(u, v);
}

double ndist(int i, int j) {
	if (pid[i] != -1 && pid[i] == pid[j])
		return circdist(P[i], P[j], poles[pid[i]].c);
	else return segdist(P[i], P[j]);
}

double dijkstra(int s, int t) {
	vector<double> dist(sz(P), INF);
	dist[s] = 0;
	set< pair<double,int> > nodes;
	nodes.insert(make_pair(0.0, s));
	while(!nodes.empty()) {
		int u = nodes.begin()->second;
		//printf("point (%.3f,%.3f), id %d dist %.3f\n", P[u].x, P[u].y, u, dist[u]);
		nodes.erase(nodes.begin());
		FOR(v, sz(P)) {
			if (u == v) continue;
			double w = ndist(u, v);
			if (dist[v] > dist[u] + w) {
				nodes.erase(make_pair(dist[v], v));
				dist[v] = dist[u] + w;
				nodes.insert(make_pair(dist[v], v));
			}
		}
	}
	return dist[t];
}

point read() {
	double x, y;
	scanf("%lf %lf", &x, &y);
	return point(x, y);
}

int main() {
	int n;
	r = 100;
	scanf("%d", &n);
	P.pb(point());
	pid.pb(-1);
	P.pb(read());
	pid.pb(-1);
	FOR(i, n) {
		poles.pb({read(), r});
		FOR(j, i) {
			auto v = poles[i].getTangentSegs(poles[j]);
			for(auto pp : v) {
				P.pb(pp.fi); pid.pb(i);
				P.pb(pp.se); pid.pb(j);
			}
		}

		auto pp = poles[i].getTangentPoint(P[0]);
		P.pb(pp.fi); pid.pb(i);
		P.pb(pp.se); pid.pb(i);

		pp = poles[i].getTangentPoint(P[1]);
		P.pb(pp.fi); pid.pb(i);
		P.pb(pp.se); pid.pb(i);
	}

	double ans = dijkstra(0, 1);
	if (ans > 1e10) puts("0.0");
	else printf("%.20f\n", ans);
	return 0;
}
#include <bits/stdc++.h>
#define EPS 1e-5
using namespace std;

/*
 * Point 2D
 */

struct point {
	double x, y;
	point() { x = y = 0.0; }
	point(double _x, double _y) : x(_x), y(_y) {}
	double norm() {
		return hypot(x, y);
	}
	point normalized() {
		return point(x,y)*(1.0/norm());
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

double inner(point p1, point p2) {
	return p1.x*p2.x + p1.y*p2.y;
}

double dist(point p1, point p2) {
	return hypot(p1.x - p2.x, p1.y - p2.y);
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

/*
 * Polygon 2D
 */

typedef vector<point> polygon;

int leftmostIndex(vector<point> &P) {
	int ans = 0;
	for(int i=1; i<(int)P.size(); i++) {
		if (P[i] < P[ans]) ans = i;
	}
	return ans;
}


/*
 * Convex Hull
 */

point pivot(0, 0);

bool angleCmp(point a, point b) {
	if (collinear(pivot, a, b))
		return inner(pivot-a, pivot-a) < inner(pivot-b, pivot-b);
	return cross(a-pivot, b-pivot) >= 0;
}

polygon convexHull(vector<point> P) {
	int i, j, n = (int)P.size();
	if (n <= 2) return P;
	int P0 = leftmostIndex(P);
	swap(P[0], P[P0]);
	pivot = P[0];
	sort(++P.begin(), P.end(), angleCmp);
	vector<point> S;
	S.push_back(P[n-1]);
	S.push_back(P[0]);
	S.push_back(P[1]);
	for(i = 2; i < n;) {
		j = (int)S.size()-1;
		if (ccw(S[j-1], S[j], P[i])) S.push_back(P[i++]);
		else S.pop_back();
	}
	reverse(S.begin(), S.end());
	S.pop_back();
	reverse(S.begin(), S.end());
	return S;
}

/*
 * Codeforces 101657C
 */

point proj(point u, point v) {
	return v*(inner(u, v)/inner(v, v));
}

#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define INF 1e+55

int main() {
	int T;
	scanf("%d", &T);
	FOR1(caseNo, T) {
		int N;
		scanf("%d", &N);
		vector<point> arr(N);
		FOR(i, N) {
			scanf("%lf %lf", &arr[i].x, &arr[i].y);
		}
		polygon ch = convexHull(arr);
		vector<double> h(ch.size());
		int sz = ch.size();
		FOR(i, sz) {
			h[i] = 0;
			point v = ch[(i+1)%sz] - ch[i];
			for(point& p : ch) {
				point dp = p - ch[i];
				point d = dp - proj(dp, v);
				h[i] = max(h[i], d.norm());
			}
		}
		double ans = INF;
		FOR(i, sz) {
			FOR(j, sz) {
				if (i == j) continue;
				point v1 = ch[(i+1)%sz] - ch[i];
				point v2 = ch[(j+1)%sz] - ch[j];
				double sintheta = fabs(cross(v1, v2) / (v1.norm()*v2.norm()));
				if (fabs(sintheta) < EPS) continue;
				ans = min(ans, h[i]*h[j]/sintheta);
			}
		}
		printf("Swarm %d Parallelogram Area: %.4f\n", caseNo, ans);
	}
	return 0;
}
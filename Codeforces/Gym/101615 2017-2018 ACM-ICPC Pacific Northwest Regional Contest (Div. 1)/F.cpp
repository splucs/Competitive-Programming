#include <bits/stdc++.h>
#define MAXN 309
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define EPS 1e-9
#define FOR(x,n) for(int x=0; x<n; x++)
#define FOR1(x,n) for(int x=1; x<=n; x++)
#define REP(x,n) for(int x=n-1; x>=0; x--)
#define REP1(x,n) for(int x=n; x>0; x--)
#define pb push_back
#define sz(x) ((int)x.size())
#define all(x) x.begin(),x.end()
#define mset(x, y) memset(&x, y, sizeof x)
using namespace std;
typedef pair<int,int> ii;
typedef long long ll;
typedef vector<int> vi;

struct dist {
	const double d2;
	dist(double dx, double dy) : d2(dx*dx + dy*dy) {}
};

bool operator < (dist a, dist b) {
	if (fabs(a.d2-b.d2) < EPS) return false;
	return a.d2 < b.d2;
}

bool operator == (dist a, dist b) {
	return (fabs(a.d2-b.d2) < EPS);
}

struct point {
	double x, y;
	point() : x(double()), y(double()) {}
	point(double _x, double _y) : x(_x), y(_y) {}
	point operator +(point o) {
		return point(x+o.x, y+o.y);
	}
	point operator -(point o) {
		return point(x-o.x, y-o.y);
	}
	bool operator == (point o) {
		return (x == o.x) && (y == o.y);
	}
	point operator *(double k) {
		return point(x*k, y*k);
	}
	point rotate() {
		return point(double()-y, x);
	}
};

bool operator <(point a, point b) {
	if (!(a.x == b.x)) return a.x < b.x;
	return a.y < b.y;
}

double cross(point a, point b) {
	return a.x*b.y - a.y*b.x;
}

bool parallel(point p, point q) {
	return (fabs(cross(p, q)) < EPS);
}

bool collinear(point a, point b, point c) {
	return parallel(a-b, c-a);
}

point lineIntersect(point p, point q, point A, point B) {
	double c = cross(A-B, p-q);
	double a = cross(A, B);
	double b = cross(p, q);
	return ((p-q)*(a/c)) - ((A-B)*(b/c));
}

point read() {
	ll x, y;
	scanf("%lld %lld", &x, &y);
	return point(double(x), double(y));
}

int simulate(vector<point> &P, point q) {
	//printf("circle at (%lld/%lld,%lld/%lld)\n", q.x.x, q.x.y, q.y.x, q.y.y);
	//printf("circle at %.3f,%.3f\n", q.x, q.y);

	set<dist> alld;
	for(point p : P) {
		double dx = q.x - p.x;
		double dy = q.y - p.y;
		dist cur(dx, dy);
		//printf("dist %lld/%lld, %lld/%lld\n", cur.dx.x, cur.dx.y, cur.dy.x, cur.dy.y);
		alld.insert(dist(dx, dy));
	}

	//printf("%d distinct values\n", sz(alld));
	return alld.size();
}

int main() {
	int n;
	while(scanf("%d", &n) != EOF) {
		vector<point> P;
		set<point> Q;
		FOR(i, n) P.pb(read());

		FOR(i, n) {
			FOR(j, n) {
				FOR(k, n) {
					FOR(l, n) {
						point m1 = (P[i]+P[j])*0.5;
						point m2 = (P[k]+P[l])*0.5;
						point d1 = (P[i]-P[j]).rotate();
						point d2 = (P[k]-P[l]).rotate();
						if (parallel(d1, d2)) continue;
						Q.insert(lineIntersect(m1, m1+d1, m2, m2+d2));
					}
				}
				Q.insert((P[i]+P[j])*0.5);
			}
			Q.insert(P[i]);
		}
		
		int ans = max(n-1, 1);
		//Q.clear(); Q.pb(point());
		for(point q : Q) {
			ans = min(ans, simulate(P, q));
		}

		printf("%d\n", ans);
	}
	return 0;
}
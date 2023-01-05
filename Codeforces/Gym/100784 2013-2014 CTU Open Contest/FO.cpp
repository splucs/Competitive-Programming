#include <bits/stdc++.h>
using namespace std;
#define MAXN 10009
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define fi first
#define se second
#define sz(x) int(x.size())
#define all(x) x.begin(),x.end()
#define mset(x, y) memset(&x, y, sizeof x)
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;

struct point {
	ll x, y;
	point(ll _x = 0, ll _y = 0) : x(_x), y(_y) {}
	bool operator < (point other) const {
		if (x == other.x) return y < other.y;
		else return x < other.x;
	}
	point operator -(point other) const {
		return point(x-other.x, y-other.y);
	}
	double norm() {
		return hypot(1.0*x, 1.0*y);
	}
};

double dist(point a, point b) {
	return hypot(a.x - 1.0*b.x, a.y - 1.0*b.y);
}

ll inner(point a, point b) {
	return a.x*b.x + a.y*b.y;
}

ll cross(point a, point b) {
	return a.x*b.y - a.y*b.x;
}

bool ccw(point p, point q, point r) {
	return cross(q-p, r-p) > 0;
}

bool collinear(point a, point b, point c) {
	return cross(a-c, b-c) == 0;
}

int leftmostIndex(vector<point> P) {
	int ans = 0;
	FOR(i, sz(P)) {
		if (P[i] < P[ans]) ans = i;
	}
	return ans;
}

typedef vector<point> polygon;

point pivot(0,0);

bool angleCmp(point a, point b) {
	if (collinear(pivot, a, b))
		return inner(pivot-a, pivot-a) < inner(pivot-b, pivot-b);
	return cross(a-pivot, b-pivot) >= 0;
}

polygon convexHull(vector<point> P) {
	int n = P.size();
	if (n <= 2) return P;
	swap(P[0], P[leftmostIndex(P)]);
	pivot = P[0];
	sort(++all(P), angleCmp);
	polygon S;
	S.pb(P[n-1]);
	S.pb(P[0]);
	S.pb(P[1]);
	for(int i = 2; i < n;) {
		int j = sz(S)-1;
		if (ccw(S[j-1], S[j], P[i])) S.pb(P[i++]);
		else S.pop_back();
	}
	reverse(all(S));
	S.pop_back();
	reverse(all(S));
	return S;
}

int n;

point read() {
	ll x, y;
	scanf("%lld %lld", &x, &y);
	return point(x, y);
}

int main() {
	while(scanf("%d", &n) != EOF) {
		polygon P;
		FOR(i, n) P.pb(read());

		bool allcollinear = true;
		FOR(i, n) {
			if (!collinear(P[0], P[1], P[i])) allcollinear = false;
		}
		if (allcollinear) {
			double ans = 0;
			pivot = P[leftmostIndex(P)];
			sort(all(P), angleCmp);
			FOR(i, n) ans = max(ans, 2*dist(P[i], pivot));
			printf("%.20f\n", ans);
			continue;
		}

		P = convexHull(P);
		n = P.size();
		double ans = 1e100;
		int i = 0, j = 2, p = 1, q = 2;
		for(; i < n; i++) {
			if ((i+1)%n == j) j = (j+1)%n;
			point d = P[(i+1)%n] - P[i];
			while (cross(d, P[(j+1)%n]-P[i]) > cross(d, P[j]-P[i])) {
				if (j == q) q = (q+1)%n;
				j = (j+1)%n;
			}
			while (inner(d, P[(p+1)%n]-P[i]) > inner(d, P[p]-P[i]))
				p = (p+1)%n;
			while (inner(d, P[(q+1)%n]-P[i]) < inner(d, P[q]-P[i]))
				q = (q+1)%n;
			double cur = cross(d, P[j]-P[i]) + inner(d, P[p]-P[i]) - inner(d, P[q]-P[i]);
			cur /= d.norm();
			ans = min(ans, 2*cur);
		}
		printf("%.20f\n", ans);
	}
	return 0;
}
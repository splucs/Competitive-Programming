#include <cmath>
#include <algorithm>
#define MAXN 100309
#define INF 1e+30
using namespace std;

/*
 * Closest point problem
 */

struct point {
    double x, y;
    point() { x = y = 0; }
    point(double _x, double _y) : x(_x), y(_y) {}
};

typedef pair<point, point> pp;

double dist(pp p) {
	double dx = p.first.x - p.second.x;
	double dy = p.first.y - p.second.y;
	return hypot(dx, dy);
}

point strip[MAXN];

pp closest(point *P, int l, int r) {
	if (r == l) return pp(point(INF, 0), point(-INF, 0));
	int m = (l + r) / 2, s1 = 0, s2;
	int midx = (P[m].x + P[m+1].x)/2;
	pp pl = closest(P, l, m);
	pp pr = closest(P, m+1, r);
	pp ans = dist(pl) > dist(pr) ? pr : pl;
	double d = dist(ans);
	for(int i = l; i <= m; i++) {
		if (midx - P[i].x < d) strip[s1++] = P[i];
	}
	s2 = s1;
	for(int i = m+1; i <= r; i++) {
		if (P[i].x - midx < d) strip[s2++] = P[i];
	}
	for(int j = 0, s = s1; j < s1; j++) {
		point p = strip[j];
		for(int i = s; i < s2; i++) {
			point q = strip[i];
			pp cur = pp(p, q);
			double dcur = dist(cur);
			if (d > dcur) {
				ans = cur; d = dcur;
			}
			if (q.y - p.y > d) break;
			if (p.y - q.y > d) s = i+1;
		}
	}
	int i = l, j = m+1, k = l;
	while(i <= m && j <= r) {
		if (P[i].y < P[j].y) strip[k++] = P[i++];
		else strip[k++] = P[j++];
	}
	while(i <= m) strip[k++] = P[i++];
	for(i = l; i < k; i++) P[i] = strip[i];
	return ans;
}

bool compx(point a, point b) {
    return a.x < b.x;
}

pp closest(point *P, int n){
	sort(P, P+n, compx);
	return closest(P, 0, n-1);
}

/*
 * Codeforces 101707F
 */
#include <cstdio>

point P[MAXN];
int n;

int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%lf %lf", &P[i].x, &P[i].y);
	pp ans = closest(P, n);
	printf("%.0f %.0f\n", ans.first.x, ans.first.y);
	printf("%.0f %.0f\n", ans.second.x, ans.second.y);
	return 0;
}
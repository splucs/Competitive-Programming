#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(),x.end()
#define sz(x) int(x.size())
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
typedef long long ll;

struct point {
	ll x, y;
	point(ll _x, ll _y) : x(_x), y(_y) {}
	point operator -(point o) const {
		return point(x - o.x, y - o.y);
	}
	ll oil;
};

ll cross(point a, point b) {
	return a.x*b.y - a.y*b.x;
}

bool operator < (point a, point b) {
	ll cr = cross(a, b);
	if (cr != 0) return cr > 0;
	return a.oil > b.oil;
}

void add(point p0, point p1, vector<point> &P, ll oil) {
	if (p0.y == 0) return;
	if (p0.y < 0) {
		p0.y *= -1; p0.x *= -1;
		p1.y *= -1; p1.x *= -1;
	}
	if (p0.x < p1.x) swap(p0, p1);
	p0.oil = abs(oil);
	p1.oil = -abs(oil);
	P.pb(p0);
	P.pb(p1);
}

ll compute(vector<point> &P) {
	sort(all(P));
	ll ans = 0, cur = 0;
	for(point p : P) {
		cur += p.oil;
		ans = max(ans, cur);
	}
	return ans;
}

ll compute(int i, int n, bool left, vector<point> &P0, vector<point> &P1) {
	point pivot = left ? P0[i] : P1[i];
	vector<point> P;
	FOR(j, n) {
		if (i == j) continue;
		add(P0[j] - pivot, P1[j] - pivot, P, P0[j].oil);
	}
	return P0[i].oil + compute(P); 
}

int main() {
	int n;
	vector<point> P0, P1;
	scanf("%d", &n);
	FOR(i, n) {
		ll x0, x1, y;
		scanf("%lld %lld %lld", &x0, &x1, &y);
		point p0(x0, y), p1(x1, y);
		p0.oil = p1.oil = abs(x0-x1);
		P0.pb(p0);
		P1.pb(p1);
	}
	ll ans = 0;
	FOR(i, n) {
		ans = max(ans, compute(i, n, false, P0, P1));
		ans = max(ans, compute(i, n, true, P0, P1));
	}
	printf("%lld\n", ans);
	return 0;
}

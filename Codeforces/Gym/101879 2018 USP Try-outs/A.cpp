#include <bits/stdc++.h>
#define FOR(x,n) for(int x=0;x<n;x++)
using namespace std;
#define MAXN 100009
#define mp make_pair
#define pb push_back
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define fi first
#define se second
typedef long long ll;

struct point {
	ll x, y;
	point() {}
	point(ll x, ll y) : x(x), y(y) {}
};

point operator -(point a, point b) {
	return point(a.x-b.x, a.y-b.y);
}

ll cross(point a, point b) {
	return a.x*b.y - a.y*b.x;
}

bool ccw(point a, point b, point c) {
	return cross(b-a, c-b) > 0;
}

point rotate(point a) {
	return point(a.y, -a.x);
}

struct tg {
	ll x, y;
	tg(point p) {
		x = p.x;
		y = p.y;
		if (x < 0) {
			x *= -1; y *= -1;
		}
	}
};

bool operator < (tg a, tg b) {
	if (a.x == 0 && b.x == 0) {
		if (a.y*b.y < 0) return a.y < b.y;
		return false;
	}
	if (a.x == 0) return a.y < 0;
	if (b.x == 0) return b.y > 0;
	return a.y*b.x < a.x*b.y;
}

bool operator == (tg a, tg b) {
	return !(a<b) && !(b<a);
}

tg pinf(point(0, 1));
tg minf(point(0, -1));
vector< pair<tg,tg> > s;
bool vertical = true;
bool allforbidden = false;

void add_restriction(point a, point b) {
	//assert(cross(a, b) > 0);
	//printf("adding restriction (%lld,%lld), (%lld,%lld)\n", a.x, a.y, b.x, b.y);
	tg tga(a), tgb(b);
	if (tgb == tga) return;
	if (tgb < tga) {
		if (tga < pinf) {
			s.pb(mp(tga, pinf));
			//printf("added restriction (%.3f,%.3f)\n", atan2(tga.y, tga.x), atan2(pinf.y, pinf.x));
		}
		if (minf < tgb) {
			 s.pb(mp(minf, tgb));
			//printf("added restriction (%.3f,%.3f)\n", atan2(minf.y, minf.x), atan2(tgb.y, tgb.x));
		}
		vertical = false;
	}
	else {
		s.pb(mp(tga, tgb));
		//printf("added restriction (%.3f,%.3f)\n", atan2(tga.y, tga.x), atan2(tgb.y, tgb.x));
	}
}

set<tg> manual;

void process(vector<point> P) {
	int n = P.size();
	FOR(j, n) {
		int i = (j-1+n)%n;
		int k = (j+1)%n;
		if (ccw(P[i], P[j], P[k])) {
			rotate(P.begin(), P.begin()+j, P.end());
			break;
		}
	}
	s.clear();
	FOR(j, n) {
		int i = (j-1+n)%n;
		int k = (j+1)%n;
		if (!ccw(P[i], P[j], P[k])) {
			add_restriction(P[k]-P[j], P[j]-P[i]);
			int it = (i+1+n)%n;
			int jt = (j+1+n)%n;
			int kt = (k+1+n)%n;
			if (!ccw(P[it], P[jt], P[kt])) {
				tg q(P[k]-P[j]);
				manual.insert(tg(P[k]-P[j]));
				//printf("added restriction [%.3f,%.3f]\n", atan2(q.y, q.x), atan2(q.y, q.x));
				q = tg(P[j]-P[k]);
				manual.insert(tg(P[k]-P[j]));
				//printf("added restriction [%.3f,%.3f]\n", atan2(q.y, q.x), atan2(q.y, q.x));
			}
		}
	}
}

void fix_restrictions() {
	sort(all(s));
	vector< pair<tg,tg> > in;
	for(auto pp : s) {
		if (!in.empty() && pp.fi < in.back().se) {
			in.back().se = max(in.back().se, pp.se);
		}
		else in.pb(pp);
	}
	s.swap(in);
}

bool query(point pq) {
	tg q(rotate(pq));
	//printf("query %.3f\n", atan2(q.y, q.x));
	if (q.x == 0) return vertical;
	if (manual.count(q)) return false;
	int i = lower_bound(all(s), mp(q, q)) - s.begin();
	i-=2;
	i = max(i, 0);
	FOR(k, 5) {
		if (i >= sz(s)) break;
		if (s[i].fi < q && q < s[i].se) return false;
		i++;
	}
	return true;
}

point read() {
	int x, y;
	scanf("%d %d", &x, &y);
	return point(x, y);
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	vector<point> P;
	FOR(i, n) P.pb(read());
	process(P);
	fix_restrictions();
	FOR(j, m) printf("%c\n", query(read()) ? 'Y' : 'N');
	return 0;
}
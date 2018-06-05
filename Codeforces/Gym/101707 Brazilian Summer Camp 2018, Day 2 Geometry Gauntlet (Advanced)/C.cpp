#include <bits/stdc++.h>
#define EPS 1e-9
using namespace std;

typedef long long ll;

struct point {
	int id;
	ll x, y;
	point() { x = y = 0.0; }
	point(ll _x, ll _y) : x(_x), y(_y) {}
	bool operator < (point other) const {
		if (x != other.x) return x < other.x;
		else return y < other.y;
	}
	bool operator == (point other) const {
		return x == other.x && y == other.y;
	}
	point operator +(point other) const{
		return point(x + other.x, y + other.y);
	}
	point operator -(point other) const{
		return point(x - other.x, y - other.y);
	}
	point operator *(ll k) const{
		return point(x*k, y*k);
	}
};

ll inner(point p1, point p2) {
	return p1.x*p2.x + p1.y*p2.y;
}

double dist(point p1, point p2) {
	return hypot(p1.x - 1.0*p2.x, p1.y - 1.0*p2.y);
}

ll cross(point p1, point p2) {
	return p1.x*p2.y - p1.y*p2.x;
}

bool ccw(point p, point q, point r) {
	return cross(q-p, r-p) > 0LL;
}

bool collinear(point p, point q, point r) {
	return cross(p-q, r-p) == 0LL;
}

int leftmostIndex(vector<point> &P){
	int ans = 0;
	for(int i=1; i<(int)P.size(); i++){
		if (P[i] < P[ans]) ans = i;
	}
	return ans;
}
point pivot(0, 0);

bool angleCmp(point a, point b) {
	if (collinear(pivot, a, b)) return inner(pivot-a, pivot-a) < inner(pivot-b, pivot-b);
	return cross(a-pivot, b-pivot) >= 0;
}

vector<point> convexHull(vector<point> P){
	int i, j, n = (int)P.size();
	if (n <= 2){
		if (!(P[0] == P[n-1])) P.push_back(P[0]);
		return P;
	}
	int P0 = leftmostIndex(P);
	swap(P[0], P[P0]);
	pivot = P[0];
	sort(++P.begin(), P.end(), angleCmp);
	vector<point> S;
	S.push_back(P[n-1]);
	S.push_back(P[0]);
	S.push_back(P[1]);
	i = 2;
	while(i < n){
		j = (int)S.size()-1;
		if (ccw(S[j-1], S[j], P[i])) S.push_back(P[i++]);
		else S.pop_back();
	}
	return S;
}

struct StableSum {
	int cnt = 0;
	vector<double> v, pref{0};
	void operator += (double a) { // a >= 0
		for (int s = ++cnt; s % 2 == 0; s >>= 1) {
			a += v.back();
			v.pop_back(), pref.pop_back();
		}
		v.push_back(a);
		pref.push_back(pref.back() + a);
	}
	double val(int i) { return pref[i]; }
	double val() { return pref.back(); }
};

double perimeter(vector<point> P) {
	StableSum ans;
	int n = P.size();
	for(int i = 0; i < n; i++) {
		ans += dist(P[i], P[(i+1)%n]);
	}
	return ans.val();
}

ll area(vector<point> P) {
	ll ans = 0;
	int n = P.size();
	for(int i = 0; i < n; i++) {
		ans += cross(P[i], P[(i+1)%n] - P[i]);
	}
	return abs(ans);
}

#define MAXN 2000009

int main() {
	int n;
	scanf("%d", &n);
	vector<point> P;
	for(int i = 0; i < n; i++) {
		point p;
		scanf("%lld %lld", &p.x, &p.y);
		p.id = i+1;
		P.push_back(p);
	}
	vector<point> ch = convexHull(P);
	ch.pop_back();
	printf("%u\n", ch.size());
	for(int i = 0; i < (int)ch.size(); i++) {
		printf("%d ", ch[i].id);
	}
	ll ar = area(ch);
	if (ar % 2 == 0) printf("\n%.12f\n%lld.0\n", perimeter(ch), ar/2);
	else printf("\n%.12f\n%lld.5\n", perimeter(ch), ar/2);
	return 0;
}
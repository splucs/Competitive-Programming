#include <bits/stdc++.h>
using namespace std;
#define EPS 1e-9
#define INF 1e+18

typedef long long ll;

struct point {
	ll x, y;
	point() { x = y = 0; }
	point(ll _x, ll _y) : x(_x), y(_y) {}
};

bool equal(point a, point b) {
	return a.x == b.x && a.y == b.y;
}

ll gcd(ll x, ll y) {
	if (y == 0) return x;
	return gcd(y, x%y);
}

struct line {
	ll a, b, c;
	line() { a = b = c = 0; }
	line(ll _a, ll _b, ll _c) : a(_a), b(_b), c(_c) {}
	bool operator < (line o){
		if (a!=o.a) return a<o.a;
		if (b!=o.b) return b<o.b;
		return c<o.c;
	}
	bool operator == (line o) {
		return a==o.a && b==o.b && c==o.c;
	}
};

line pointsToLine(point p1, point p2) {
	line l;
	l.a = p2.y-p1.y;
	l.b = p1.x-p2.x;
	l.c = p1.y*p2.x - p1.x*p2.y;
	if (l.c < 0) {
		l.c = -l.c;
		l.a = -l.a;
		l.b = -l.b;
	}
	else if (l.c == 0 && l.b < 0) {
		l.c = -l.c;
		l.a = -l.a;
		l.b = -l.b;
	}
	else if (l.c == 0 && l.b == 0 && l.a < 0) {
		l.c = -l.c;
		l.a = -l.a;
		l.b = -l.b;
	}
	ll g = gcd(abs(l.c), gcd(abs(l.b), abs(l.a)));
	l.a /= g;
	l.b /= g;
	l.c /= g;
	return l;
}

vector<line> L;
line mostcommon(const vector<point> & P) {
	int n = P.size();
	L.clear();
	for(int i=0; i<n; i++) {
		for(int j=0; j<i; j++) {
			if (equal(P[i], P[j])) continue;
			else L.push_back(pointsToLine(P[i], P[j]));
		}
	}
	sort(L.begin(), L.end());
	if (L.empty()) return pointsToLine(P[0], point());
	line ans = L[0];
	int cnt = 1, mx = 1;
	for(int i=1; i-1<(int)L.size(); i++) {
		if (i<(int)L.size() && L[i] == L[i-1]) {
			cnt++;
		}
		else {
			if (cnt > mx) {
				ans = L[i-1];
				mx = cnt;
			}
			cnt = 1;
		}
	}
	return ans;
}

#define MAXN 500009
int N, P, minp;
point arr[MAXN];

bool check(line l) {
	int ans = 0;
	for(int i=0; i<N; i++) {
		if (l.a*arr[i].x + l.b*arr[i].y + l.c == 0) ans++;
	}
	return ans >= minp;
}

int main() {
	scanf("%d %d", &N, &P);
	minp = N*P;
	if (minp % 100 == 0) minp /= 100;
	else minp = minp/100 + 1;
	
	for(int i=0; i<N; i++) {
		scanf("%I64d %I64d", &arr[i].x, &arr[i].y);
	}
	
	bool ok = false;
	vector<point> P(1009);
	for(int k=0; k<10 && !ok; k++) {
		random_shuffle(arr, arr+N);
		P.clear();
		for(int i=0; i<100 && i<N; i++) {
			P.push_back(arr[i]);
		}
		line cur = mostcommon(P);
		ok = check(cur);
	}
	
	if (ok) printf("possible\n");
	else printf("impossible\n");
	return 0;
}
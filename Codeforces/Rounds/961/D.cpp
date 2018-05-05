#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define MAXM 320
#define MOD 1000000007
#define INF 1000000009
#define EPS 1e-7
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;

struct point {
	ll x, y;
	point(): x(0), y(0) {}
	point(ll _x, ll _y) : x(_x), y(_y) {}
	point operator - (point o) {
		return point(x-o.x, y-o.y);
	}
};

ll cross(point a, point b) {
	return a.x*b.y - a.y*b.x;
}

bool collinear(point a, point b, point c) {
	return cross(c-a, b-a) == 0;
}

struct line {
	point a, b;
	line() : a(point()), b(point()) {}
	line(point _a, point _b) : a(_a), b(_b) {}
	bool inside(point c) {
		return collinear(a, b, c);
	}
};

point arr[MAXN];
int N;

bool checklines(line a, line b) {
	FOR(i, N) {
		if (!a.inside(arr[i]) && !b.inside(arr[i])) return false;
	}
	return true;
}

int main() {
	scanf("%d", &N);
	FOR(i, N) {
		scanf("%I64d %I64d", &arr[i].x, &arr[i].y);
	}
	bool ok = false;
	point p[4];
	p[0] = arr[0];
	p[1] = arr[1];
	line l[6];
	int k = 0;
	l[k++] = line(p[0], p[1]);
	FOR(i, N) {
		bool col = false;
		FOR(j, k) {
			if (l[j].inside(arr[i])) col = true;
		}
		if (!col) {
			p[2] = arr[i];
			l[k++] = line(p[0], p[2]);
			l[k++] = line(p[1], p[2]);
			break;
		}
	}
	if (k == 1) ok = true;
	else {
		FOR(i, N) {
			bool col = false;
			FOR(j, k) {
				if (l[j].inside(arr[i])) col = true;
			}
			if (!col) {
				p[3] = arr[i];
				l[k++] = line(p[0], p[3]);
				l[k++] = line(p[1], p[3]);
				l[k++] = line(p[2], p[3]);
				break;
			}
		}
		FOR(i, k) FOR(j, k) {
			if (checklines(l[i], l[j])) ok = true;
		}
	}

	if (ok) printf("YES\n");
	else printf("NO\n");
	return 0;
}
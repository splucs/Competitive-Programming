#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

typedef long long ll;

ll gcd(ll x, ll y) {
	if (y == 0) return x;
	return gcd(y, x%y);
}

struct point {
	ll x, y;
} pts[MAXN];

struct line {
	ll a, b, c;
	line(ll x1, ll y1, ll x2, ll y2) {
		a = y1 - y2;
		b = x2 - x1;
		c = y2*x1 - y1*x2;
		ll g = gcd(abs(c), gcd(abs(a), abs(b)));
		a /= g;
		b /= g;
		c /= g;
		if (a < 0 || (a==0 && b < 0)) {
			a = -a;
			b = -b;
			c = -c;
		}
	}
	bool contains(point p) {
		return a*p.x + b*p.y + c == 0;
	}
};

bool parallel(line l1, line l2) {
	return l1.a==l2.a && l1.b==l2.b;
}

int main() {
	int N;
	scanf("%d", &N);
	for(int i=1; i<=N; i++) {
		scanf("%I64d", &pts[i].y);
		pts[i].x = i;
	}
	bool ok = false;
	for(int s=1; s<=2; s++) {
		for(int i=1; i<=N && !ok; i++) {
			if (i == s) continue;
			line l1 = line(pts[s].x, pts[s].y, pts[i].x, pts[i].y);
			vector<int> p2;
			for(int j=1; j<=N; j++) {
				if (!l1.contains(pts[j])) {
					p2.push_back(j);
				}
			}
			if (p2.size() == 0u) continue;
			if (p2.size() == 1u) {
				ok = true;
				break;
			}
			line l2 = line(pts[p2.front()].x, pts[p2.front()].y, pts[p2.back()].x, pts[p2.back()].y);
			if (!parallel(l1, l2)) continue;
			ok = true;
			for(int jt=0, j; jt<(int)p2.size() && ok; jt++) {
				j = p2[jt];
				if (!l2.contains(pts[j])) ok = false;
			}
		}
	}
	if (ok) printf("Yes\n");
	else printf("No\n");
	return 0;
}
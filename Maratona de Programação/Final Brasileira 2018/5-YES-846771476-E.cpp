#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
#define EPS 1e-9
#define MAXN 100009
#define FOR(x,n) for(int x=0;x<n;x++)
#define FOR1(x,n) for(int x=1;x<=n;x++)
#define sz(x) int(x.size())
#define mset(x, y) memset(&x, y, sizeof x)
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long int ll;
typedef pair<int, int> ii;

struct point {
	ll x, y;
	point(ll _x=0, ll _y=0) : x(_x), y(_y) {}
	point operator -(point o) {
		return point(x - o.x, y - o.y);
	}
};

ll cross(point a, point b) {
	return a.x*b.y - a.y*b.x;
}

point read() {
	int x, y;
	scanf("%d %d", &x, &y);
	return point(x, y);
}

int main() {
	vector<point> P, Q;
	int n;
	scanf("%d", &n);
	FOR(i, n) P.pb(read());
	FOR(i, n) Q.pb(P[(i+1)%n] - P[i]);
	int j = 0;
	ll ans = n*(n-1ll)*(n-2ll)/6;
	FOR(i, n) {
		while(cross(Q[i], Q[j]) >= 0) j = (j+1)%n;
		int m = (j-i-1+n)%n;
		//printf("i=%d m=%d\n", i, m);
		ans -= m*(m-1LL)/2;
	}
	printf("%lld\n", ans);
	return 0;
}

/*
i=0, j=5, l = 4, r = 3
i=1, j=6, l = 4, r = 3
i=2, j=0, l = 5, r = 2
i=3, j=0, l = 4, r = 3
i=4, j=0, l = 3, r = 4
i=5, j=1, l = 3, r = 4
i=6, j=2, l = 3, r = 4
i=7, j=2, l = 2, r = 5

*/

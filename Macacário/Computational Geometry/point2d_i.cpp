typedef long long ll;

struct point_i {
	ll x, y;
	point_i() { x = y = 0; }
	point_i(ll _x, ll _y) : x(_x), y(_y) {}
	bool operator < (point_i other) const {
		if (x != other.x) return x < other.x;
		else return y < other.y;
	}
	bool operator == (point_i other) const {
		return (x == other.x && y == other.y);
	}
};

ll cross(point_i a, point_i b) {
	return a.x*b.y - a.y*b.x;
}

int insideCircle(point_i p, point_i c, int r) {
	ll dx = p.x - c.x, dy = p.y - c.y;
	ll Euc = dx * dx + dy * dy, rSq = r * r;
	return Euc < rSq ? 0 : Euc == rSq ? 1 : 2;
} //0 = inside/1 = border/2 = outside

bool polarCmp(point_i a, point_i b) {
	if (b.y*a.y > 0) return cross(a, b) > 0;
	else if (b.y == 0 && b.x > 0) return false;
	else if (a.y == 0 && a.x > 0) return true;
	else return b.y < a.y;
}

/*
 * TEST MATRIX
 */
#include <cstdio>

int test()
{
	point_i a, b;
	while(scanf("%I64d %I64d %I64d %I64d", &a.x, &a.y, &b.x, &b.y) != EOF) {
		if (polarCmp(a, b)) printf("a < b\n");
		else printf("a >= b\n");
	}
	return 0;
}

/*
 * Codeforces 514B
 */
#include <algorithm>
using namespace std;
#define MAXN 1009
point_i vet[MAXN];

int main() {
	int n, x0, y0, x, y, dx, dy;
	scanf("%d %d %d", &n, &x0, &y0);
	for(int i=0; i<n; i++) {
		scanf("%d %d", &x, &y);
		dx = x - x0;
		dy = y - y0;
		if (dy < 0 || (dy == 0 && dx < 0)) {
			dx *= -1;
			dy *= -1;
		}
		vet[i] = point_i(dx, dy);
	}
	sort(vet, vet+n, &polarCmp);
	int ans = n;
	for(int i=1; i<n; i++) {
		if (!polarCmp(vet[i], vet[i-1]) && !polarCmp(vet[i-1], vet[i])) ans--;
	}
	printf("%d\n", ans);
	return 0;
}
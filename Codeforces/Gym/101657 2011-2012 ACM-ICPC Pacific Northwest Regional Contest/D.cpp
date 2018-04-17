#include <bits/stdc++.h>
using namespace std;
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define MAXN 1000009

struct point {
	double x, y;
	point() : x(0), y(0) {}
	point(int _x, int _y) : x(_x), y(_y) {}
	point operator - (point o) {
		return point(x - o.x, y - o.y);
	}
};

double cross(point p1, point p2) {
	return p1.x*p2.y - p1.y*p2.x;
}

struct triangle {
	int x[3], y[3];
	int maxx() {
		return max(x[0], max(x[1], x[2]));
	}
	int maxy() {
		return max(y[0], max(y[1], y[2]));
	}
	int minx() {
		return min(x[0], min(x[1], x[2]));
	}
	int miny() {
		return min(y[0], min(y[1], y[2]));
	}
}

triangle arr[MAXN];
int ans[MAXN], aux[MAXN];

void getbasevec(triangle t, point & p1, point & p2) {
	FOR(i, 3) {
		if (tr.minx() == tr.x[i]) p1 = point(tr.x[i], tr.y[i]);
		if (tr.maxx() == tr.x[i]) p2 = point(tr.x[i], tr.y[i]);
	}
}

bool before(int i, int j) {
	const triangle & tr1 = arr[i];
	const triangle & tr2 = arr[j];
	if (tr1.maxx() < tr2.minx()) return false;
	if (tr1.minx() > tr2.maxx()) return false;
	point p1i, p1j, p2i, p2j;
	getbasevec(tr1, p1)
	point ref = point(tr1.minx(), tr1.miny() - 1);
}

void solve(int l, int r) {
	if (l == r) return;
	int mid = (l + r) / 2;
	solve(l, mid);
	solve(mid+1, r);
	int i = l, j = mid+1, k = l;
	while(i <= mid || j <= r) {
		if (before(i, j)) {
			aux[k++] = ans[i++];
		}
		else {
			aux[k++] = ans[j++];
		}
	}
	while(i <= mid) aux[k++] = ans[i++];
	while(j <= r) aux[k++] = ans[j++];
	for(i = l; i <= r; i++) {
		ans[i] = aux[i];
	}
}

bool comp(int i, int j) {
	const triangle & tr1 = arr[i];
	const triangle & tr2 = arr[j];
	return tr1.minx() < tr2.minx();
}

int main() {
	int T;
	scanf("%d", &T);
	FOR1(caseNo, T) {
		int N;
		scanf("%d", &N);
		FOR1(i, N) {
			scanf("%d %d %d %d %d %d",
			&arr[i].x[0], &arr[i].y[0],
			&arr[i].x[1], &arr[i].y[1],
			&arr[i].x[2], &arr[i].y[2]);
			ans[i] = i;
		}
		sort(ans+1, ans+1+N, comp);
		solve(1, N);
		FOR1(i, N) {
			printf("%d ", ans[i]);
		}
		printf("\n");
	}
	return 0;
}
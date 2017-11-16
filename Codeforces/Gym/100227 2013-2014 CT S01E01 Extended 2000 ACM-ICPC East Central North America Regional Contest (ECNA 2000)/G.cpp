#include <bits/stdc++.h>
using namespace std;
#define EPS 1e-9
#define MAXN 200009

struct point {
	double x, y;
	point() { x = y = 0.0; }
	point(double _x, double _y) : x(_x), y(_y) {}
	point operator -(point other) const{
		return point(x - other.x, y - other.y);
	}
};

double cross(point p1, point p2) {
	return p1.x*p2.y - p1.y*p2.x;
}

bool ccw(point p, point q, point r) {
	return cross(q-p, r-p) > 0;
}

int sz, prv, N, l[MAXN], r[MAXN];
vector<int> v[MAXN];
vector<point> pol[MAXN];

void cut(point a, point b) {
	if (a.x > b.x) swap(a, b);
	int aux = sz;
	for(int u=prv; u<aux; u++) {
		l[sz] = -1; r[sz] = -1;
		l[u] = sz++;
		l[sz] = -1; r[sz] = -1;
		r[u] = sz++;
		for(int i=0; i<(int)v[u].size(); i++) {
			point p = pol[v[u][i]][0];
			if (ccw(a, b, p)) v[l[u]].push_back(v[u][i]);
			else v[r[u]].push_back(v[u][i]);
		}
		v[u].clear();
	}
	prv = aux;
}

void dfs(int u) {
	if (u == -1) return;
	for(int i=0; i<(int)v[u].size(); i++) {
		printf("%c", v[u][i] + 'A');
	}
	dfs(l[u]); dfs(r[u]);
}

int main() {
	scanf("%d", &N);
	sz = prv = 0;
	l[sz] = -1; r[sz] = -1;
	double x, y, x1, x2, y1, y2;
	for(int i=0, m; i<N; i++) {
		scanf("%d", &m);
		while(m--) {
			scanf("%lf %lf", &x, &y);
			pol[i].push_back(point(x, y));
		}
		v[0].push_back(i);
	}
	sz++;
	int p;
	scanf("%d", &p);
	while(p--) {
		scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
		cut(point(x1, y1), point(x2, y2));
	}
	dfs(0);
	printf("\n");
	return 0;
}
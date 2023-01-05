#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;
#define EPS 1e-9

/*
 * Point 2D
 */

struct point {
	double x, y;
	point() { x = y = 0.0; }
	point(double _x, double _y) : x(_x), y(_y) {}
	bool operator < (point other) const {
		if (fabs(x - other.x) > EPS) return x < other.x;
		else return y < other.y;
	}
	bool operator == (point other) const {
		return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS));
	}
	point operator +(point other) const {
		return point(x + other.x, y + other.y);
	}
	point operator -(point other) const {
		return point(x - other.x, y - other.y);
	}
	point operator *(double k) const {
		return point(x*k, y*k);
	}
};

double dist(point p1, point p2) {
	return hypot(p1.x - p2.x, p1.y - p2.y);
}

double inner(point p1, point p2) {
	return p1.x*p2.x + p1.y*p2.y;
}

double cross(point p1, point p2) {
	return p1.x*p2.y - p1.y*p2.x;
}

bool collinear(point p, point q, point r) {
	return fabs(cross(p-q, r-p)) < EPS;
}

/*
 * Circle 2D
 */

struct circle {
	point c;
	double r;
	circle() { c = point(); r = 0; }
};

circle circumcircle(point a, point b, point c) {
	circle ans;
	point u = point((b-a).y, -(b-a).x);
	point v = point((c-a).y, -(c-a).x);
	point n = (c-b)*0.5;
	double t = cross(u,n)/cross(v,u);
	ans.c = ((a+c)*0.5) + (v*t);
	ans.r = dist(ans.c, a);
	return ans;
}

/*
 * Delaunay Triangulation
 * http://graphics.stanford.edu/courses/cs368-06-spring/handouts/Delaunay_2.pdf
 */

#include <set>
#include <algorithm>
#define MAXN 200309

struct truple {
	int a, b, c;
	truple(int _a, int _b, int _c) :
		a(_a), b(_b), c(_c) {
		if (a > b) swap(a, b);
		if (a > c) swap(a, c);
		if (b > c) swap(b, c);
	}
};
bool operator < (truple x, truple y) {
	if (x.a != y.a) return x.a < y.a;
	if (x.b != y.b) return x.b < y.b;
	if (x.c != y.c) return x.c < y.c;
	return false;
}

namespace Delaunay {
vector< set<int> > adj;
vector<point> P;
set<truple> tri;
void add_edge(int u, int v, int w = -1) {
	adj[u].insert(v); adj[v].insert(u);
	if (w >= 0) tri.insert(truple(u, v, w));
}
void del_edge(int u, int v) {
	adj[u].erase(v); adj[v].erase(u);
}
void brute(int l, int r) {	
	if (r-l == 2 && collinear(P[l],P[l+1],P[r])) {
		add_edge(l, l+1); add_edge(l+1, r);
		return;
	}
	for(int u = l; u <= r; u++)
		for(int v = u+1; v <= r; v++)
			add_edge(u, v);
	if (r-l == 2) tri.insert(truple(l,l+1,r));
}
double theta[MAXN];
bool comp(int u, int v) {
	return theta[u] < theta[v];
}
vector< vector<int> > g;
bool right; point base;
void computeG(int u, int r = -1) {
	if (!g[u].empty()) return;
	if (r >= 0) adj[u].erase(r);
	g[u] = vector<int>(adj[u].begin(), adj[u].end());
	if (r >= 0) adj[u].insert(r);
	for(int i = 0; i < int(g[u].size()); i++) {
		double co = inner(base, P[g[u][i]]-P[u]);
		double si = cross(base, P[g[u][i]]-P[u]);
		theta[g[u][i]] = atan2(si, co);
	}
	sort(g[u].begin(), g[u].end(), comp);
	if (right) reverse(g[u].begin(), g[u].end());
}
int getNext(int u, int a, int b) {
	right = (u == b);
	base = (right ? P[b]-P[a] : P[a]-P[b]);
	computeG(u, a + b - u);
	int ans = -1, w;
	while(!g[u].empty()) {
		int j = g[u].size() - 1;
		ans = g[u][j];
		if (right && cross(base, P[ans]-P[b]) > -EPS) return -1;
		if (!right && cross(base, P[ans]-P[a]) < EPS) return -1;
		circle c = circumcircle(P[a],P[b],P[ans]);
		if (g[u].size() > 1u && dist(c.c, P[w = g[u][j-1]]) < c.r - EPS) {
			del_edge(u, ans); g[u].pop_back();
			tri.erase(truple(u, w, ans));
		}
		else break;
	}
	return ans;
}
int moveEdge(int & u, int a, int b) {
	right = (b == u); int v = a+b-u;
	for(set<int>::iterator it = adj[u].begin(); it != adj[u].end(); it++) {
		int nu = *it;
		double cr = cross(P[u]-P[v], P[nu]-P[v]);
		if (right && cr > EPS) return u = nu;
		if (!right && cr < -EPS) return u = nu;
		if (fabs(cr) < EPS && dist(P[nu], P[v]) < dist(P[u], P[v])) return u = nu;
	}
	return -1;
}
void delaunay(int l, int r) {
	if (r - l < 3) { brute(l, r); return; }
	int mid = (r + l) / 2;
	delaunay(l, mid); delaunay(mid + 1, r);
	int u = l, v = r, nu, nv;
	double du, dv;
	do {
		nu = moveEdge(u, u, v);
		nv = moveEdge(v, u, v);
	} while (nu != -1 || nv != -1);
	g[u].clear(); g[v].clear();
	add_edge(u, v);
	while(true) {
		nu = getNext(u, u, v); nv = getNext(v, u, v);
		if (nu == -1 && nv == -1) break;
		if (nu != -1 && nv != -1) {
			point nor = point(P[u].y-P[v].y, P[v].x-P[u].x);
			circle cu = circumcircle(P[u],P[v],P[nu]);
			circle cv = circumcircle(P[u],P[v],P[nv]);
			du = inner(cu.c-P[u], nor);
			dv = inner(cv.c-P[v], nor);
		}
		else du = 1, dv = 0;
		if (nu == -1 || du < dv) {
			add_edge(u, nv, v); g[v = nv].clear();
		}
		else if (nv == -1 || du >= dv) {
			add_edge(nu, v, u); g[u = nu].clear();
		}
	}
}
vector< set<int> > compute(vector<point> & Q) {
	sort(Q.begin(), Q.end());
	int n = (P = Q).size();
	adj.clear(); adj.assign(n, set<int>());
	g.clear(); g.assign(n, vector<int>());
	tri.clear();
	delaunay(0, n-1);
	return adj;
}
set<truple> getTriangles() { return tri; }
};

/*
 * TEST MATRIX
 */

#include <cstdio>

int cnt = 0;
void plot2csv(vector<point> P, vector< set<int> > adj) {
	char filename[100];
	int n = P.size();
	sprintf(filename, "graph%d.csv", cnt++);
	FILE * out = fopen(filename, "w");
	fprintf(out, "id,lat,lng\n");
	for(int i = 0; i < n; i++) {
		fprintf(out, "%d,%.2f,%.2f\n", i, P[i].x, P[i].y);
	}
	fprintf(out, "source,target\n");
	for(int u = 0; u < n; u++) {
		for(set<int>::iterator it = adj[u].begin(); it != adj[u].end(); it++) {
			fprintf(out, "%d,%d\n", u, *it);
		}
	}
	fclose(out);
}

typedef pair<int, int> ii;

bool isAllCollinear(vector<point> P) {
	int n = P.size(), id = 0;
	while(id < n && P[0] == P[id]) id++;
	if (id == n) return true;
	for(int i = 0; i < n; i++) {
		if (!collinear(P[0], P[id], P[i])) return false;
	}
	return true;
}

bool between(point p, point q, point r) {
	return collinear(p, q, r) && inner(p - q, r - q) < -EPS;
}

point lineIntersectSeg(point p, point q, point A, point B) {
	double c = cross(A-B, p-q);
	double a = cross(A, B);
	double b = cross(p, q);
	return ((p-q)*(a/c)) - ((A-B)*(b/c));
}

bool parallel(point a, point b) {
	return fabs(cross(a, b)) < EPS;
}

bool segIntersects(point a, point b, point p, point q) {
	if (parallel(a-b, p-q)) {
		return between(a, p, b) || between(a, q, b)
			|| between(p, a, q) || between(p, b, q); 
	}
	point i = lineIntersectSeg(a, b, p, q);
	return between(a, i, b) && between(p, i, q);
}

bool isTriangulation(vector<point> P, vector< set<int> > adj) {
	vector< pair<point, point> > seg;
	set<ii> edges, aux;
	int n = P.size();
	for(int u = 0; u < n; u++) {
		vector<int> g(adj[u].begin(), adj[u].end());
		for(int j = 0; j < (int)g.size(); j++) {
			int v = g[j];
			if (u < v) {
				seg.push_back(make_pair(P[u], P[v]));
				edges.insert(make_pair(u, v));
			}
		}
	}
	set<truple> tri = Delaunay::getTriangles();
	for(set<truple>::iterator it = tri.begin(); it != tri.end(); it++) {
		int u = it->a, v = it->b, w = it->c;
		if (!edges.count(ii(u, v))) {
			printf("error, not a triangulation\n");
			return false;
		}
		else aux.insert(ii(u, v));
		if (!edges.count(ii(v, w))) {
			printf("error, not a triangulation\n");
			return false;
		}
		else aux.insert(ii(v, w));
		if (!edges.count(ii(u, w))) {
			printf("error, not a triangulation\n");
			return false;
		}
		else aux.insert(ii(u, w));
	}
	if (!isAllCollinear(P) && aux.size() != edges.size()) {
		printf("error, not a triangulation\n");
		return false;
	}
	for(int u = 0; u < n; u++) {
		for(int v = 0; v < n; v++) {
			if (u >= v || edges.count(ii(u, v))) continue;
			bool found = false;
			for(int j = 0; !found && j < (int)seg.size(); j++) {
				point p = seg[j].first;
				point q = seg[j].second;
				if (segIntersects(p, q, P[u], P[v])) found = true;
			}
			if (!found) {
				printf("error, not a triangulation\n");
				return false;
			}
		}
	}
	return true;
}

bool isDelaunayTriangulation(vector<point> P, vector< set<int> > adj) {
	int n = P.size();
	if (!isTriangulation(P, adj)) return false;
	set<truple> tri = Delaunay::getTriangles();
	for(set<truple>::iterator it = tri.begin(); it != tri.end(); it++) {
		int u = it->a, v = it->b, w = it->c;
		circle c = circumcircle(P[u], P[v], P[w]);
		for(int i = 0; i < n; i++) {
			if (dist(c.c, P[i]) < c.r - 1e-4) {
				printf("error, point %d = (%.3f,%.3f) is inside circumcircle:\n", i, P[i].x, P[i].y);
				printf("%d = (%.3f,%.3f)\n", u, P[u].x, P[u].y);
				printf("%d = (%.3f,%.3f)\n", v, P[v].x, P[v].y);
				printf("%d = (%.3f,%.3f)\n", w, P[w].x, P[w].y);
				printf("center (%.3f,%.3f), radius %.3f, distance %.3f\n", c.c.x, c.c.y, c.r, dist(c.c, P[i]));
				return false;
			}
		}
	}
	return true;
}

bool inputTest() {
	int n;
	if(scanf("%d", &n) == EOF) return false;
	if (n <= 0) return false;
	vector<point> P(n);
	for(int i = 0; i < n; i++) {
		scanf("%lf %lf", &P[i].x, &P[i].y);
	}
	vector< set<int> > adj = Delaunay::compute(P);
	if(!isDelaunayTriangulation(P, adj)) return false;
	printf("input test passed\n");
	return true;
}

#include <ctime>
typedef pair<int, int> ii;

bool agnezCornerCase(int n, bool testtri) {
	printf("test Victor Agnez's corner case, ");
	vector<point> P;
	for(int i = 0; i < n; i++) {
		P.push_back(point(i / 2, i % 2));
	}
	clock_t last = clock();
	vector< set<int> > adj = Delaunay::compute(P);
	double t = (clock() - last)*1.0/CLOCKS_PER_SEC;
	printf("time %.3fs ", t);
	if(testtri && !isDelaunayTriangulation(P, adj)) {
		printf("failed\n");
		return false;
	}
	printf("ok\n");
	return true;
}

bool test(int lowtest, int hightest, bool testtri) {
	agnezCornerCase(hightest, testtri);
	srand(time(NULL));
	for(int suit = lowtest; suit <= hightest; suit++) {
		printf("test %d, ", suit);
		int n = suit;
		set<ii> inuse;
		while(inuse.size() < n) {
			inuse.insert(ii(rand()%MAXN, rand()%MAXN));
		}
		vector<point> P;
		for(set<ii>::iterator it = inuse.begin(); it != inuse.end(); it++) {
			P.push_back(point(it->first, it->second));
		}
		clock_t last = clock();
		vector< set<int> > adj = Delaunay::compute(P);
		double t = (clock() - last)*1.0/CLOCKS_PER_SEC;
		printf("time %.3fs ", t);
		if(testtri && !isDelaunayTriangulation(P, adj)) {
			printf("failed test %d\n", suit);
			return false;
		}
		printf("ok\n");
		//plot2csv(P, adj);
	}
	if (testtri) printf("all tests passed\n");
	return true;
}

int main() {
	test(1, 100, true);
	return 0;
}

/*
 * http://wcipeg.com/problem/ccc08s2p6
 */
/*
int main() {
	int n;
	while(scanf("%d", &n) != EOF) {
		vector<point> P(n);
		for(int i = 0; i < n; i++) {
			scanf("%lf %lf", &P[i].x, &P[i].y);
		}
		Delaunay::compute(P);
		double ans = 0;
		set<truple> tri = Delaunay::getTriangles();
		for(set<truple>::iterator it = tri.begin(); it != tri.end(); it++) {
			int u = it->a, v = it->b, w = it->c;
			circle c = circumcircle(P[u], P[v], P[w]);
			if (c.r > ans) ans = c.r;
		}
		printf("%.8f\n", ans);
	}
	return 0;
}
*/
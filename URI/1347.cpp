#include <bits/stdc++.h>
using namespace std;
#define MAXN 2009
#define INF 1e+18
#define EPS 1e-9

struct point {
	double x, y;
	point() { x = y = 0.0; }
	point(double _x, double _y) : x(_x), y(_y) {}
	bool operator < (point other) const {
		if (x == other.x) return x < other.x;
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
	point operator *(double k) const{
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

bool between(point p, point q, point r) {
    return collinear(p, q, r) && inner(p - q, r - q) < -EPS;
}

bool lineIntersectSeg(point p, point q, point A, point B) {
	if (fabs(cross(p-q, A-B)) < EPS) return false;
	double a = B.y - A.y;
	double b = A.x - B.x;
	double c = B.x * A.y - A.x * B.y;
	double u = abs(a * p.x + b * p.y + c);
	double v = abs(a * q.x + b * q.y + c);
	point inter = point(p.x * v + q.x * u, p.y * v + q.y * u)*(1.0/(u+v));
	return between(A, inter, B);
}

typedef pair<point, point> pp;
vector<pp> seg;
int N, M, L, cnt;
point nds[MAXN];

bool checkseg(point p, point q) {
	for(int i=0; i<(int)seg.size(); i++) {
		if (lineIntersectSeg(p, q, seg[i].first, seg[i].second)) return false;
	}
	return true;
}

bool clearseg(point p, point q) {
	if (!checkseg(p, q)) return false;
	for(int i=0; i<cnt; i++) {
		if (between(p, nds[i], q)) return false;	
	}
	return true;
}

bool teleport[MAXN];
double pdist[MAXN][MAXN];
bool pclear[MAXN][MAXN];
typedef pair<double, int> ii;
vector<ii> adjList[MAXN*59];
double ddist[MAXN*59];

double dijkstra(int s, int t) {
	for(int i=0; i<cnt*(N+1); i++) ddist[i] = INF;
	ddist[s]=0;
	set<ii> nodes;
	nodes.insert(ii(0.0, s));
	while(!nodes.empty()){
		int u = nodes.begin()->second;
		nodes.erase(nodes.begin());
		for(int i=0; i<(int)adjList[u].size(); i++){
			int v = adjList[u][i].second;
			double w = adjList[u][i].first;
			if (ddist[v] > ddist[u] + w){
				if (ddist[v] < INF){
					nodes.erase(ii(ddist[v], v));
				}
				ddist[v] = ddist[u] + w;
				nodes.insert(ii(ddist[v], v));
			}
		}
	}
	return ddist[t];
}

int main() {
	while(scanf("%d %d %d", &N, &M, &L), N || M || L) {
		seg.clear();
		cnt = 0;
		double x1, y1, x2, y2;
		for(int j=0; j<M; j++) {
			scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
			seg.push_back(pp(point(x1, y1), point(x2, y2)));
			teleport[cnt] = false;
			nds[cnt++] = point(x1, y1);
			teleport[cnt] = false;
			nds[cnt++] = point(x2, y2);
		}
		for(int i=0; i<L; i++) {
			scanf("%lf %lf", &x1, &y1);
			teleport[cnt] = true;
			nds[cnt++] = point(x1, y1);
		}
		scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
		teleport[cnt] = false;
		int s = cnt;
		nds[cnt++] = point(x1, y1);
		teleport[cnt] = false;
		int t = cnt;
		nds[cnt++] = point(x2, y2);
			
		for(int i=0; i<cnt; i++) {
			for(int j=0; j<cnt; j++) {
				if (checkseg(nds[i], nds[j])) pdist[i][j] = dist(nds[i], nds[j]);
				else pdist[i][j] = -1.0;
				pclear[i][j] = clearseg(nds[i], nds[j]);
			}
		}
		
		for(int tel=0; tel<=N; tel++) {
			for(int i=0; i<cnt; i++) {
				adjList[i+tel*cnt].clear();
				if (tel+1 <= N) {
					adjList[i+tel*cnt].push_back(ii(0.0, i + (tel+1)*cnt));
				}
				for(int j=0; j<cnt; j++) {
					if (pdist[i][j] < 0.0) continue;
					adjList[i+tel*cnt].push_back(ii(pdist[i][j], j + tel*cnt));
					if (teleport[i] && teleport[j] && tel+1 <= N && pclear[i][j]) {
						adjList[i+tel*cnt].push_back(ii(0.0, j + (tel+1)*cnt));
					}
				}
			}
		}
		
		printf("%d\n", int(dijkstra(s, t+N*cnt) + 0.5));
		/*for(int i=0; i<cnt; i++) {
			printf("mindist(%lf,%lf) = %.3f\n", nds[i].x, nds[i].y, ddist[i+N*cnt]);
		}*/
	}
	
	return 0;
}
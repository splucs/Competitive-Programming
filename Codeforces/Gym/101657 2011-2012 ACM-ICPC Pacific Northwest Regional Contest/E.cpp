#include <bits/stdc++.h>
using namespace std;
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define MAXN 69
#define MAXSQ 28
#define MAXM 3300009
#define OFFSET 13

struct point {
	long long x, y;
	point() { x = y = 0; }
	point(long long _x, long long _y) : x(_x), y(_y) {}
	point operator +(point other) const{
		return point(x + other.x, y + other.y);
	}
	point operator -(point other) const{
		return point(x - other.x, y - other.y);
	}
	point operator *(long long k) const{
		return point(x*k, y*k);
	}
};

long long inner(point p1, point p2) {
	return p1.x*p2.x + p1.y*p2.y;
}

long long cross(point p1, point p2) {
	return p1.x*p2.y - p1.y*p2.x;
}

bool collinear(point p, point q, point r) {
	return cross(p-q, r-p) == 0;
}

bool between(point p, point q, point r) {
    return collinear(p, q, r) && inner(p - q, r - q) <= 0;
}

bool segIntersects(point a, point b, point p, point q) {
    point u = b-a, v = q-p;
	long long vu = cross(v, u);
    if (vu == 0) return between(a, p, b) || between(a, q, b) || between(p, a, q) || between(p, b, q);
    long long k1 = (cross(a, v) - cross(p, v));
    long long k2 = (cross(a, u) - cross(p, u));
    return k1 >= 0 && k1 <= vu && k2 >= 0 && k2 <= vu;
}

int pos[MAXN][MAXN][MAXSQ][MAXSQ];
vector<int> adjList[MAXM];
int W, H;

bool valid(int i, int j) {
	return i >= 0 && j >= 0 && i < W && j < H;
}

bool validspeed(int vi, int vj) {
	return vi >= 0 && vj >= 0 && vi < MAXN && vj < MAXN;
}

typedef pair<point, point> pp;
vector<pp> walls;
bool check(point p1, point p2) {
	for(const pp wall : walls) {
		if (segIntersects(wall.first, wall.second, p1, p2)) {
			return false;
		}
		if (segIntersects(wall.second, wall.first, p1, p2)) {
			return false;
		}
		if (segIntersects(wall.first, wall.second, p2, p1)) {
			return false;
		}
		if (segIntersects(wall.second, wall.first, p2, p1)) {
			return false;
		}
	}
	return true;
}

void process(int i, int j, int vi, int vj) {
	int u = pos[i][j][vi][vj];
	for(int di = -1; di <= 1; di++) {
		for(int dj = -1; dj <= 1; dj++) {
			if (abs(di) + abs(dj) >= 2) continue;
			int nvi = vi + di;
			int nvj = vj + dj;
			int ni = i + nvi - OFFSET;
			int nj = j + nvj - OFFSET;
			if (!valid(ni, nj) || !validspeed(nvi, nvj) || !check(point(i, j), point(ni, nj))) continue;
			int v = pos[ni][nj][nvi][nvj];
			adjList[u].push_back(v);
		}
	}
}

int x[MAXM], y[MAXM], vx[MAXM], vy[MAXM];
void preprocess() {
	int k = 0;
	FOR(i, W) FOR(j, H) FOR(vi, MAXSQ) FOR(vj, MAXSQ) {
		x[k] = i, y[k] = j;
		vx[k] = vi;
		vy[k] = vj;
		adjList[k].clear();
		pos[i][j][vi][vj] = k++;
	}
}

int dist[MAXM];
int bfs(int s, int t) {
	queue<int> q;
	memset(&dist, -1, sizeof dist);
	q.push(s);
	dist[s] = 0;
	while(dist[t] == -1 && !q.empty()) {
		int u = q.front();
		q.pop();
		process(x[u], y[u], vx[u], vy[u]);
		for(int& v : adjList[u]) {
			if (dist[v] == -1) {
				dist[v] = dist[u] + 1;
				q.push(v);
			}
		}
	}
	return dist[t];
}

int main() {
	while(scanf("%d %d", &W, &H) != EOF) {
		int tx, ty, sx, sy;
		scanf("%d %d %d %d", &sx, &sy, &tx, &ty);
		int F, x1, x2, y1, y2;
		scanf("%d", &F);
		walls.clear();
		while(F --> 0) {
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			walls.push_back(pp(point(x1, y1), point(x2, y2)));
		}
		preprocess();
		int s = pos[sx][sy][OFFSET][OFFSET];
		int t = pos[tx][ty][OFFSET][OFFSET];
		printf("%d\n", bfs(s, t));
	}
	return 0;
}
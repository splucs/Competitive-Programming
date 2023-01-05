#include <bits/stdc++.h>
using namespace std;
#define EPS 1e-9
#define MAXN 1009

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
	point operator +(point other) const{
		return point(x + other.x, y + other.y);
	}
	point operator -(point other) const{
		return point(x - other.x, y - other.y);
	}
};

double cross(point p1, point p2) {
	return p1.x*p2.y - p1.y*p2.x;
}

point lineIntersectSeg(point p, point q, point A, point B) {
	double a = B.y - A.y;
	double b = A.x - B.x;
	double c = B.x * A.y - A.x * B.y;
	double u = fabs(a * p.x + b * p.y + c);
	double v = fabs(a * q.x + b * q.y + c);
	return point((p.x * v + q.x * u) / (u+v), (p.y * v + q.y * u) / (u+v));
}

point l1[MAXN], l2[MAXN], inter[MAXN*MAXN];
int cnt = 0, col[MAXN*MAXN], si[MAXN*MAXN], sj[MAXN*MAXN], ans[MAXN][MAXN];
vector<int> line[MAXN], adjList[MAXN*MAXN];

bool comp(int i, int j) {
	return inter[i] < inter[j];
}

void backtrack(int u) {
	if (col[u] > 0) return;
	bool ok = false;
	for(col[u] = 1; true; col[u]++) {
		ok = true;
		//printf("col[%d] = %d\n", u, col[u]);
		for(int i=0; i<(int)adjList[u].size() && ok; i++) {
			int v = adjList[u][i];
			//printf("col[%d] = %d (adj)\n", v, col[v]);
			if (col[v] == col[u]) ok = false;
		}
		if (ok) break;
	}
	for(int i=0; i<(int)adjList[u].size(); i++) {
		int v = adjList[u][i];
		backtrack(v);
	}
}

int main() {
	int T, N;
	scanf("%d", &T);
	while(T-->0) {
		scanf("%d", &N);
		double x1, x2, y1, y2;
		cnt = 0;
		for(int i=0; i<N; i++) {
			scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
			l1[i] = point(x1, y1);
			l2[i] = point(x2, y2);
			line[i].clear();
			for(int j=0; j<i; j++) {
				if (fabs(cross(l2[i]-l1[i], l2[j]-l1[j])) < EPS) continue;
				point p = lineIntersectSeg(l1[i], l2[i], l1[j], l2[j]);
				inter[cnt] = p;
				line[i].push_back(cnt);
				line[j].push_back(cnt);
				adjList[cnt].clear();
				si[cnt] = i;
				sj[cnt] = j;
				//printf("intersection between lines %d and %d is node %d\n", i, j, cnt);
				cnt++;
			}
		}
		for(int i=0; i<N; i++) {
			sort(line[i].begin(), line[i].end(), comp);
			for(int j=0; j<(int)line[i].size(); j++) {
				if (j-1 >= 0){
					adjList[line[i][j]].push_back(line[i][j-1]);
					//printf("%d adjacent to %d\n", line[i][j], line[i][j-1]);
				}
				if (j+1 < (int)line[i].size()) {
					adjList[line[i][j]].push_back(line[i][j+1]);
					//printf("%d adjacent to %d\n", line[i][j], line[i][j+1]);
				}
			}
		}
		for(int i=0; i<cnt; i++) col[i] = 0;
		for(int i=0; i<cnt; i++) {
			backtrack(i);
		}
		memset(&ans, -1, sizeof ans);
		int mx = 0;
		for(int i=0; i<cnt; i++) {
			mx = max(mx, col[i]);
			ans[si[i]][sj[i]] = col[i];
			ans[sj[i]][si[i]] = col[i];
		}
		printf("%d\n", mx);
		for(int i=0; i<N; i++) {
			for(int j=i+1; j<N; j++) {
				printf("%d ", ans[i][j]);
			}
			if (i+1 < N) printf("\n");
		}
	}
	return 0;
}
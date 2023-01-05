#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < int(n); i++)
#define REP(i, n) for(int i = int(n)-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= int(n); i++)
#define REP1(i, n) for(int i = int(n); i > 0; i--)
#define pb push_back
#define INF 0x3f3f3f3f
#define EPS 1e-9
#define mset(x, y) memset(&x, y, sizeof x)

int x[25], y[25], pos[5][5];
double mitm[1<<25], baseCost;
double dist[25][25];
bool vis[25][25], isedge[25];
int num[25];
int eu[100], ev[100], ne;
int initialMask;

void addedge(int u, int v) {
	if (u == v) return;
	if (u > v) swap(u, v);
	if (vis[u][v]) return;
	vis[u][v] = vis[v][u] = true;
	assert(__gcd(abs(x[u] - x[v]), abs(y[u] - y[v])) == 1);
	eu[ne] = u;
	ev[ne] = v;
	num[u] = num[v] = 1;
	initialMask ^= (1<<v)^(1<<u);
	baseCost += dist[u][v];
	ne++;
}

void addpath(int i1, int j1, int i2, int j2) {
	isedge[pos[i1][j1]] = true;
	isedge[pos[i2][j2]] = true;
	int dj = j2 - j1;
	int di = i2 - i1;
	int g = __gcd(abs(di), abs(dj));
	di /= g;
	dj /= g;
	FOR(it, g) {
		addedge(pos[i1 + di*(it)][j1 + dj*(it)], pos[i1 + di*(it+1)][j1 + dj*(it+1)]);
	}	
}

vector<int> computePaths() {
	vector<int> ans;
	ans.pb(0);
	FOR(u, 25) FOR(v, u) {
		if (!isedge[u] && !isedge[v]) continue;
		if (num[v] == 0) continue;
		ans.pb((1<<u)^(1<<v));
	}
	return ans;
}

bool checkConnected() {
	int st = eu[0];
	queue<int> q;
	q.push(st);
	num[st] = 2;
	while (!q.empty()) {
		int w = q.front();
		q.pop();
		FOR(e, ne) {
			int u = eu[e], v = ev[e];
			if (u != w && v != w) continue;
			int o = u + v - w;
			if (num[o] != 1) continue;
			num[o] = 2;
			q.push(o);
		}
	}
	FOR(u, 25) {
		if (num[u] == 1) return false;
	}
	return true;
}

int main() {
	FOR(i, 5) FOR(j, 5) {
		pos[i][j] = 5*i + j;
		x[pos[i][j]] = i;
		y[pos[i][j]] = j;
	}
	FOR(u, 25) FOR(v, 25) {
		dist[u][v] = hypot(x[u] - 1.0*x[v], y[u] - 1.0*y[v]);
	}
	int T;
	scanf("%d", &T);
	FOR1(caseNo, T) {
		printf("Case %d: ", caseNo);
		mset(vis, false);
		mset(isedge, false);
		mset(num, 0);
		ne = 0;
		initialMask = 0;
		baseCost = 0;
		int n;
		scanf("%d", &n);
		FOR(i, n) {
			char x1, x2;
			int y1, y2;
			scanf(" %c%d %c%d", &x1, &y1, &x2, &y2);
			x1 -= 'A';
			x2 -= 'A';
			y1--;
			y2--;
			addpath(x1, y1, x2, y2);
		} 
		if (!checkConnected()) {
			printf("~x(\n");
			continue;
		}
		FOR(mask, 1<<25) mitm[mask] = 1e30;
		int m = (ne / 2) + (ne % 2);
		FOR(mask, 1<<m) {
			int mask1 = 0;
			double cost = 0;
			FOR(e, m) {
				int u = eu[e], v = ev[e];
				if (mask & (1<<e)) {
					cost += dist[u][v];
					mask1 ^= (1<<u)^(1<<v);
				}
			}
			if (mitm[mask1] > cost)
				mitm[mask1] = cost;
		}
		vector<int> paths = computePaths();
		double ans = 1e30;
		FOR(mask, 1<<(ne-m)) {
			int mask2 = 0;
			double cost = 0;
			FOR(e, ne-m) {
				int u = eu[e+m], v = ev[e+m];
				if (mask & (1<<e)) {
					cost += dist[u][v];
					mask2 ^= (1<<u)^(1<<v);
				}
			}
			double dcost = 1e30, cur;
			int mask1;
			for (int target : paths) {
				mask1 = mask2^target^initialMask;
				cur = mitm[mask1];
				if (dcost > cur) dcost = cur;
			}
			if (ans > cost + dcost)
				ans = cost + dcost;
		}
		ans += baseCost;
		printf("%.2f\n", ans);
	}
	return 0;
}

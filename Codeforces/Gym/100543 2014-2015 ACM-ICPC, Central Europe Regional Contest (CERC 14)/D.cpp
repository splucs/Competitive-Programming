#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define pb push_back
typedef long long ll;
typedef vector<int> vi;

vector<int> g[MAXN];
ll p[MAXN], q[MAXN];
int n, x[MAXN], y[MAXN], r[MAXN];
bool dir[MAXN];

ll gcd(ll a, ll b) {
	if (b == 0) return a;
	return gcd(b, a%b);
}

void dfs(int u, ll curp, ll curq, bool curdir) {
	p[u] = curp;
	q[u] = curq;
	dir[u] = curdir;
	ll newp, newq, m;
	for(int v : g[u]) {
		if (p[v] >= 0) continue;
		newp = curp*r[u];
		newq = curq*r[v];
		m = gcd(newq, newp);
		newq /= m;
		newp /= m;
		dfs(v, newp, newq, !curdir);
	}
}

int main() {
	int T;
	scanf("%d", &T);
	FOR1(caseNo, T) {
		scanf("%d", &n);
		FOR1(u, n) {
			g[u].clear();
			p[u] = -1;
			scanf("%d %d %d", &x[u], &y[u], &r[u]);
			FOR1(v, u-1) {
				int dx = x[u]-x[v];
				int dy = y[u]-y[v];
				int sr = r[u]+r[v];
				if (dx*dx + dy*dy == sr*sr) {
					g[u].pb(v);
					g[v].pb(u);
				}
			}
		}
		dfs(1, 1, 1, true);
		FOR1(u, n) {
			if (p[u] == -1)	printf("not moving\n");
			else {
				if (q[u] == 1) printf("%lld ", p[u]);
				else printf("%lld/%lld ", p[u], q[u]);
				if (dir[u]) printf("clockwise\n");
				else printf("counterclockwise\n");
			}
		}
	}
	return 0;
}
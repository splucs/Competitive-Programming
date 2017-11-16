#include <bits/stdc++.h>
using namespace std;
#define MAXN 309
#define EPS 1e-9

int N, K, Q, cnt;
int par[MAXN][2], ts[MAXN], inv[MAXN];
bool vis[MAXN];

void dfs(int u) {
	if (u == -1 || vis[u]) return;
	vis[u] = true;
	dfs(par[u][0]);
	dfs(par[u][1]);
	ts[cnt] = u;
	inv[u] = cnt;
	cnt++;
}

struct fraction {
	long long x, y;
	fraction() : x(0), y(1) {}
	fraction(long long _x, long long _y) : x(_x), y(_y) {
		while((x&1) == 0 && (y&1) == 0 && (x||y)) {
			x >>= 1;
			y >>= 1;
		}
	}
	fraction operator +(fraction o) { return fraction(x*o.y + o.x*y, y*o.y); }
	fraction operator -(fraction o) { return fraction(x*o.y - o.x*y, y*o.y); }
	fraction operator *(fraction o) { return fraction(x*o.x, y*o.y); }
	fraction operator /(fraction o) { return fraction(x*o.y, y*o.x); }
};
fraction p1[MAXN], p2[MAXN];

int main() {
	scanf("%d %d", &N, &K);
	
	memset(&par, -1, sizeof par);
	memset(&vis, false, sizeof vis);
	
	int a, b, c;
	while(K --> 0) {
		scanf("%d %d %d", &a, &b, &c);
		par[a][0] = b;
		par[a][1] = c;
	}
	
	cnt = 0;
	for(int i=1; i<=N; i++) dfs(i);
	
	scanf("%d", &Q);
	fraction ans;
	while(Q --> 0) {
		scanf("%d %d", &a, &b);
		if (inv[a] > inv[b]) swap(a, b);
		
		for(int i=1; i<=N; i++) p1[i] = p2[i] = fraction(0, 1);
		p1[a] = fraction(1, 1);
		for(int i=cnt-1; i>=0; i--) {
			int u = ts[i];
			//printf("p1[%d] = %.3f\n", u, p1[u].x*1.0/p1[u].y);
			p1[par[u][0]] = p1[par[u][0]] + (p1[u]*fraction(1, 2));
			p1[par[u][1]] = p1[par[u][1]] + (p1[u]*fraction(1, 2));
		}
		
		p2[b] = fraction(1, 1);
		ans = fraction(0, 1);
		for(int i=cnt-1; i>=0; i--) {
			int u = ts[i];
			ans = ans + (p1[u]*p2[u]);
			//printf("p2[%d] = %.3f\n", u, p2[u].x*1.0/p2[u].y);
			if (p1[u].x != 0) continue;
			p2[par[u][0]] = p2[par[u][0]] + (p2[u]*fraction(1, 2));
			p2[par[u][1]] = p2[par[u][1]] + (p2[u]*fraction(1, 2));
		}
		
		ans = ans * fraction(100, 1);
		printf("%I64d", ans.x/ans.y);
		ans.x %= ans.y;
		if (ans.x != 0) printf(".");
		while(ans.x != 0) {
			ans.x *= 5;
			ans.y >>= 1;
			printf("%I64d", ans.x/ans.y);
			ans.x %= ans.y;
		}
		printf("%%\n");
	}
	
	return 0;
}
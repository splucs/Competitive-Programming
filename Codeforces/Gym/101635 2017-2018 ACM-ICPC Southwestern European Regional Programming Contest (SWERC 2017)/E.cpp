#include <bits/stdc++.h>
#define MAXN 10009
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define fi first
#define se second
#define sz(x) int(x.size())
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;

int n = 0, m, B;
int cost[MAXN], prestige[MAXN];
vector< pair<int, ii> > g[MAXN];
int deg[MAXN];

map<string, int> red;
string name[MAXN];
int reduce(string str) {
	if (!red.count(str)) {
		red[str] = ++n;
		name[n] = str;
	}
	return red[str];
}

int q[MAXN];
vector<ii> arr;

void kahn() {
	FOR1(u, n) {
		deg[u] = 0;
		cost[u] = INF;
	}
	FOR1(u, n) for(auto p : g[u]) {
		deg[p.fi]++;
	}
	int en = 0;
	FOR1(u, n) {
		if (deg[u] == 0) {
			q[en++] = u;
			cost[u] = 0;
			prestige[u] = 0;
		}
	}
	FOR(st, en) {
		int u = q[st];
		//printf("%s: %d %d\n", name[u].c_str(), prestige[u], cost[u]);
		for(auto pp : g[u]) {
			int v = pp.fi;
			int w = pp.se.fi;
			int p = pp.se.se;
			if (cost[v] > cost[u] + w) {
				cost[v] = cost[u] + w;
				prestige[v] = prestige[u] + p;
			}
			if (cost[v] == cost[u] + w && prestige[v] < prestige[u] + p) {
				prestige[v] = prestige[u] + p;
			}
			deg[v]--;
			if (deg[v] == 0) q[en++] = v;
		}
	}
}

int P[2][MAXN], S[2][MAXN];

ii knapsack() {
	FOR(i, n+1) FOR(j, B+1) {
		if (i == 0) {
			P[i%2][j] = 0;
			S[i%2][j] = j;
		}
		else {
			P[i%2][j] = P[(i+1)%2][j];
			S[i%2][j] = S[(i+1)%2][j];
			if (j >= cost[i] && prestige[i]+P[(i+1)%2][j-cost[i]] > P[i%2][j]) {
				P[i%2][j] = prestige[i]+P[(i+1)%2][j-cost[i]];
				S[i%2][j] = S[(i+1)%2][j-cost[i]];
			}
			if (j >= cost[i] && prestige[i]+P[(i+1)%2][j-cost[i]] == P[i%2][j]
				&& S[i%2][j] < S[(i+1)%2][j-cost[i]]) {
				P[i%2][j] = prestige[i]+P[(i+1)%2][j-cost[i]];
				S[i%2][j] = S[(i+1)%2][j-cost[i]];
			}
		}
	}
	return {P[n%2][B], B-S[n%2][B]};
}

char s1[MAXN], s2[MAXN], s3[MAXN];

int main() {
	scanf("%d %d", &B, &m);
	FOR(j, m) {
		int w, p;
		scanf(" %s %s %s %d %d", s2, s1, s3, &w, &p);
		int u = reduce(string(s1));
		int v = reduce(string(s2));
		g[u].pb({v, {w,p}});
	}
	kahn();
	ii ans = knapsack();
	printf("%d\n%d\n", ans.fi, ans.se);
	return 0;
}
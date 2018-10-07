#include <bits/stdc++.h>
using namespace std;
#define MAXN 4000009
#define MAXM 300009
#define MAXLOGN 20
#define INF 0x3f3f3f3f
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define pb push_back
#define fi first
#define se second
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;

map<string, int> stop;
string name[MAXM];

char buffer[109];

int readStops() {
	scanf(" %s", buffer);
	int ans = 0;
	stop.clear();
	bool ok = true;
	do {
		scanf(" %s", buffer);
		int len = strlen(buffer);
		if (buffer[len-1] == ',') {
			buffer[--len] = 0;
		}
		else ok = false;
		stop[string(buffer)] = ++ans;
		//printf("stop %d: %s\n", ans, buffer);
		name[ans] = string(buffer);
	} while(ok);
	return ans;
}

int readNRoute() {
	scanf(" %s", buffer);
	int ans = 0;
	bool ok = true;
	do {
		scanf(" %s", buffer);
		int len = strlen(buffer);
		if (buffer[len-1] == ',') {
			buffer[--len] = 0;
		}
		else ok = false;
		ans++;
	} while(ok);
	return ans;
}

vi readRoute() {
	scanf(" %s %s", buffer, buffer);
	vi ans;
	bool ok = true;
	do {
		scanf(" %s", buffer);
		int len = strlen(buffer);
		if (buffer[len-1] == ',') {
			buffer[--len] = 0;
		}
		else ok = false;
		ans.pb(stop[string(buffer)]);
	} while(ok);
	return ans;
}

int readHouse() {
	scanf(" %s %s %s", buffer, buffer, buffer);
	scanf(" %s", buffer);
	return stop[string(buffer)];
}

int cnt, n, s, t;
int center[MAXN], dist[MAXN];
vector<ii> g[MAXN];
vi q[MAXM];

int bfs() {
	FOR(i, cnt+1) q[i].clear();
	FOR1(i, cnt) dist[i] = INF;
	q[0].pb(s);
	dist[s] = 0;
	FOR(i, cnt+1) {
		while(!q[i].empty()) {
			int u = q[i].back();
			q[i].pop_back();
			if (dist[u] != i) continue;
			//if (u <= n) printf("dist[%d] = %d\n", u, i);
			for(ii pp : g[u]) {
				int v = pp.se;
				int w = pp.fi;
				//printf("candidate %d, %d < %d + %d\n", v, dist[v], dist[u], w);
				if (dist[v] > dist[u] + w) {
					dist[v] = dist[u] + w;
					//printf("added %d\n", v);
					q[dist[v]].pb(v);
				}
			}
		}
	}
	return dist[t];
}

int dp[MAXN];
bitset<MAXN> vis;

int DP(int u) {
	int &ans = dp[u];
	if (vis[u]) return ans;
	vis[u] = true;
	if (u == t) return ans = 0;
	ans = -INF;
	for(ii pp : g[u]) {
		int v = pp.se;
		int w = pp.fi;
		if (dist[v] != dist[u] + w) continue;
		int add = 1;
		if (u <= n || v <= n) add = 0;
		ans = max(ans, add + DP(v));
	}
	return ans;
}

int main() {
	int T;
	scanf("%d", &T);
	FOR1(caseNo, T) {
		n = readStops();
		cnt = 0;
		FOR1(i, n) {
			center[i] = ++cnt;
			g[cnt].clear();
		}
		int nlines = readNRoute();
		while(nlines --> 0) {
			vi line = readRoute();
			FOR(k, 2) {
				//printf("line:");
				FOR(i, sz(line)) {
					//printf(" %d", line[i]);
					++cnt;
					g[cnt].clear();
					g[cnt].pb({0, center[line[i]]});
					g[center[line[i]]].pb({1, cnt});
					if (i > 0) g[cnt-1].pb({0, cnt});
				}
				//printf("\n");
				reverse(all(line));
			}
		}
		s = center[readHouse()];
		t = center[readHouse()];
		int changes = bfs();
		vis.reset();
		int maxtime = DP(s);
		printf("optimal travel from %s to %s: %d line%s, %d minute%s\n",
			name[s].c_str(), name[t].c_str(),
			changes, changes > 1 ? "s" : "",
			maxtime, maxtime > 1 ? "s" : ""
		);
	}
	return 0;
}
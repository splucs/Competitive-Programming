#include <bits/stdc++.h>
using namespace std;
#define MAXN 29
#define MAXM MAXN*MAXN*300
#define MOD 1000000007
#define INF 1000000009
#define EPS 1e-7
#define FOR(x,n) for(int x=0; x<n; x++)
#define FOR1(x,n) for(int x=1; x<=n; x++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;

int H, W, cnt;
int pos[MAXN][MAXN][300], num[MAXM];
bool vis[MAXM];
char endpoint[MAXM], neigh[300];
vector<int> g[MAXM];

int dfs(int u, int p) {
	if (vis[u]) return -1;
	printf("dfs %d\n", u);
	vis[u] = true;
	if (p != -1 && g[u].size() == 1u) return u;
	for(int v : g[u]) {
		if (v == p) continue;
		return dfs(v, u);
	}
	printf("error\n");
}

vector<ii> getedges() {
	memset(&vis, false, sizeof vis);
	vector<ii> ans;
	FOR1(u, cnt) {
		if (!vis[u]) {
			int p1 = u;
			int p2 = dfs(u, -1);
			if (p2 != -1) ans.push_back(ii(p1, p2));
		}
	}
	return ans;
}

int main() {

	neigh['A'] = 'F';
	neigh['B'] = 'E';
	neigh['C'] = 'H';
	neigh['D'] = 'G';
	neigh['E'] = 'B';
	neigh['F'] = 'A';
	neigh['G'] = 'D';
	neigh['H'] = 'C';

	int bcount = 0;
	while(scanf("%d %d", &H, &W), H || W) {
		cnt = 0;
		int k = 0;
		FOR(i, H) FOR(j, W) {
			k++;
			for(char c = 'A'; c <= 'H'; c++) {
				pos[i][j][c] = ++cnt;
				num[cnt] = k;
				endpoint[cnt] = c;
				g[cnt].clear();
			}
		}
		FOR(i, H) FOR(j, W) {
			int c;
			scanf("%d", &c);
			while(c--) {
				char c1, c2;
				scanf(" %c %c", &c1, &c2);
				int u = pos[i][j][c1];
				int v = pos[i][j][c2];
				g[u].push_back(v);
				g[v].push_back(u);
			}
		}
		FOR(i, H) FOR(j, W-1) {
			for(char c = 'C'; c <= 'D'; c++) {
				int u = pos[i][j][c];
				int v = pos[i][j+1][neigh[c]];
				g[u].push_back(v);
				g[v].push_back(u);
			}
		}
		FOR(i, H-1) FOR(j, W) {
			for(char c = 'E'; c <= 'F'; c++) {
				int u = pos[i][j][c];
				int v = pos[i+1][j][neigh[c]];
				g[u].push_back(v);
				g[v].push_back(u);
			}
		}
		vector<ii> ans = getedges();
		if (bcount > 0) printf("\n");
		printf("Board %d:\n", ++bcount);
		for(ii &cur : ans) {
			int u = cur.first;
			int v = cur.second;
			printf("%d%c is connected to %d%c\n", num[u], endpoint[u], num[v], endpoint[v]);
		}
	}
	return 0;
}
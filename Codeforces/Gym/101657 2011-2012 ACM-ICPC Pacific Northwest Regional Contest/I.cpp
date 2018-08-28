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
char endpoint[MAXM], neigh[300];
vector<int> g[MAXM];

int dfs(int u, int p) {
	for(int v : g[u]) {
		if (v == p) continue;
		//printf("%d%c -> %d%c\n", num[u], endpoint[u], num[v], endpoint[v]);
		return dfs(v, u);
	}
	return u;
}

char buffer[10009];

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
	while(scanf(" %d %d ", &H, &W), H || W) {
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
		while(true) {
			int n;
			scanf("%d ", &n);
			if (n == 0) break;
			int i = (n-1)/W;
			int j = (n-1)%W;
			gets(buffer);
			//printf("description for square %d: |%s|\n", n, buffer);
			scanf("\n");
			int len = strlen(buffer);
			FOR(it, len) {
				if (buffer[it] != ' ' && (it == 0 || buffer[it-1] == ' ')) {
					char c1, c2;
					sscanf(buffer+it, " %c %c", &c1, &c2);
					int u = pos[i][j][c1];
					int v = pos[i][j][c2];
					//printf("wire (internal) %d%c - %d%c\n", num[u], endpoint[u], num[v], endpoint[v]);
					g[u].push_back(v);
					g[v].push_back(u);
				}
			}
		}
		FOR(i, H) FOR(j, W-1) {
			for(char c = 'C'; c <= 'D'; c++) {
				int u = pos[i][j][c];
				int v = pos[i][j+1][neigh[c]];
				//printf("wire (horizontal) %d%c - %d%c\n", num[u], endpoint[u], num[v], endpoint[v]);
				g[u].push_back(v);
				g[v].push_back(u);
			}
		}
		FOR(i, H-1) FOR(j, W) {
			for(char c = 'E'; c <= 'F'; c++) {
				int u = pos[i][j][c];
				int v = pos[i+1][j][neigh[c]];
				//printf("wire (vertical) %d%c - %d%c\n", num[u], endpoint[u], num[v], endpoint[v]);
				g[u].push_back(v);
				g[v].push_back(u);
			}
		}
		if (bcount > 0) printf("\n");
		printf("Board %d:\n", ++bcount);
		gets(buffer);
		scanf("\n");
		int len = strlen(buffer);
		FOR(it, len) {
			if (buffer[it] != ' ' && (it == 0 || buffer[it-1] == ' ')) {
				char c;
				int n;
				sscanf(buffer+it, "%d%c", &n, &c);
				int i = (n-1)/W;
				int j = (n-1)%W;
				int u = pos[i][j][c];
				int v = dfs(u, -1);
				printf("%d%c is connected to %d%c\n", num[u], endpoint[u], num[v], endpoint[v]);
		
			}
		}
	}
	return 0;
}
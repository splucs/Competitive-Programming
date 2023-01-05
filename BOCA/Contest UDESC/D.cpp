#include <bits/stdc++.h>
using namespace std;
#define MAXN 1010009
#define MAXM 320
#define MOD 1000000007
#define INF 1000000009
#define EPS 1e-7
#define FOR(x,n) for(int x=0; x<n; x++)
#define FOR1e(x,n) for(int x=1; x<=n; x++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;

vector<int> viz[MAXN];
vector<int> esq[MAXN], dir[MAXN];
bool vis[MAXN];

int arr[MAXN];

void bfs(int u) {
	queue<int> q;
	q.push(u);
	vis[u] = true;
	
	while (!q.empty()) {
		u = q.front(); q.pop();
	
		FOR(i, viz[u].size()) {
			int v = viz[u][i];
			if (vis[v]) continue;
			q.push(v); vis[v] = true;
		}
	}
}
int main() {
	int n;
	while (scanf("%d", &n) != EOF && n > 0) {
		FOR(i, n) scanf("%d", &arr[i]);
		FOR(i, n + 9) {
			viz[i].clear();
			esq[i].clear();
			dir[i].clear();
		}

		FOR(i, n) {
			if (i + arr[i] < n) {
				esq[i+arr[i]].pb(i);
			}
			if (i - arr[i] >= 0) {
				dir[i-arr[i]].pb(i);
			}
		}
		FOR(i, n) {
			FOR(a, esq[i].size()) {
				FOR(b, dir[i].size()) {
					viz[esq[i][a]].pb(dir[i][b]);
					viz[dir[i][b]].pb(esq[i][a]);
				}
			}
		}
		memset(vis, 0, sizeof(vis));

		bfs(0);

		int m = 0;
		FOR(i, n) {
			if (vis[i]) m = i;
		}
		printf("%d\n", m);
	} 
}
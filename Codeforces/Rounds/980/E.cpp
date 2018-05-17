#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000009
#define MAXLOGN 22
#define MAXM (30*MAXN)
#define MOD 1000000007
#define INF 1000000009
#define EPS 1e-9
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;
#define EPS 1e-9

vector<int> g[MAXN];
int N, K;
int P[MAXN][MAXLOGN], h[MAXN];
bool in[MAXN];

void depthdfs(int u) {
	for(int v : g[u]) {
		if (v == P[u][0]) continue;
		P[v][0] = u;
		depthdfs(v);
	}
}

void computeP(int root) {
	P[root][0] = root;
	depthdfs(root);
	for(int j = 1; j < MAXLOGN; j++)
		for(int i = 1; i <= N; i++) {
			P[i][j] = P[P[i][j-1]][j-1];
		}
}

int dist(int u) {
	if (in[u]) return 0;
	for(int & j = h[u]; j >= 0; j--) {
		if (in[P[u][j]]) continue;
		return (1<<j) + dist(P[u][j]);
	}
	return 1;
}

int main() {
	scanf("%d %d", &N, &K);
	K = N-K;
	FOR(j, N-1) {
		int u, v;
		scanf("%d %d", &u, &v);
		g[u].pb(v);
		g[v].pb(u);
	}
	computeP(N);
	memset(&in, false, sizeof in);
	K--;
	FOR1(i, N) h[i] = MAXLOGN - 1;
	in[N] = true;
	for(int i = N-1; i > 0; i--) {
		//printf("dist(%d) = %d\n", i, dist(i));
		if (dist(i) <= K) {
			for(int j = i; !in[j]; j = P[j][0]) {
				in[j] = true;
				K--;
			}
		}
	}
	FOR1(i, N) {
		if (!in[i]) printf("%d ", i);
	}
	return 0;
}
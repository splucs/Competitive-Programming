#include <cstdio>
#include <vector>
#include <iostream>
using namespace std;
#define MAXN 100009
#define MAXLOGN 20
#define INF (1<<30)

/*
 * LCA + PATH QUERY O(logn)
 */

const int neutral = 0;
#define comp(a, b) ((a)+(b))

typedef pair<int, int> ii;
vector<ii> adjList[MAXN];
int level[MAXN];
int P[MAXN][MAXLOGN], D[MAXN][MAXLOGN];

void depthdfs(int u) {
	for(int i=0; i<(int)adjList[u].size(); i++) {
		int v = adjList[u][i].first;
		int w = adjList[u][i].second;
		if (v == P[u][0]) continue;
		P[v][0] = u; D[v][0] = w;
		level[v] = 1 + level[u];
		depthdfs(v);
	}
}

void computeP(int root, int n) {
	level[root] = 0;
	P[root][0] = root; D[root][0] = neutral;
	depthdfs(root);
	for(int j = 1; j < MAXLOGN; j++)
		for(int i = 1; i <= n; i++) {
			P[i][j] = P[P[i][j-1]][j-1];
			D[i][j] = comp(D[P[i][j-1]][j-1], D[i][j-1]);
		}
}

ii LCA(int u, int v) {
	if (level[u] > level[v]) swap(u, v);
	int d = level[v] - level[u];
	int ans = neutral;
	for(int i = 0; i < MAXLOGN; i++) {
		if (d & (1<<i)) {
			ans = comp(ans, D[v][i]);
			v = P[v][i];
		}
	}
	if (u == v) return ii(u, ans);
	for(int i = MAXLOGN-1; i >= 0; i--)
		while(P[u][i] != P[v][i]) {
			ans = comp(ans, D[v][i]);
			ans = comp(ans, D[u][i]);
			u = P[u][i]; v = P[v][i];
		}
	ans = comp(ans, D[v][0]);
	ans = comp(ans, D[u][0]);
	return ii(P[u][0], ans);
}

/*
 * TEST MATRIX
 */
#include <cstdlib>
#include <ctime>
int N;

void generateRandTree(int _N) {
	N = _N;
	//printf("new tree %d:\n", N);
	for(int i=1; i<=N; i++) {
		adjList[i].clear();
		if (i == 1) continue;
		int j = 1 + rand()%(i-1);
		int w = rand()%1000;
		//printf("%d-%d: %d\n", i, j, w);
		adjList[i].push_back(ii(j, w));
		adjList[j].push_back(ii(i, w));
	}
}

bool dist(int u, int p, int t, int & ans) {
	if (u == t) return true;
	for(int i=0; i<(int)adjList[u].size(); i++) {
		int v = adjList[u][i].first;
		int w = adjList[u][i].second;
		if (v == p) continue;
		if (dist(v, u, t, ans)) {
			ans = comp(ans, w);
			return true;
		}
	}
	return false;
}

bool test(int nTest) {
	clock_t naive=0, lca=0, last;
	for(int t=1; t<=nTest; t++) {
		generateRandTree(t);
		computeP(1, t);

		for(int it=0; it<t; it++) {
			int u = 1 + (rand()%t);
			int v = 1 + (rand()%t);
			int res1 = neutral;
			last = clock();
			dist(u, -1, v, res1);
			naive += clock() - last;
			last = clock();
			int res2 = LCA(u, v).second;
			lca += clock() - last;
			if (res1 != res2) {
				printf("failed on test %d\n", t);
				return false;
			}
		}
	}

	printf("all tests passed\n");
	printf("naive time: %.3fs, lca time: %.3fs\n", naive*1.0/CLOCKS_PER_SEC, lca*1.0/CLOCKS_PER_SEC);
	return true;
}

bool usertest() {
	scanf("%d", &N);
	int a, b, c;
	for(int i=1; i<N; i++) {
		scanf("%d %d %d", &a, &b, &c);
		adjList[a].push_back(ii(b, c));
		adjList[b].push_back(ii(a, c));
	}
	int root = 1;
	computeP(root, N);
	while(scanf("%d %d", &a, &b)!=EOF) {
		printf("LCA(%d, %d) = %d, ", a, b, LCA(a,b).first);
	}
	return true;
}

int main() {
	test(1000);
	return 0;
}
#include <vector>
using namespace std;
#define MAXN 200009

vector<int> adjList[MAXN], revAdjList[MAXN]; 	//grafo
vector<int> dtree[MAXN];						//dominator tree
int sdom[MAXN], dom[MAXN], idom[MAXN], N, M;	//semi-dominator, immediate dominator pelo indice, immediate dominator, tamanhos
int dsu[MAXN], best[MAXN];					//disjoint sets
int par[MAXN], num[MAXN], rev[MAXN], cnt;	//dfs

int find(int x) {
	if (x == dsu[x]) return x;
	int y = find(dsu[x]);
	if (sdom[best[x]] > sdom[best[dsu[x]]]) best[x] = best[dsu[x]];
	return dsu[x] = y;
}

void dfs(int u) {
	num[u] = cnt; rev[cnt++] = u;
	for (int i=0; i<(int)adjList[u].size(); i++) {
		int v = adjList[u][i];
		if (num[v] >= 0) continue;
		dfs(v);
		par[num[v]] = num[u];
	}
}

void dominator() {
	for (int u = 1; u <= N; u++) {
		num[u] = -1; dtree[u].clear();
		dsu[u] = best[u] = sdom[u] = u;
	}
	cnt = 0;
	dfs(1);
	for (int j = cnt - 1, u; u = rev[j], j > 0; j--) {
		for (int i = 0; i<(int)revAdjList[u].size(); i++) {
			int y = num[revAdjList[u][i]];
			if (y == -1) continue;
			find(y);
			if (sdom[best[y]] < sdom[j]) sdom[j] = sdom[best[y]];
		}
		dtree[sdom[j]].push_back(j);
		int x = dsu[j] = par[j];
		for (int i=0; i<(int)dtree[x].size(); i++) {
			int z = dtree[x][i];
			find(z);
			if (sdom[best[z]] < x) dom[z] = best[z];
			else dom[z] = x;
		}
		dtree[x].clear();
	}
	idom[1] = -1;
	for (int i = 1; i < cnt; i++) {
		if (sdom[i] != dom[i]) dom[i] = dom[dom[i]];
		idom[rev[i]] = rev[dom[i]];
		dtree[rev[dom[i]]].push_back(rev[i]);
	}
}

/*
 * Codeforces 100513L
 */
 

#include <cstdio>
#include <set>

int eu[MAXN], ev[MAXN];
int st[MAXN], en[MAXN], k;

void dfs2(int u, int p) {
	st[u] = k++;
	for(int i=0; i<(int)dtree[u].size(); i++) {
		int v = dtree[u][i];
		if (v != p) dfs2(v, u);
	}
	en[u] = k++;
}

int main() {
	int u, v;
	set<int> ans;
	while(scanf("%d %d", &N, &M) != EOF) {
		for(int j=1; j<=M; j++) {
			scanf("%d %d", &u, &v);
			adjList[u].push_back(v);
			revAdjList[v].push_back(u);
			eu[j] = u;
			ev[j] = v;
		}
		dominator();
		ans.clear();
		k = 0;
		dfs2(1, -1);
		for(int j=1; j<=M; j++) {
			u = eu[j];
			v = ev[j];
			if (st[v] <= st[u] && en[v] >= en[u]) continue;
			if (num[u] == -1 || num[v] == -1) continue;
			ans.insert(j);
		}
		printf("%u\n", ans.size());
		for(set<int>::iterator it = ans.begin(); it != ans.end(); it++) {
			printf("%d ", *it);
		}
		printf("\n");
		for(int i=1; i<=N; i++) {
			adjList[i].clear();
			revAdjList[i].clear();
		}
	}
	return 0;
}

/*
 * COJ 2609
 */
 
/*
#include <cstdio>
#define MAXLOGN 22

int level[MAXN];
int P[MAXN][MAXLOGN];

void derevhdfs(int u) {
	for(int i=0; i<(int)dtree[u].size(); i++) {
		int v = dtree[u][i];
		if (v == P[u][0]) continue;
		P[v][0] = u;
		level[v] = 1 + level[u];
		derevhdfs(v);
	}
}
void computeP(int root) {
	level[root]=0;
	P[root][0]=root;
	derevhdfs(root);
	for(int j = 1; j < MAXLOGN; j++)
		for(int i = 1; i <= N; i++)
			P[i][j] = P[P[i][j-1]][j-1];
}
int LCA(int a, int b) {
	if(level[a] > level[b]) swap(a, b);
	int d = level[b] - level[a];
	for(int i=0; i<MAXLOGN; i++) {
		if((d & (1<<i)) != 0) b = P[b][i];
	}
	if(a == b) return a;
	for(int i = MAXLOGN-1; i>=0; i--)
		while(P[a][i] != P[b][i]) {
			a=P[a][i]; b=P[b][i];
		}
	return P[a][0];
}
 
int main() {
	int u, v;
	while(scanf("%d %d", &N, &M) != EOF) {
		for(int j=1; j<=M; j++) {
			scanf("%d %d", &u, &v);
			adjList[u].push_back(v);
		}
		dominator();
		computeP(1);
		int ans = 0;
		for(int i=1; i<=N; i++) {
			for(int j=1; j<i; j++) {
				if (LCA(i, j) == 1) ans++;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

*/
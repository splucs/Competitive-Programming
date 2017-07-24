#include <vector>
#include <algorithm>
using namespace std;
#define MAXN 200009

vector<int> adjList[MAXN], revAdjList[MAXN]; 	//grafo
vector<int> dtree[MAXN], bucket[MAXN];			//dominator tree, auxiliar
int sdom[MAXN], idom[MAXN], dom[MAXN], N, M;	//semi-dominator, immediate dominator, idom pelo indice do dfs, tamanhos
int dsu[MAXN], label[MAXN];					//DSU
int par[MAXN], num[MAXN], rev[MAXN], cnt;	//dfs

int find(int u, int x) {
    if(u == dsu[u]) return x ? -1 : u;
    int v = find(dsu[u], x + 1);
    if(v < 0) return u;
    if(sdom[label[dsu[u]]] < sdom[label[u]]) label[u] = label[dsu[u]];
    dsu[u] = v;
    return x ? v : label[u];
}

void unionSet(int u,int v) {
    dsu[v] = u;   
}

void dfs(int u) {
    cnt++;
	num[u] = cnt; rev[cnt] = u;
    label[cnt] = cnt; sdom[cnt] = cnt; dsu[cnt] = cnt;
    for(int i = 0, v; i < (int)adjList[u].size(); i++) {
        v = adjList[u][i];
        if(!num[v]) {
            dfs(v);
            par[num[v]] = num[v];
        }
        revAdjList[num[v]].push_back(num[u]);
    }
}

void dominator() {
	cnt = 0;
	for(int u = 1; u <= N; u++) {
		revAdjList[u].clear();
		dtree[u].clear(); bucket[u].clear();
		num[u] = 0; dom[u] = u;
	}
	dfs(1);
	for(int i = cnt; i >= 1; i--) {
		for(int j = 0; j < (int)revAdjList[i].size(); j++)
			sdom[i] = min(sdom[i], sdom[find(revAdjList[i][j], 0)]);
		if(i > 1) bucket[sdom[i]].push_back(i);
		for(int j = 0; j < (int)bucket[i].size(); j++) {
			int w = bucket[i][j], v = find(w, 0);
			if(sdom[v] == sdom[w]) dom[w] = sdom[w];
			else dom[w] = v;
		}
		if(i > 1) unionSet(par[i], i);
	}
	for(int i = 2; i <= cnt; i++) {
		if(dom[i] != sdom[i]) dom[i] = dom[dom[i]];
		idom[i] = rev[dom[i]];
		dtree[idom[i]].push_back(rev[i]);
	}
}

/*
 * Codeforces 100513L (WA)
 */
 
/*
#include <cstdio>
#include <set>

int eu[MAXN], ev[MAXN];
int pre[MAXN], pos[MAXN], precnt, poscnt;

void dfs2(int u, int p) {
	pre[u] = precnt++;
	for(int i=0; i<(int)dtree[u].size(); i++) {
		int v = dtree[u][i];
		if (v != p) dfs2(v, u);
	}
	pos[u] = poscnt++;
}

int main() {
	int u, v;
	set<int> ans;
	while(scanf("%d %d", &N, &M) != EOF) {
		for(int j=1; j<=M; j++) {
			scanf("%d %d", &u, &v);
			adjList[u].push_back(v);
			eu[j] = u;
			ev[j] = v;
		}
		dominator();
		ans.clear();
		precnt = poscnt = 0;
		dfs2(1, -1);
		for(int j=1; j<=M; j++) {
			u = eu[j];
			v = ev[j];
			if (pre[v] <= pre[u] && pos[v] >= pos[u]) continue;
			if (num[u] == 0 || num[v] == 0) continue;
			ans.insert(j);
		}
		printf("%u\n", ans.size());
		for(set<int>::iterator it = ans.begin(); it != ans.end(); it++) {
			printf("%d ", *it);
		}
		printf("\n");
		for(int i=1; i<=N; i++) adjList[i].clear();
	}
	return 0;
}

*/

/*
 * COJ 2609
 */
#include <cstdio>
#define MAXLOGN 22

int level[MAXN];
int P[MAXN][MAXLOGN];

void depthdfs(int u){
	for(int i=0; i<(int)dtree[u].size(); i++){
		int v = dtree[u][i];
		if (v == P[u][0]) continue;
		P[v][0] = u;
		level[v] = 1 + level[u];
		depthdfs(v);
	}
}
void computeP(int root){
	level[root]=0;
	P[root][0]=root;
	depthdfs(root);
	for(int j = 1; j < MAXLOGN; j++)
		for(int i = 1; i <= N; i++)
			P[i][j] = P[P[i][j-1]][j-1];
}
int LCA(int a, int b){
	if(level[a] > level[b]) swap(a, b);
	int d = level[b] - level[a];
	for(int i=0; i<MAXLOGN; i++){
		if((d & (1<<i)) != 0) b = P[b][i];
	}
	if(a == b) return a;
	for(int i = MAXLOGN-1; i>=0; i--)
		while(P[a][i] != P[b][i]){
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
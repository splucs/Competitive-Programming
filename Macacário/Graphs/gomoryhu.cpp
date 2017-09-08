#include <bits/stdc++.h>
 
using namespace std;
#define MAXN 3005
#define MAXM 200005
#define INF 1000000009
typedef pair<int, int> ii;

int N, M;

/*
  Algoritmo de Fluxo (Dinic)
*/
int ned, prv[MAXN], first[MAXN], frt[MAXN];
int cap[MAXM], to[MAXM], nxt[MAXM], dist[MAXN];

void init(){
   memset(first, -1, sizeof first);
   ned = 0;
}
void add(int u, int v, int f){
    to[ned] = v, cap[ned] = f;
    nxt[ned] = first[u];
    first[u] = ned++;   
    to[ned] = u, cap[ned] = 0;
    nxt[ned] = first[v];
    first[v] = ned++;
}

int dfs(int u, int f, int s, int t) {
	if (u == t) return f;
	int v, df;
	for(int& e = frt[u]; e!=-1; e = nxt[e]){
        v = to[e];

		if (dist[v] == dist[u] + 1 && cap[e] > 0) {
			df = dfs(v, min(f, cap[e]), s, t);
			if (df > 0) {
				cap[e] -= df;
				cap[e^1] += df;
				return df;
			}
		}
	}
	return 0;
}
bool bfs(int s, int t){
	int u, v;
	memset(&dist, -1, sizeof dist);
	dist[s] = 0;
	queue<int> q; q.push(s);
	while (!q.empty()) {
		u = q.front(); q.pop();
		for(int e = first[u]; e!=-1; e = nxt[e]){
			v = to[e];
			if (dist[v] < 0 && cap[e] > 0) {
				dist[v] = dist[u] + 1;
				q.push(v);
			}
		}
	}
	return dist[t] >= 0;
}

int dinic(int s, int t) {
	int result = 0, f;
	while (bfs(s, t)) {
		
		memcpy(frt, first, sizeof(frt));
		while (f = dfs(s, INF, s, t)) result += f;
	}
	return result;
}

/*
  Gomory Hu Tree
*/

int parent[MAXN], flowToParent[MAXN];
int backup[MAXM];
bool belongToCut[MAXN];

// Add dinic and cap vector before
// Complexity O((N-1)*(flow computation))

void cutGraph(int s) {
	belongToCut[s] = true;

	for(int e = first[s]; e!=-1; e = nxt[e]){
		int v = to[e];
		if (!belongToCut[v] && cap[e] > 0) {
			cutGraph(v);
		}
	}
}

int computeMinCut(int s, int t) {
	memcpy(backup, cap, sizeof (cap));
	memset(belongToCut, 0, sizeof(belongToCut));
	int f = dinic(s, t); // Call flux algorithm
	cutGraph(s);

	memcpy(cap, backup, sizeof (cap));
	return f;
}

// Gusfield algorithm
// N-1 max-flow computations
// Vector from 0 to N-1
void gomory_hu_tree(int n, vector<vector<ii> >& neighbor) {
	for (int i = 0; i < n; i++) {
		parent[i] = 0;
	}

	// N-1 max-flow s-t
	for (int s = 1; s < n; s++) {
		int t = parent[s];
	
		flowToParent[s] = computeMinCut(s, t);
		for (int u = s+1; u < n; u++) {
			if (u == s) continue;
			if (parent[u] == t && belongToCut[u]) {
				parent[u] = s;
			}
			if (parent[t] == u && belongToCut[u]) {
				parent[s] = u;
				parent[t] = s;
				swap(flowToParent[s], flowToParent[t]);
			}
		}
	}

	neighbor.clear();
	neighbor.resize(N+5);
	for (int i = 0; i < N; i++) {
		if (parent[i] == i) continue;
		neighbor[i].push_back(ii(parent[i], flowToParent[i]));
		neighbor[parent[i]].push_back(ii(i, flowToParent[i]));
	}
}

/*
  2015-2016 ACM-ICPC, Central Europe Regional Contest (CERC 15)
  http://codeforces.com/gym/101480
  Problem J
*/

vector<vector<ii> > tree;

int cnt(int v, int previous, int k) {
	int ans = 0;
	for (int i = 0; i < tree[v].size(); i++) {
		if (tree[v][i].first == previous) continue;
		ans += min(k, tree[v][i].second);
		ans += cnt(tree[v][i].first, v, min(k, tree[v][i].second));
	}

	return ans;
}

int main() {
	int a, b;
	scanf("%d %d", &N, &M);
	
	init();
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &a, &b);
		a--; b--;
		add(a, b, 1);
		add(b, a, 1);
	}

	gomory_hu_tree(N, tree);
	
	int ans = 0;
	for (int i = 0; i < N; i++) {
		ans += cnt(i, -1, INF);
	}
	printf("%d\n", ans/2);
}

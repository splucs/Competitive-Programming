#include <bits/stdc++.h>
 
using namespace std;
#define MAXN 3005
#define MAXM 200005
#define INF 1000000009
typedef pair<int, int> ii;

int N, M;

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

int main() {
	int a, b;
	scanf("%d %d", &N, &M);
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &a, &b);
		a--; b--;
		addEdge(a, b, 1);
		addEdge(b, a, 1);
	}

	vector<vector<ii> > tree;
	gomory_hu_tree(N, tree);
}
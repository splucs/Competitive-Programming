#include <cstdio>
#include <vector>
#include <cstring>
#define MAXN 100009
using namespace std;

/*
 * Kosaraju SCC O(n)
 */

vector<int> adjList[MAXN], revAdjList[MAXN], ts;
bool vis[MAXN];
int comp[MAXN], parent = 0, numSCC;

void revdfs(int u) {
    vis[u] = true;
    for(int i = 0, v; i < (int)revAdjList[u].size(); i++) {
    	v = revAdjList[u][i];
        if(!vis[v]) revdfs(v);
    }
    ts.push_back(u);
}

void dfs(int u) {
    vis[u] = true; comp[u] = parent;
    for(int i = 0, v; i < (int)adjList[u].size(); i++) {
    	v = adjList[u][i];
        if(!vis[v]) dfs(v);
    }
}

void kosaraju(int n) {
	memset(&vis, false, sizeof vis);
    for(int i = 0; i < n; i++)  {
        if(!vis[i]) revdfs(i);
    }
    memset(&vis, false, sizeof vis);
    numSCC = 0;
    for(int i = n-1; i >= 0; i--) {
        if(!vis[ts[i]]) {
            parent = ts[i];
            dfs(ts[i]);
            numSCC++;
        }
    }
}

/*
 * TEST MATRIX
 */

int leader[MAXN];

int main() {
    int u, v, N, M;
	scanf("%d %d", &N, &M);
	for(int i=0; i<M; i++) {
		scanf("%d %d", &u, &v);
		adjList[u].push_back(v);
		revAdjList[v].push_back(u);
	}
    kosaraju(N);
    memset(&leader, -1, sizeof leader);
	for(int i=0; i<N; i++) {
		if (leader[comp[i]] == -1 || leader[comp[i]] > i) {
			leader[comp[i]] = i;
		}
	}
	for(int i=0; i<N; i++) printf("%d\n", leader[comp[i]]);
    return 0;
}
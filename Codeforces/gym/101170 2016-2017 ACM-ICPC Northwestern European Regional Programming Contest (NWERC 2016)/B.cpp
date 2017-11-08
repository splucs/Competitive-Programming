#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define FOR(x,n) for (int x = 0; x < n; x++)
typedef pair<int, int> ii;

vector<int> adjList[MAXN], revAdjList[MAXN], toposort;
bool num[MAXN];
int component[MAXN], parent = 0, N, M, numSCC;

void revdfs(int u) {
    num[u] = true;
    for(int i=0, v; i<(int)revAdjList[u].size(); i++){
    	v = revAdjList[u][i];
        if(!num[v]) revdfs(v);
    }
    toposort.push_back(u);
}

void dfs(int u) {
    num[u] = true;
    component[u] = parent;
    for(int i=0, v; i<(int)adjList[u].size(); i++){
    	v = adjList[u][i];
        if(!num[v]) dfs(v);
    }
}

void kosaraju(){
	memset(&num, false, sizeof num);
    for(int i=0; i<N; i++)  {
        if(!num[i]) revdfs(i);
    }
    memset(&num, false, sizeof num);
    numSCC = 0;
    for(int i=N-1; i>=0; i--){
        if(!num[toposort[i]]) {
			parent = numSCC;
            // parent = toposort[i];
            dfs(toposort[i]);
            numSCC++;
        }
    }
}

vector<int> inComp[MAXN], notInComp[MAXN];
vector<int> componentNodes[MAXN];
int pesos[MAXN];
map<int,int> memo[MAXN];
map<ii, int> dist;

int dfsComponents(int v, int orig) {
	if (memo[v].find(orig) != memo[v].end()) return memo[v][orig];
	
	int ans = 1, viz;
	for (int j = 0; j < componentNodes[v].size(); j++) {
		viz = componentNodes[v][j];
		
		ans = max(ans, dist[ii(orig,viz)]);
		for (int k = 0; k < notInComp[viz].size(); k++) {
			ans = max(ans, dist[ii(orig,viz)] + dfsComponents(component[notInComp[viz][k]], notInComp[viz][k]));
		}
	}
	memo[v][orig] = ans;
	return ans;
}

bool visited[MAXN];
void computeDist(int i, int j, int v) {
	visited[j] = true;
	
	if (dist.find(ii(i, j)) == dist.end()) dist[ii(i,j)] = v;
	else dist[ii(i,j)] = max(dist[ii(i,j)], v);
	
	for (int k = 0; k < inComp[j].size(); k++) {
		if (visited[inComp[j][k]]) continue;
		computeDist(i, inComp[j][k], v+1);
	}
	
	visited[j] = false;
}

int main() {
	int a, b;
	scanf("%d %d", &N, &M);
	FOR(x, M) {
		scanf("%d %d", &a, &b); a--; b--;
		adjList[a].push_back(b);
		revAdjList[b].push_back(a);
	}
	kosaraju();
	for (int i = 0; i < N; i++) {
		componentNodes[component[i]].push_back(i);
		for (int j = 0; j < adjList[i].size(); j++) {
			if (component[i] == component[adjList[i][j]]) inComp[i].push_back(adjList[i][j]);
			else notInComp[i].push_back(adjList[i][j]);	
		}
	}
	for (int i = 0; i < N; i++) computeDist(i,i, 1);
	
	int ans = 0;
	for (int i = 0; i < numSCC; i++) {
		for (int j = 0; j < componentNodes[i].size(); j++) {
		//	printf("%d %d\n", i, componentNodes[i][j]);
			ans = max(ans, dfsComponents(i, componentNodes[i][j]));
		}
	}
	printf("%d\n", ans);
}
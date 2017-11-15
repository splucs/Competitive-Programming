#include <vector>
#include <stack>
#include <set>
#include <algorithm>
#include <cstring>
using namespace std;
#define MAXN 400009
#define UNVISITED -1
#define EXPLORED -2
#define VISITED -3

int num[MAXN], vis[MAXN], component[MAXN], low[MAXN];
int N, counter, numSCC;
stack<int> S;
vector<int> adjList[MAXN];

void dfs(int u) {
	low[u] = num[u] = counter++;
	S.push(u);
	vis[u] = 1;
	int v;
	for (int j = 0; j < (int)adjList[u].size(); j++) {
		v = adjList[u][j];
		if (num[v] == UNVISITED) dfs(v);
		if (vis[v]) low[u] = min(low[u], low[v]);
	}
	if (low[u] == num[u]) {
		while (true) {
			v = S.top(); S.pop(); vis[v] = 0;
			component[v] = numSCC;
			if (u == v) break;
		}
		numSCC++;
	}
}

void tarjan(){
	counter = numSCC = 0;
	memset(&num, UNVISITED, sizeof num);
	memset(&vis, 0, sizeof vis);
	memset(&low, 0, sizeof low);
	for (int i = 0; i < N; i++){
		if (num[i] == UNVISITED)
			dfs(i);
	}
}

bool twosat(){
	tarjan();
	for(int i=0; i<N/2; i++){
		if (component[i]==component[i+N/2]) return false;
	}
	return true;
}

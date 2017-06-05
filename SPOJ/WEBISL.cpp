#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm>
#include <cstring>
using namespace std;
#define MAXN 100009
#define UNVISITED -1

int num[MAXN], vis[MAXN], component[MAXN], N, M, low[MAXN], counter, root, numSCC;
stack<int> S;
vector<int> adjList[MAXN];

void tarjan(int u) {
	low[u] = num[u] = counter++;
	S.push(u);
	vis[u] = 1;
	int v;
	for (int j = 0; j < (int)adjList[u].size(); j++) {
		v = adjList[u][j];
		if (num[v] == UNVISITED) tarjan(v);
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

int leader[MAXN];

int main(){
	int u, v;
	scanf("%d %d", &N, &M);
	for(int i=0; i<M; i++){
		scanf("%d %d", &u, &v);
		adjList[u].push_back(v);
	}
	counter = numSCC = 0;
	memset(&num, UNVISITED, sizeof num);
	memset(&vis, 0, sizeof vis);
	memset(&low, 0, sizeof low);
	for (int i = 0; i < N; i++){
		if (num[i] == UNVISITED)
			tarjan(i);
	}
	memset(&leader, -1, sizeof leader);
	for(int i=0; i<N; i++){
		if (leader[component[i]] == -1 || leader[component[i]] > i){
			leader[component[i]] = i;
		}
	}
	for(int i=0; i<N; i++) printf("%d\n", leader[component[i]]);
	return 0;
}

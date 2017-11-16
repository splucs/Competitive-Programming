#include <bits/stdc++.h>
using namespace std;
#define UNVISITED -1
#define EXPLORED -2
#define VISITED -3
#define MAXN 2009

int num[MAXN], vis[MAXN], component[MAXN], low[MAXN];
int value[MAXN], N, M, counter, root, numSCC;
stack<int> S;
vector<int> adjList[MAXN], toposort, C[MAXN];
set<int> adjComp[MAXN];

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

void ts(int u){
	vis[u] = VISITED;
	set<int>::iterator it;
	for(it = adjComp[u].begin(); it!=adjComp[u].end(); it++){
		if (vis[*it] == UNVISITED) dfs(*it);
	}
	toposort.push_back(u);
}

bool twosat(){
	tarjan();
	for(int i=0; i<N; i++){
		C[i].clear(); adjComp[i].clear();
	}
	for(int i=0; i<N/2; i++){
		if (component[i]==component[i+N/2]) return false;
	}
	return true;
}

int main(){
	int n,m;
	int a,b,u,v;
	while (scanf("%d%d",&n,&m)!=EOF){
		N = 2*n;
		for (int i=0;i<N;i++)adjList[i].clear();
		for (int i=0;i<m;i++){
			scanf("%d%d",&a,&b);
			u = a<0?-a-1+n:a-1;
			v = b<0?-b-1+n:b-1;
		
			adjList[(u+n)%N].push_back(v);
			adjList[(v+n)%N].push_back(u);
		}
		adjList[n].push_back(0);
		if (twosat())printf("yes\n");
		else printf("no\n");
	}
	
}
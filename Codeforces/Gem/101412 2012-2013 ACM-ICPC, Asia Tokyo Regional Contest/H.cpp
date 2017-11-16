#include <bits/stdc++.h>
using namespace std;
#define MAXN 109
#define MAXM 10009
#define UNVISITED -1

int num[MAXN], vis[MAXN], component[MAXN], N, low[MAXN], counter, numSCC;
stack<int> S;
vector<int> adjList[MAXN], revAdj[MAXN];

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
	for (int i = 1; i <= N; i++){
		if (num[i] == UNVISITED)
			dfs(i);
	}
}

typedef pair<int, int> ii;
int op[MAXM];
ii uv[MAXM];
bool nil[MAXN][MAXN];

void setNil(int u, int v) {
	if (nil[u][v] || nil[v][u]) return;
	nil[u][v] = nil[v][u] = true;
	
	if (u == v) for(int i=1; i<=N; i++) {
		setNil(u, i);
	}
	
	for(int i=0; i<(int)revAdj[u].size(); i++) {
		setNil(revAdj[u][i], v);
	}
	
	for(int i=0; i<(int)revAdj[v].size(); i++) {
		setNil(u, revAdj[v][i]);
	}
}

bool check(int M) {
	vector<ii> opr[6];
	int u, v;
	for(int j=0; j<M; j++) opr[op[j]].push_back(uv[j]);
	for(u=1; u<=N; u++) adjList[u].clear(), revAdj[u].clear();
	
	//add type 1 operations
	for(int it=0; it<(int)opr[1].size(); it++) {
		u = opr[1][it].first;
		v = opr[1][it].second;
		adjList[u].push_back(v);
		revAdj[v].push_back(u);
	}
	
	//add type 2 operations
	for(int it=0; it<(int)opr[2].size(); it++) {
		u = opr[2][it].first;
		v = opr[2][it].second;
		adjList[u].push_back(v);
		adjList[v].push_back(u);
		revAdj[u].push_back(v);
		revAdj[v].push_back(u);
	}
	
	//add type 4 restrictions
	memset(&nil, false, sizeof nil);
	for(int it=0; it<(int)opr[4].size(); it++) {
		u = opr[4][it].first;
		v = opr[4][it].second;
		setNil(u, v);
	}
	
	//check type 5 restrictions
	for(int it=0; it<(int)opr[5].size(); it++) {
		u = opr[5][it].first;
		v = opr[5][it].second;
		if (nil[u][v]) return false;
	}
	
	//check type 3 restrictions
	tarjan();
	for(int it=0; it<(int)opr[3].size(); it++) {
		u = opr[3][it].first;
		v = opr[3][it].second;
		if (component[u] == component[v]) return false;
		if (nil[u][u] && nil[v][v]) return false;
	}
	
	return true;
}

int main() {
	int M;
	while(scanf("%d %d", &N, &M), N || M) {
		
		for(int j=0; j<M; j++) {
			scanf("%d %d %d", &op[j], &uv[j].first, &uv[j].second);
		}
		
		int lo = 1;
		int hi = M+1;
		while(hi > lo + 1) {
			int mid = (hi + lo) / 2;
			if (check(mid)) lo = mid;
			else hi = mid;
		}
		
		printf("%d\n", lo);
	}
	return 0;
}
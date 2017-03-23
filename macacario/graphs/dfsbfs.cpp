#include <cstdio>
#include <stack>
#include <queue>
using namespace std;
#define MAXN 1009

int vis[MAXN];
vector<int> adjList[MAXN];

void dfs(int u){
	vis[u]=true;
	/* atividades neste no */
	int v;
	for(int i=0; i<(int)adjList[u].size(); i++){
		v = adjList[u][i];
		if (!vis[v]) dfs(v);
	}
}

void dfsstack(){
	memset(&vis, false, sizeof vis);
	stack<int> s;
	s.push(root);
	int u, v;
	while(!s.empty()){
		u = s.top();
		s.pop();
		/* atividades neste no */
		for(int i=0; i<(int)adjList[u].size(); i++){
			v = adjList[u][i];
			if (!vis[v]) {
				vis[v] = true;
				s.push(v);
			}
		}
	}
}

void bfs(){
	memset(&vis, false, sizeof vis);
	queue<int> q;
	q.push(root);
	int u, v;
	while(!q.empty()){
		u = q.top();
		q.pop();
		/* atividades neste no */
		for(int i=0; i<(int)adjList[u].size(); i++){
			v = adjList[u][i];
			if (!vis[v]) {
				vis[v] = true;
				q.push(v);
			}
		}
	}
}
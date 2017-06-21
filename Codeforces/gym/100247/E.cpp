#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009

vector<int> adj[MAXN], ans;
char access[MAXN];
int n;

char dfs(int u, char c){
	if (access[u] == '0') access[u] = c;
	if (adj[u].empty()) return access[u];
	bool sons = true;
	for(int i=0; i<(int)adj[u].size(); i++){
		int v = adj[u][i];
		if (dfs(v, access[u]) == '-') sons = false;
	}
	if (sons) access[u] = '+';
	else{
		for(int i=0; i<(int)adj[u].size(); i++){
			int v = adj[u][i];
			if (access[v] == '+') ans.push_back(v);
		}
		access[u] = '-';
	}
	//printf("access[%d] = %c, sons = %d\n", u, access[u], sons);
	return access[u];
	
}

int main()
{
	int u, v;
	scanf("%d", &n);
	scanf(" %s", access+1);
	for(int i=0; i<n-1; i++){
		scanf("%d %d", &u, &v);
		adj[u].push_back(v);
	}
	if(dfs(1, '-') == '+'){
		printf("1\n1\n");
	}
	else{
		printf("%d\n", ans.size());
		sort(ans.begin(), ans.end());
		for(int i=0; i<(int)ans.size(); i++){
			if(i > 0) printf(" ");
			printf("%d", ans[i]);
		}
		printf("\n");
	}
	return 0;
}